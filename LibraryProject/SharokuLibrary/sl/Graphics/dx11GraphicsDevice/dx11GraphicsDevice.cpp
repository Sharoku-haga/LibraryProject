//==================================================================================================================================//
//!< @file		dx11GraphicsDevice.h
//!< @brief		dx11::GraphicsDeviceクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "dx11GraphicsDevice.h"
#include "../../Common/slDefine.h"
#include "../../Common/slTemplate.h"
#include "../../slBuild.h"
#include <crtdbg.h>

/* Namespace -------------------------------------------------------------------------------------------------- */

namespace sl
{
namespace dx11
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const UINT	AppFPS				= 60;									// アプリケーションのFPS
const float ClearColor[4]		= { 0.0f, 0.0f, 0.0f, 0.0f};			// 画面をクリアする色、RGBAの順

}

/* Public Functions ------------------------------------------------------------------------------------------- */

GraphicsDevice::GraphicsDevice(void)
	: m_hWnd(NULL)
	, m_pDevice(NULL)
	, m_pDeviceContext(NULL)
	, m_pDXGISwapChain(NULL)
	, m_pDXGI(NULL)
	, m_pDXGIAdapter(NULL)
	, m_pDXGIFactory(NULL)
	, m_pRenderTargetView(NULL)
	, m_pDepthStencilView(NULL)
	, m_pDepthStencilBuffer(NULL)
	, m_pRasterizerState(NULL)
{}

GraphicsDevice::~GraphicsDevice(void)
{
	Finalize();
}

bool GraphicsDevice::Initialize(HWND hWnd)
{
	if(RESULT_FAILED(InitDevice()))
	{
		MessageBox(0, "DeviceとDeviceContextの生成に失敗しました。", NULL, MB_OK);
		return false;
	}

	if(RESULT_FAILED(InitDXGI(hWnd)))
	{
		MessageBox(0, "SwapChainの生成と設定に失敗しました。", NULL, MB_OK);
		ReleaseDevice();
		return false;
	}

	m_hWnd = hWnd;

	if(RESULT_FAILED(InitView()))
	{
		MessageBox(0, "View関連の生成と設定に失敗しました。", NULL, MB_OK);
		ReleaseDXGI();
		ReleaseDevice();
		return false;
	}

	if(RESULT_FAILED(InitRasterizerState()))
	{
		MessageBox(0, "ラスタライザの設定に失敗しました。", NULL, MB_OK);
		ReleaseView();
		ReleaseDXGI();
		ReleaseDevice();
		return false;
	}

	return true;
}

void GraphicsDevice::Finalize(void)
{
	ReleaseSafely(m_pRasterizerState);
	ReleaseView();
	ReleaseDXGI();
	ReleaseDevice();
}

void GraphicsDevice::StartRender(void)
{
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);						// 画面をクリア
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);		// ステンシルバッファをクリア
}

void GraphicsDevice::EndRender(void)
{
	m_pDXGISwapChain->Present(1, 0);			// 画面を更新する
}

void GraphicsDevice::ChangeWindowMode(bool isFullScreen)
{
	m_pDXGISwapChain->SetFullscreenState(isFullScreen, NULL);

#ifdef FULL_SCREEN
	// 初期起動をフルスクリーンモードにした場合、ウィンドウモードに変更すると
	// ウィンドウがアクティブにならないの可能性があるとのことのなので、念の為表示させる。
	if(isFullScreen == false)
	{
		ShowWindow(m_hWnd, SW_SHOW);
	}
#endif	// FULL_SCREEN

}

/* Private Functions ------------------------------------------------------------------------------------------ */

bool GraphicsDevice::InitDevice(void)
{
	// デバイス作成時に使用するビデオカードの性能一覧(仮置き)
	/** @todo 現在はシェーダー モデル 5 などの Direct3D 11.0 でサポートされている機能のみに限定 */
	D3D_FEATURE_LEVEL	pFeatureLevels[] = { D3D_FEATURE_LEVEL_11_0 };			

	HRESULT hr = D3D11CreateDevice(
		NULL,								// 使用するアダプターを設定。NULLの場合はデフォルトのアダプター。
		D3D_DRIVER_TYPE_HARDWARE,			// ドライバーの種類。pAdapterが NULL 以外の場合は、D3D_DRIVER_TYPE_UNKNOWNを指定する。
		NULL,								// ソフトウェアラスタライザを実装するDLLへのハンドル。D3D_DRIVER_TYPE を D3D_DRIVER_TYPE_SOFTWARE に設定している場合は NULL にできない。
		0,									// デバイスを作成時に使用されるパラメータ
		pFeatureLevels,						// D3D_FEATURE_LEVELのポインタ
		1,									// D3D_FEATURE_LEVEL配列の要素数
		D3D11_SDK_VERSION,					// DirectX SDKのバージョン
		&m_pDevice,							// 初期化されたデバイス
		&m_FeatureLevel,					// 採用されたフィーチャーレベル
		&m_pDeviceContext);					// 初期化されたデバイスコンテキスト

	if(FAILED(hr))
	{
		return false;
	}

	return true;
}

