//==================================================================================================================================//
//!< @file		slDXRasterizerStateManager.h
//!< @brief		sl::DXRasterizerStateManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/01	更新履歴：
//==================================================================================================================================//

#ifndef SL_DX_RASTERIZER_STATE_MANAGER_H
#define SL_DX_RASTERIZER_STATE_MANAGER_H

#include <d3dx11.h>

namespace sl
{

/** @todo ラスタライザステートをカスタムできる機能を追加したい */
//===================================================================================//
//!< ラスタライザステートを管理するクラス
//===================================================================================//
class DXRasterizerStateManager
{

public:
	/** Constructor */
	DXRasterizerStateManager();

	/** Destructor */
	~DXRasterizerStateManager();

	/**
	* デフォルトのラスタライザステートを生成する関数
	* @param[in] pDevice			DirectXのデバイス
	* @return ture→成功 false→失敗
	*/
	bool CreateDefaultRasterizerState(ID3D11Device*	pDevice);

	/**
	* Getter
	* @return デフォルトラスタライザステート
	*/
	inline ID3D11RasterizerState* GetDefaultRasterizerState() const { return m_pDefaultRasterizerState; }

private:
	ID3D11RasterizerState*	m_pDefaultRasterizerState;	// デフォルトのラスタライザステート

};	// class DXRasterizerStateManager

}	// namespace sl

#endif	// SL_DX_RASTERIZER_STATE_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
