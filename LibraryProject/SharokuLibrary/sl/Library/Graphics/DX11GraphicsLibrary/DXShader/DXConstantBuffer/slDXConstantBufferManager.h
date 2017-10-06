//==================================================================================================================================//
//!< @file		slDXConstantBufferManager.h		
//!< @brief		sl::DXConstantBufferManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/04	更新履歴：
//==================================================================================================================================//

#ifndef SL_DX_CONSTANT_BUFFER_MANAGER_H
#define SL_DX_CONSTANT_BUFFER_MANAGER_H

#include <d3dx11.h>
#include <vector>
#include "../../../../Utility/slTypes.h"
#include "../../../slGraphicsID.h"

namespace sl
{

//===================================================================================//
//!< DirectXのコンスタントバッファーを管理するクラス
//===================================================================================//
class DXConstantBufferManager
{

public:
	/** 
	* Constructor 
	* @param[in] pDevice DirectXのデバイス
	*/
	DXConstantBufferManager(ID3D11Device*	pDevice);

	/** Destructor */
	~DXConstantBufferManager();

	/**
	* コンスタントバッファ生成関数
	* @param[in] constantBufferSize コンスタントバッファサイズ
	*/
	ConstantBufferID CreateConstantBuffer(unsigned int constantBufferSize);

	/**
	* 指定したコンスタントバッファーを取得する関数
	* @param[in] rID	取得したいコンスタントバッファ-のサイズ
	* @return 指定したコンスタントバッファー
	*/
	inline ID3D11Buffer* GetConstantBuffer(const ConstantBufferID& rID) { return m_pConstantBuffer[rID.m_Num]; }

	/**
	* 指定したコンスタントバッファーを解放する関数
	* @param[in] rID 解放したいコンスタントバッファーのID
	*/
	void Release(const ConstantBufferID& rID);

	/** 全てのコンスタントバッファーを解放する関数 */
	void ReleaseALL();

private:
	ID3D11Device*								m_pDevice;					//!< DirectXのデバイス
	std::vector<ID3D11Buffer*>					m_pConstantBuffer;			//!< コンスタントバッファを格納したvector

};	// class DXConstantBufferManager

}	// namespace sl

#endif	// SL_DX_CONSTANT_BUFFER_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
