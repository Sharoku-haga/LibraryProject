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
#include "../../../Common/slTypes.h"
#include "../../../Common/slDefine.h"

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
	* @param[in] pDevice			デバイス
	* @param[in] pDeviceContext		デバイスコンテキスト
	*/
	TextureManager(ID3D11Device* pDevice, ID3D11DeviceContext*	pDeviceContext);

	/** Destructor */
	~TextureManager(void);

	/** 
	* テクスチャーを読み込む関数 
	* @param[in] pFileName テクスチャーのファイルネーム
	* @return 登録したID
	*/
	int LoadTexture(const t_char* pFileName);

	/**
	* 指定したテクスチャーをセットする関数
	* @param[in] id 登録したID
	*/
	void SetUpTexture(int id);

	/** 
	* 指定したテクスチャーを解放する関数 
	* @param[in] id 登録したテクスチャーのID 
	*/
	void Release(int id);

	/**  全てのテクスチャーを解放する関数 */
	void ReleaseALL(void);

private:
	ID3D11Device*											m_pDevice;					//!< Direct3Dのデバイス
	ID3D11DeviceContext*									m_pDeviceContext;			//!< デバイスコンテキスト
	ID3D11SamplerState*										m_pSamplerState;			//!< サンプラー
	std::vector<ID3D11ShaderResourceView*>					m_pTextureRV;				//!< テクスチャーのリソースヴュー

	/**
	 * サンプラステートの初期化関数
	 * @return 結果 true→成功 false→失敗
	 */
	bool InitSamplerState(void);

};

}	// namespace dx11
}	// namespace sl

#endif	// SL_DX11_TEXTURE_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
