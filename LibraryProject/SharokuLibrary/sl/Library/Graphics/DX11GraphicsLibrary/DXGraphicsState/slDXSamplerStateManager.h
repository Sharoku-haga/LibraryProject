//==================================================================================================================================//
//!< @file		slDXSamplerStateManager.h
//!< @brief		sl::DXSamplerStateManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/01	更新履歴：
//==================================================================================================================================//

#ifndef SL_DX_SAMPLER_STATE_MANAGER_H
#define SL_DX_SAMPLER_STATE_MANAGER_H

#include <d3dx11.h>

namespace sl
{

/** @todo サンプラーステートをカスタムできる機能を追加したい */
//===================================================================================//
//!< サンプラーステートを管理するクラス
//===================================================================================//
class DXSamplerStateManager
{

public:
	/** Constructor */
	DXSamplerStateManager();

	/** Destructor */
	~DXSamplerStateManager();

	/**
	* デフォルトのサンプラーステートを生成する関数
	* @param[in] pDevice			DirectXのデバイス
	* @return ture→成功 false→失敗
	*/
	bool CreateDefaultSamplerState(ID3D11Device*	pDevice);

	/**
	* Getter
	* @return デフォルトのサンプラーステート
	*/
	inline ID3D11SamplerState* GetDefaultSamplerState() const { return m_pDefaultSamplerState; }

private:
	ID3D11SamplerState*				m_pDefaultSamplerState;			//!< デフォルトのサンプラーステート

};	// class DXSamplerStateManager

}	// namespace sl

#endif	// SL_DX_SAMPLER_STATE_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
