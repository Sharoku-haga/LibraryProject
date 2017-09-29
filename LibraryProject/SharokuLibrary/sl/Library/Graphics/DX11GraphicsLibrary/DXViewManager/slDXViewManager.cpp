//==================================================================================================================================//
//!< @file		slDXViewManager.cpp		
//!< @brief		sl::DXViewManagerクラス実装
//!< @author	T.Haga
//!< @data		作成日時：2017/09/30	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "../../../Utility/slTemplateFunction.h"
#include "slDXViewManager.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DXViewManager::DXViewManager()
	: m_pRenderTargetView(NULL)
	, m_pDepthStencilView(NULL)
	, m_pDepthStencilBuffer(NULL)
{}

DXViewManager::~DXViewManager()
{
	SafeReleaseDX(m_pDepthStencilView);
	SafeReleaseDX(m_pDepthStencilBuffer);
	SafeReleaseDX(m_pRenderTargetView);
}

bool DXViewManager::CreateRenderTargetView(ID3D11Device* pDevice, IDXGISwapChain* pDXGISwapChain)
{
	if(m_pRenderTargetView != NULL)
	{
		return true;
	}

	ID3D11Texture2D* pBackBuffer = NULL;		
	// スワップチェーンからバックバッファを取得する
	if(FAILED(pDXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer))))
	{
		return false;
	}
	
	if(FAILED(pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView)))
	{
		SafeReleaseDX(pBackBuffer);
		return false;
	}
	SafeReleaseDX(pBackBuffer);			// 参照カウンタを減らす

	return true;
}

bool DXViewManager::CreateDepthStencilView(ID3D11Device* pDevice, IDXGISwapChain* pDXGISwapChain)
{
	if(m_pDepthStencilView != NULL)
	{
		return true;
	}

	// スワップチェーンの設定を取得する
	DXGI_SWAP_CHAIN_DESC			swapChainDesc;
	pDXGISwapChain->GetDesc(&swapChainDesc);

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

	if(FAILED(pDevice->CreateTexture2D(&depthDesc, NULL, &m_pDepthStencilBuffer)))
	{
		SafeReleaseDX(m_pRenderTargetView);
		return false;
	}

	if(FAILED(pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, NULL, &m_pDepthStencilView)))
	{
		SafeReleaseDX(m_pDepthStencilBuffer);
		SafeReleaseDX(m_pRenderTargetView);
		return false;
	}

	return true;
}

}	// nmaespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
