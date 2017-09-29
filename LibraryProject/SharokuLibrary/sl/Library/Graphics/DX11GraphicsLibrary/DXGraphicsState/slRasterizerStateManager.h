//==================================================================================================================================//
//!< @file		slRasterizerStateManager.h
//!< @brief		sl::RasterizerStateManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/01	更新履歴：
//==================================================================================================================================//

#ifndef SL_RASTERIZER_STATE_MANAGER_H
#define SL_RASTERIZER_STATE_MANAGER_H

#include <d3dx11.h>

namespace sl
{

/** @todo ラスタライザステートをカスタムできる機能を追加したい */
//===================================================================================//
//!< ラスタライザステートを管理するクラス
//===================================================================================//
class RasterizerStateManager
{

public:
	/** Constructor */
	RasterizerStateManager();

	/** Destructor */
	~RasterizerStateManager();

	/**
	* ラスタライザステートを生成する関数
	* @param[in] pDevice			DirectXのデバイス
	* @return ture→成功 false→失敗
	*/
	bool CreateDefaultRasterizerState(ID3D11Device*	pDevice);

	/**
	* Getter
	* @return デフォルトラスタライザステート
	*/
	inline ID3D11RasterizerState* GetDefaultRasterizerState() { return m_pDefaultRasterizerState; }

private:
	ID3D11RasterizerState*	m_pDefaultRasterizerState;	// デフォルトのラスタライザステート

};	// class RasterizerStateManager

}	// namespace sl

#endif	// SL_RASTERIZER_STATE_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
