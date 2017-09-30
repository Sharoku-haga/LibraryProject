//==================================================================================================================================//
//!< @file		slDXBlendStateManager.h
//!< @brief		sl::DXBlendStateManagerクラスのヘッダ
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
class DXBlendStateManager
{

public:
	/** Constructor */
	DXBlendStateManager();

	/** Destructor */
	~DXBlendStateManager();

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
	inline ID3D11BlendState* GetDefaultBlendState() const{ return m_pDefaultBlendState; }

private:
	ID3D11BlendState*	m_pDefaultBlendState;

};	// class DXBlendStateManager

}	// namespace sl

#endif	// SL_BLEND_STATE_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
