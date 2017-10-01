//==================================================================================================================================//
//!< @file		slDXVertexShaderManager.h		
//!< @brief		sl::DXVertexShaderManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/03	更新履歴：2017/10/04
//==================================================================================================================================//

#ifndef SL_DX_VERTEX_SHADER_MANAGER_H
#define SL_DX_VERTEX_SHADER_MANAGER_H

#include <d3dx11.h>
#include <vector>
#include "../../../../Utility/slTypes.h"
#include "../../../slGraphicsID.h"

namespace sl
{

//===================================================================================//
//!< DirectXのバーテックスシェーダーを管理するクラス
//===================================================================================//
class DXVertexShaderManager
{

public:
	/** 
	* Constructor 
	* @param[in] pDevice DirectXのデバイス
	*/
	explicit DXVertexShaderManager(ID3D11Device*	pDevice);

	/** Destructor */
	~DXVertexShaderManager();

	/** 
	* バーテックスシェーダーを生成する関数
	* @param[in] pFilePath			シェーダーファイルへのパス
	* @param[in] pShaderFuncName	シェーダー関数名
	* @return バーテックスシェーダーID
	*/
	VertexShaderID CreateVertexShader(const t_char* pFilePath, const t_char* pShaderFuncName);

	/**
	* 指定したバーテックスシェーダーを取得する関数
	* @param[in] rID	取得したいバーテックスシェーダーID
	* @return 取得したいバーテックスシェーダーへのポインタ
	*/
	inline ID3D11VertexShader* GetVertexShader(const VertexShaderID& rID) { return m_pVertexShader[rID.m_Num]; }

	/** 
	* 指定したバーテックスシェーダーを解放する関数 
	* @param[in] rID 登録したバーテックスシェーダーのID 
	*/
	void Release(const VertexShaderID & rID);

	/**  全てのバーテックスシェーダーを解放する関数 */
	void ReleaseALL(void);

private:
	ID3D11Device*						m_pDevice;					//!< DirectXのデバイス
	std::vector<ID3D11VertexShader*	>	m_pVertexShader;			//!< 生成したバーテックスシェーダーを格納するvector

};	// class DXVertexShaderManager

}	// namespace sl

#endif	// SL_DX_VERTEX_SHADER_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
