//==================================================================================================================================//
//!< @file		slDXTextureManager.h		
//!< @brief		sl::DXTextureManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/01	更新履歴：
//==================================================================================================================================//

#ifndef SL_DX_TEXTURE_MANAGER_H
#define SL_DX_TEXTURE_MANAGER_H

#include <d3dx11.h>
#include <vector>
#include "../../../Utility/slTypes.h"
#include "../../slGraphicsID.h"

namespace sl
{

//===================================================================================//
//!< DirectXのテクスチャーを管理するクラス
//===================================================================================//
class DXTextureManager
{

public:
	/** 
	* Contructor 
	* @param[in] pDevice DirectXのデバイス
	*/
	explicit DXTextureManager(ID3D11Device* pDevice);

	/** Destructor */
	~DXTextureManager();

	/** 
	* テクスチャーを読み込む関数 
	* @param[in] pFileName テクスチャーのファイル名
	* @return 登録したID
	*/
	TextureID LoadTexture(const t_char* pFileName);

	/**
	* 指定したテクスチャーへのポインタを取得する関数
	* @param[in] rID	テクスチャーのID
	* @return 指定したテクスチャーへのポインタ
	*/
	ID3D11ShaderResourceView* GetTextureRV(const TextureID& rID) { return m_pTextureRV[rID.m_Num]; }

	/** 
	* 指定したテクスチャーを解放する関数 
	* @param[in] rID 登録したテクスチャーのID 
	*/
	void Release(const TextureID& rID);

	/**  全てのテクスチャーを解放する関数 */
	void ReleaseALL(void);

private:
	ID3D11Device*											m_pDevice;					//!< Direct3Dのデバイス
	std::vector<ID3D11ShaderResourceView*>					m_pTextureRV;				//!< テクスチャーのリソースヴューを格納しているvector

};	// class DXTextureManager

}	// namespace sl

#endif	// SL_DX_TEXTURE_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