bool GraphicsDevice::InitDXGI(HWND hWnd)
{
	/** @note 今回はDXGIでSwapChainを作成している */

	// インタフェース取得
	if(FAILED(m_pDevice->QueryInterface(__uuidof(IDXGIDevice1), reinterpret_cast<void**>(&m_pDXGI))))
	{
		return false;
	}

	//  アダプター取得
	if(FAILED(m_pDXGI->GetAdapter(&m_pDXGIAdapter)))
	{
		ReleaseSafely(m_pDXGI);
		return false;
	}

	// ファクトリー取得
	if(FAILED(m_pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&m_pDXGIFactory))))
	{
		ReleaseSafely(m_pDXGIAdapter);
		ReleaseSafely(m_pDXGI);
		return false;
	}

	// ALT+Enterでフルスクリーンを許可している。しない場合は第二引数でDXGI_MWA_NO_ALT_ENTERを指定する
	if(FAILED(m_pDXGIFactory->MakeWindowAssociation(hWnd, 0)))
	{
		return false;
	}

	// スワップチェーンを作成する
	{
		// 設定したいバックバッファの幅と高さを求める
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);
		int backBufferWidth = static_cast<int>((clientRect.right - clientRect.left));
		int backBufferHeight = static_cast<int>((clientRect.bottom - clientRect.top));

		// ウィンドウモード選択
#ifdef FULL_SCREEN
		BOOL windowMode = FALSE;
#else
		BOOL windowMode = TRUE;
#endif	// FULL_SCREEN

		// スワップチェーンの設定
		/** @todo 現在は数値はほぼ固定してるが、後で設定できるように作り直したい */
		DXGI_SWAP_CHAIN_DESC			swapChainDesc;
		swapChainDesc.BufferDesc.Width						= backBufferWidth;							// バックバッファの幅
		swapChainDesc.BufferDesc.Height						= backBufferHeight;							// バックバッファの高さ
		swapChainDesc.BufferDesc.Format						= DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;			// ディスプレイフォーマット(各8ビットの符号なし整数タイプでwindows標準のsRGBの非線形カラーフォーマット)
		swapChainDesc.BufferDesc.RefreshRate.Numerator		= AppFPS;									// リフレッシュ・レート(分子)
		swapChainDesc.BufferDesc.RefreshRate.Denominator	= 1;										// リフレッシュ・レート(分母)
		swapChainDesc.BufferDesc.ScanlineOrdering			= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;		// スキャンライン・オーダー(走査方式の指定)。現在は指定なし。
		swapChainDesc.BufferDesc.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;			// スケーリングモード(バックバッファのサイズの拡縮指定)。現在は指定なし。
		swapChainDesc.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT;			// バックバッファの使用方法
		swapChainDesc.SampleDesc.Count						= 1;										// マルチサンプルの数(アンチエリアス処理を行わない為この数値)
		swapChainDesc.SampleDesc.Quality					= 0;										// クオリティ(アンチエリアス処理を行わない為この数値)
		swapChainDesc.BufferCount							= 1;										// バックバッファの数(現在は1で固定)
		swapChainDesc.OutputWindow							= hWnd;										// 関連付けるウィンドウ
		swapChainDesc.Windowed								= windowMode;								// ウィンドウモード(falseだとフルスクリーンモード)
		swapChainDesc.SwapEffect							= DXGI_SWAP_EFFECT_DISCARD;					// スワップ効果の指定
		swapChainDesc.Flags									= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	// モード自動切換え

		// スワップチェーンの作成
		if(FAILED(m_pDXGIFactory->CreateSwapChain(m_pDevice, &swapChainDesc, &m_pDXGISwapChain)))
		{
			ReleaseSafely(m_pDXGIFactory);
			ReleaseSafely(m_pDXGIAdapter);
			ReleaseSafely(m_pDXGI);
			return false;
		}
	}

	return true;
}

