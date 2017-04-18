//==================================================================================================================================//
//!< @file		dx11TextureManager.h
//!< @brief		dx11::TextureManagerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_DX11_TEXTURE_MANAGER_H
#define SL_DX11_TEXTURE_MANAGER_H

#include <windows.h>
//#include <d3dx10.h>
#include <d3dx11.h>
#include <vector>
#include "../../Common/slTypes.h"

namespace sl
{
namespace dx11
{

//======================================================================//
//!< DirectX11のTextureを管理するクラス
//======================================================================//
class TextureManager
{

public:
	/** 
	* Constructor
	* @param[in] pDevice デバイス
	*/
	TextureManager(ID3D11Device* pDevice);

	/** Destructor */
	~TextureManager(void);

	/** 
	* テクスチャーを読み込む関数 
	* @param[in] pFileName テクスチャーのファイルネーム
	* @return 登録したID
	*/
	int LoadTexture(const t_char* pFileName);

	/** 
	* 指定したテクスチャーを解放する関数 
	* @param[in] id 登録したテクスチャーのID 
	*/
	void Release(int id);

	/**  全てのテクスチャーを解放する関数 */
	void ReleaseALL(void);

private:
	ID3D11Device*											m_pDevice;					//!< Direct3Dのデバイス
	std::vector<ID3D11ShaderResourceView*>					m_pTextureRV;				//!< テクスチャーのリソースヴュー

};

}	// namespace dx11
}	// namespace sl

#endif	// SL_DX11_TEXTURE_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
