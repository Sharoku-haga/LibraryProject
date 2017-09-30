//==================================================================================================================================//
//!< @file		slDXViewManager.h		
//!< @brief		sl::DXViewManagerクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/30	更新履歴：
//==================================================================================================================================//

#ifndef SL_DX_VIEW_MANAGER_H
#define SL_DX_VIEW_MANAGER_H

#include <d3dx11.h>

namespace sl
{

//===================================================================================//
//!< DirextXのビュー関連を管理するクラス
//===================================================================================//
class DXViewManager
{

public:
	/** Constructor */
	DXViewManager();

	/** Destructor */
	~DXViewManager();

	/**
	* レンダリングターゲットビューを生成する関数
	* @param[in] pDevice			DirectXのデバイス
	* @param[in] pDXGISwapChain		DXGIのスワップチェイン
	* @return ture→成功 false→失敗
	*/
	bool CreateRenderTargetView(ID3D11Device* pDevice, IDXGISwapChain* pDXGISwapChain);

	/**
	* 深度ステンシルビューを生成する関数
	* @param[in] pDevice			DirectXのデバイス
	* @param[in] pDXGISwapChain		DXGIのスワップチェイン
	* @return ture→成功 false→失敗
	*/
	bool CreateDepthStencilView(ID3D11Device* pDevice, IDXGISwapChain* pDXGISwapChain);

	/**
	* Getter
	* @return レンダリングターゲットビューへのポインタ
	*/
	inline ID3D11RenderTargetView* GetRenderTargetView() const { return m_pRenderTargetView; }
	
	/**
	* Getter
	* @return	深度ステンシルビューへのポインタ
	*/
	inline ID3D11DepthStencilView* GetDepthStencilView() const { return m_pDepthStencilView; }

private:
	ID3D11RenderTargetView*			m_pRenderTargetView;		//!< レンダリングターゲットビュー
	ID3D11DepthStencilView*			m_pDepthStencilView;		//!< 深度ステンシルビュー
	ID3D11Texture2D*				m_pDepthStencilBuffer;		//!< 深度ステンシルバッファ

};	// class DXViewManager

}	// namespace sl

#endif	// SL_DX_VIEW_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