bool GraphicsDevice::InitView(void)
{
	// レンダリングターゲットビューを作成する
	{
		ID3D11Texture2D* pBackBuffer = NULL;		
		// スワップチェーンからバックバッファを取得する
		if(FAILED(m_pDXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer))))
		{
			return false;
		}

		if(FAILED(m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView)))
		{
			ReleaseSafely(pBackBuffer);
			return false;
		}
		ReleaseSafely(pBackBuffer);			// 参照カウンタを減らす
	}

	// スワップチェーンの設定を取得する
	DXGI_SWAP_CHAIN_DESC			swapChainDesc;
	m_pDXGISwapChain->GetDesc(&swapChainDesc);

	// 深度ステンシルビューを作成する
	{
		D3D11_TEXTURE2D_DESC	depthDesc;			
		depthDesc.Width					= swapChainDesc.BufferDesc.Width;		// 幅(バックバッファと同じにする)
		depthDesc.Height				= swapChainDesc.BufferDesc.Height;		// 高さ(バックバッファと同じにする)
		depthDesc.MipLevels				= 1;									// ミップマップの設定。現在はミップマップを作成しない設定
		depthDesc.ArraySize				= 1;									// テクスチャーの配列数。特に指定しないので1
		depthDesc.Format				= DXGI_FORMAT_D32_FLOAT;				// フォーマット
		depthDesc.SampleDesc.Count		= swapChainDesc.SampleDesc.Count;		// マルチサンプルの数(バックバッファと同じにする)
		depthDesc.SampleDesc.Quality	= swapChainDesc.SampleDesc.Quality;		// クオリティ(バックバッファと同じにする)
		depthDesc.Usage					= D3D11_USAGE_DEFAULT;					// CPUとGPUのアクセス権指定。現在はGPUのみに設定
		depthDesc.BindFlags				= D3D11_BIND_DEPTH_STENCIL;				// パイプライン ステージへのバインドに関するフラグ。深度ステンシルを指定
		depthDesc.CPUAccessFlags		= 0;									// CPU アクセスの種類を指定するフラグ。今回は指定はなし
		depthDesc.MiscFlags				= 0;									// 他の一般性の低いリソース オプションを識別するフラグ。今回は適用なし。

		if(FAILED(m_pDevice->CreateTexture2D(&depthDesc, NULL, &m_pDepthStencilBuffer)))
		{
			ReleaseSafely(m_pRenderTargetView);
			return false;
		}

		if(FAILED(m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, NULL, &m_pDepthStencilView)))
		{
			ReleaseSafely(m_pDepthStencilBuffer);
			ReleaseSafely(m_pRenderTargetView);
			return false;
		}
	}

	// レンダーターゲットビューと深度ステンシルビューをパイプラインにバインド
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	// ビューポート設定
	{
		D3D11_VIEWPORT viewPort;
		viewPort.TopLeftX	= 0;
		viewPort.TopLeftY	= 0;
		viewPort.Width		= swapChainDesc.BufferDesc.Width;
		viewPort.Height		= swapChainDesc.BufferDesc.Height;
		viewPort.MinDepth	= 0.0f;
		viewPort.MaxDepth	= 1.0f;
		m_pDeviceContext->RSSetViewports(1, &viewPort);
	}

	return true;
}

bool GraphicsDevice::InitRasterizerState(void)
{
	// ラスタライザを設定
	/** @todo この辺りの設定は面白そうなので後でさわってみる */
	D3D11_RASTERIZER_DESC rasterizerDesc;
	rasterizerDesc.FillMode					= D3D11_FILL_SOLID;			// レンダリング時に使用する描画モード. 現在はポリゴン描画モード
	rasterizerDesc.CullMode					= D3D11_CULL_BACK;			// 特定の方向を向いている三角形の描画の有無の指定. 後ろ向きの三角形を描画しない指定をしている
	rasterizerDesc.FrontCounterClockwise	= FALSE;					// 三角形が前向きか後ろ向きかを決定する。時計回りを表面
//	rasterizerDesc.FrontCounterClockwise	= TRUE;						// 反時計回りを表面
	rasterizerDesc.DepthBias				= 0;						// 指定のピクセルに加算する深度値. 今回は0.0f。
	rasterizerDesc.DepthBiasClamp			= 0.0f;						// ピクセルの最大深度バイアス(同一平面上に存在しないかのように表示するためののもの). 今回は0.0f。
	rasterizerDesc.SlopeScaledDepthBias		= 0.0f;						// 指定のピクセルのスロープに対するスカラ
	rasterizerDesc.DepthClipEnable			= FALSE;					// 距離に基づいてクリッピング. 今回は無効.
	rasterizerDesc.ScissorEnable			= FALSE;					// シザー矩形カリング. 今回は無効.
	rasterizerDesc.MultisampleEnable		= FALSE;					// マルチサンプリングのアンチエイリアシング. 今回は無効.
	rasterizerDesc.AntialiasedLineEnable	= FALSE;					// 線のアンチエイリアシング(線を描画中で MultisampleEnable が false の場合にのみ適用).今回は無効.

	// 設定を元に作成
	if(FAILED(m_pDevice->CreateRasterizerState(&rasterizerDesc, &m_pRasterizerState)))
	{
		return false;
	}

	m_pDeviceContext->RSSetState(m_pRasterizerState);
	return true;
}

void GraphicsDevice::ReleaseDevice(void)
{
	ReleaseSafely(m_pDeviceContext);
	ReleaseSafely(m_pDevice);
}

void GraphicsDevice::ReleaseDXGI(void)
{
	// フルスクリーンだとうまく解放されない可能性があるためウィンドウモードに戻す
	m_pDXGISwapChain->SetFullscreenState(false, NULL);
	ReleaseSafely(m_pDXGISwapChain);
	ReleaseSafely(m_pDXGIFactory);
	ReleaseSafely(m_pDXGIAdapter);
	ReleaseSafely(m_pDXGI);
}

void GraphicsDevice::ReleaseView(void)
{
	ReleaseSafely(m_pDepthStencilView);
	ReleaseSafely(m_pDepthStencilBuffer);
	ReleaseSafely(m_pRenderTargetView);
}

}	// namespace dx11
}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
