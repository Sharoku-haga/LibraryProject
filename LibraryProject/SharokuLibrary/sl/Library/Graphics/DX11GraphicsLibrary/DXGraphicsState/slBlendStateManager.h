//==================================================================================================================================//
//!< @file		slBlendStateManager.h
//!< @brief		sl::BlendStateManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/01	更新履歴：
//==================================================================================================================================//

#ifndef SL_BLEND_STATE_MANAGER_H
#define SL_BLEND_STATE_MANAGER_H

#include <d3dx11.h>

namespace sl
{

/** @todo ブレンドステートをカスタムできる機能を追加したい */
//===================================================================================//
//!< ブレンドステートを管理するクラス
//===================================================================================//
class BlendStateManager
{

public:
	/** Constructor */
	BlendStateManager();

	/** Destructor */
	~BlendStateManager();

	/**
	* デフォルトブレンドステートを生成する関数
	* @param[in] pDevice			DirectXのデバイス
	* @return ture→成功 false→失敗
	*/
	bool CreateDefaultBlendState(ID3D11Device*	pDevice);

	/**
	* Getter
	* @return デフォルトブレンドステート
	*/
	inline ID3D11BlendState* GetDefaultBlendState() { return m_pDefaultBlendState; }

private:
	ID3D11BlendState*	m_pDefaultBlendState;

};	// class BlendStateManager

}	// namespace sl

#endif	// SL_BLEND_STATE_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
