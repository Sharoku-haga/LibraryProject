//==================================================================================================================================//
//!< @file		slDXPixelShaderManager.h
//!< @brief		sl::DXPixelShaderManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/03	更新履歴：2017/10/04
//==================================================================================================================================//

#ifndef SL_DX_PIXEL_SHADER_MANAGER_H
#define SL_DX_PIXEL_SHADER_MANAGER_H

#include <d3dx11.h>
#include <vector>
#include "../../../../Utility/slTypes.h"
#include "../../../slGraphicsID.h"

namespace sl
{

//===================================================================================//
//!< DirectXのピクセルシェーダーを管理するクラス
//===================================================================================//
class DXPixelShaderManager
{

public:
	/** 
	* Constructor 
	* @param[in] pDevice DirectXのデバイス
	*/
	explicit DXPixelShaderManager(ID3D11Device*	pDevice);

	/** Destructor */
	~DXPixelShaderManager();

	/** 
	* ピクセルシェーダーを生成する関数
	* @param[in] pFilePath			シェーダーファイルへのパス
	* @param[in] pShaderFuncName	シェーダーの関数名
	* @return ピクセルシェーダーID
	*/
	PixelShaderID CreatePixelShader(const t_char* pFilePath, const t_char* pShaderFuncName);

	/**
	* 指定したピクセルシェーダーを取得する関数
	* @param[in] rID	取得したいピクセルID
	* @return 取得したいピクセルシェーダーへのポインタ
	*/
	inline ID3D11PixelShader* GetPixelShader(const PixelShaderID& rID) { return m_pPixelShader[rID.m_Num]; }

	/** 
	* 指定したピクセルシェーダーを解放する関数 
	* @param[in] rID 登録したピクセルシェーダーのID 
	*/
	void Release(const PixelShaderID& rID);

	/**  全てのピクセルシェーダーを解放する関数 */
	void ReleaseALL(void);

private:
	ID3D11Device*							m_pDevice;			//!< DirectXのデバイス
	std::vector<ID3D11PixelShader*>			m_pPixelShader;		//!< 生成したピクセルシェーダーを格納するvector

};	// class DXPixelShaderManager

}	// namespace sl

#endif	// SL_DX_PIXEL_SHADER_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
