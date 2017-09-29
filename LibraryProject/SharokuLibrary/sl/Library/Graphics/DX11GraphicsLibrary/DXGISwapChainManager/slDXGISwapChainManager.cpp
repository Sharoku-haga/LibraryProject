//==================================================================================================================================//
//!< @file		slDXGISwapChainManager.cpp
//!< @brief		sl::DXGISwapChainManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/09/29	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDXGISwapChainManager.h"
#include "../../../Window/slWindowDeclaration.h"
#include "../../../../slBuild.h"
#include "../../../Utility/slTemplateFunction.h"

namespace sl
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{
	const UINT	RefreshRateFPS		= 60;		// リフレッシュレートのFPS
}

/* Public Functions ------------------------------------------------------------------------------------------- */

DXGISwapChainManager::DXGISwapChainManager()	
	: m_pDXGISwapChain(NULL)
	, m_pDXGI(NULL)
	, m_pDXGIAdapter(NULL)
	, m_pDXGIFactory(NULL)
{}

DXGISwapChainManager::~DXGISwapChainManager()
{
	// フルスクリーンだとうまく解放されない可能性があるためウィンドウモードに戻す
	m_pDXGISwapChain->SetFullscreenState(FALSE, NULL);
	sl::SafeReleaseDX(m_pDXGISwapChain);
	sl::SafeReleaseDX(m_pDXGIFactory);
	sl::SafeReleaseDX(m_pDXGIAdapter);
	sl::SafeReleaseDX(m_pDXGI);
}

bool DXGISwapChainManager::CreateDXGISwapChain(const WindowHandle& rHandle, ID3D11Device* pDevice, const fRect& rBackbufferSize)
{
	HWND hWnd = static_cast<HWND>(rHandle.m_pAdress);

	// インタフェース取得
	if(FAILED(pDevice->QueryInterface(__uuidof(IDXGIDevice1), reinterpret_cast<void**>(&m_pDXGI))))
	{
		return false;
	}

	//  アダプター取得
	if(FAILED(m_pDXGI->GetAdapter(&m_pDXGIAdapter)))
	{
		sl::SafeReleaseDX(m_pDXGI);
		return false;
	}

	// ファクトリー取得
	if(FAILED(m_pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&m_pDXGIFactory))))
	{
		sl::SafeReleaseDX(m_pDXGIAdapter);
		sl::SafeReleaseDX(m_pDXGI);
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
		int backBufferWidth = static_cast<int>((rBackbufferSize.m_Right - rBackbufferSize.m_Left));
		int backBufferHeight = static_cast<int>((rBackbufferSize.m_Bottom - rBackbufferSize.m_Top));

		// スワップチェーンの設定
		/** @todo 現在は数値はほぼ固定してるが、後で設定できるように作り直したい */
		DXGI_SWAP_CHAIN_DESC			swapChainDesc;
		swapChainDesc.BufferDesc.Width						= backBufferWidth;							// バックバッファの幅
		swapChainDesc.BufferDesc.Height						= backBufferHeight;							// バックバッファの高さ
		swapChainDesc.BufferDesc.Format						= DXGI_FORMAT_R8G8B8A8_UNORM;				// ディスプレイフォーマット(各8ビットの符号なし整数タイプ)
		swapChainDesc.BufferDesc.RefreshRate.Numerator		= RefreshRateFPS;							// リフレッシュ・レート(分子)
		swapChainDesc.BufferDesc.RefreshRate.Denominator	= 1;										// リフレッシュ・レート(分母)
		swapChainDesc.BufferDesc.ScanlineOrdering			= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;		// スキャンライン・オーダー(走査方式の指定)。現在は指定なし。
		swapChainDesc.BufferDesc.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;			// スケーリングモード(バックバッファのサイズの拡縮指定)。現在は指定なし。
		swapChainDesc.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT;			// バックバッファの使用方法
		swapChainDesc.SampleDesc.Count						= 1;										// マルチサンプルの数(アンチエリアス処理を行わない為この数値)
		swapChainDesc.SampleDesc.Quality					= 0;										// クオリティ(アンチエリアス処理を行わない為この数値)
		swapChainDesc.BufferCount							= 1;										// バックバッファの数(現在は1で固定)
		swapChainDesc.OutputWindow							= hWnd;										// 関連付けるウィンドウ
		swapChainDesc.Windowed								= TRUE;										// ウィンドウモード(falseだとフルスクリーンモード)
		swapChainDesc.SwapEffect							= DXGI_SWAP_EFFECT_DISCARD;					// スワップ効果の指定
		swapChainDesc.Flags									= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	// モード自動切換え

		// スワップチェーンの作成
		if(FAILED(m_pDXGIFactory->CreateSwapChain(pDevice, &swapChainDesc, &m_pDXGISwapChain)))
		{
			sl::SafeReleaseDX(m_pDXGIFactory);
			sl::SafeReleaseDX(m_pDXGIAdapter);
			sl::SafeReleaseDX(m_pDXGI);
			return false;
		}

// ビルド設定がフルスクリーンモードなら、それに変更
#ifdef FULL_SCREEN
	ChangeScreenMode(FALSE);
#endif	// FULL_SCREEN
	}
	return true;
}

void DXGISwapChainManager::ChangeScreenMode(bool isFullScreen)
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

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
