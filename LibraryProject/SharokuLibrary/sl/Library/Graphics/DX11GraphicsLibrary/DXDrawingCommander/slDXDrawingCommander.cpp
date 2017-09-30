
//==================================================================================================================================//
//!< @file		slDXDrawingCommander.cpp
//!< @brief		sl::DXDrawingCommanderクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/09/30	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "../../../../slBuild.h"
#include "../../../Utility/slTemplateFunction.h"
#include "slDXDrawingCommander.h"

namespace sl
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const float ClearColor[4]		= { 1.0f, 1.0f, 1.0f, 1.0f};			// 画面をクリアする色、RGBAの順

}

/* Public Functions ------------------------------------------------------------------------------------------- */

DXDrawingCommander::DXDrawingCommander(ID3D11DeviceContext*		pDeviceContext
									, IDXGISwapChain*			pDXGISwapChain
									, ID3D11RenderTargetView*	pRenderTargetView
									, ID3D11DepthStencilView*	pDepthStencilView)
	: m_pDeviceContext(pDeviceContext)
	, m_pDXGISwapChain(pDXGISwapChain)
	, m_pRenderTargetView(pRenderTargetView)
	, m_pDepthStencilView(pDepthStencilView)
{}

DXDrawingCommander::~DXDrawingCommander()
{}

void DXDrawingCommander::Initialize()
{

#ifdef STRAT_STECIL_TEST_ON
	// レンダーターゲットビューと深度ステンシルビューをパイプラインにバインド
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
#else 
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
#endif

	SetUpViewPort();
}

void DXDrawingCommander::StartRender(void)
{
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);						// 画面をクリア
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);		// ステンシルバッファをクリア
}

void DXDrawingCommander::EndRender(void)
{
	m_pDXGISwapChain->Present(1, 0);			// 画面を更新する
}

void DXDrawingCommander::SetUpDepthStencilTest(bool isStencilTest)
{
	if(isStencilTest)
	{
		m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
	}
	else
	{
		m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
	}	
}

void DXDrawingCommander::SetUpRasterizerState(ID3D11RasterizerState*	pRasterizerState)
{
	m_pDeviceContext->RSSetState(pRasterizerState);
}

void DXDrawingCommander::SetUpBlendState(ID3D11BlendState*	pBlendState, UINT sampleMask)
{
	m_pDeviceContext->OMSetBlendState(pBlendState, NULL, sampleMask);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void DXDrawingCommander::SetUpViewPort()
{
	// スワップチェーンの設定を取得する
	DXGI_SWAP_CHAIN_DESC			swapChainDesc;
	m_pDXGISwapChain->GetDesc(&swapChainDesc);

	D3D11_VIEWPORT viewPort;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = static_cast<FLOAT>(swapChainDesc.BufferDesc.Width);
	viewPort.Height = static_cast<FLOAT>(swapChainDesc.BufferDesc.Height);
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	m_pDeviceContext->RSSetViewports(1, &viewPort);
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
