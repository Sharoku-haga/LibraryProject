//==================================================================================================================================//
//!< @file		slDXDrawingCommander.h		
//!< @brief		sl::DXDrawingCommanderクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/30	更新履歴：
//==================================================================================================================================//

#ifndef SL_DX_DRAWING_COMMANDER_H
#define SL_DX_DRAWING_COMMANDER_H

#include <windows.h>
#include <d3dx11.h>

namespace sl
{

//===================================================================================//
//!< DirextXの描画の全体的な命令を管理するクラス
//===================================================================================//
class DXDrawingCommander
{

public:
	/** 
	* Constructor 
	* @param[in] pDeviceContext		Direct3Dのデバイスコンテキスト
	* @param[in] pDXGISwapChain		DXGIのスワップチェイン
	* @param[in] pRenderTargetView	レンダリングターゲットビュー
	* @param[in] pDepthStencilView	深度ステンシルビュー
	*/
	DXDrawingCommander(ID3D11DeviceContext*		pDeviceContext
					, IDXGISwapChain*			pDXGISwapChain
					, ID3D11RenderTargetView*	pRenderTargetView
					, ID3D11DepthStencilView*	pDepthStencilView);

	/** Destructor */
	~DXDrawingCommander();

	/** 初期化を行う関数 */
	void Initialize();

	/** 描画開始処理 */
	void StartRender(void);

	/** 描画終了処理 */
	void EndRender(void);

	/**
	* ステンシルテストを設定する関数
	* @param[in] isisStencilTest	true→ステンシルテストON, false→ステンシルテストOFF
	*/
	void SetUpDepthStencilTest(bool isStencilTest);

	/**
	* ラスタライザステートを設定する関数
	* @param[in] pRasterizerState	設定したいラスタライザ
	*/
	void SetUpRasterizerState(ID3D11RasterizerState*	pRasterizerState);

	/**
	* ブレンドステートを設定する関数
	* @param[in] pBlendState	設定したいブレンドステート 
	* @param[in] sampleMask		サンプルマスク
	*/
	void SetUpBlendState(ID3D11BlendState*	pBlendState, UINT sampleMask = 0xffffffff);

private:
	ID3D11DeviceContext*			m_pDeviceContext;			//!< Direct3Dのデバイスコンテキスト
	IDXGISwapChain*					m_pDXGISwapChain;			//!< スワップチェイン
	ID3D11RenderTargetView*			m_pRenderTargetView;		//!< レンダリングターゲットビュー
	ID3D11DepthStencilView*			m_pDepthStencilView;		//!< 深度ステンシルビュー

	/** ビューポートを設定する関数 */
	void SetUpViewPort();

};	// class DXDrawingCommander

}	// namespace sl

#endif

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
