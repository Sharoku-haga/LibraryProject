//==================================================================================================================================//
//!< @file		dx11ShaderManager.h
//!< @brief		dx11::ShaderManagerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef DX11_SHADER_MANAGER_H
#define DX11_SHADER_MANAGER_H

#include <d3dx11.h>
#include <vector>
#include "../../../Common/slDefine.h"

namespace sl
{
namespace dx11
{

//======================================================================//
//!< DirectX11のShader関連を管理するクラス
//======================================================================//
class ShaderManager
{

public:
	/** Constructor */
	ShaderManager(void);

	/** Destructor */
	~ShaderManager(void);

	/** コピー禁止 */
	SL_DISALLOW_COPY_AND_ASSIGN(ShaderManager);

	/**
	* 初期化関数 
	* @param[in] pDevice Direct3Dのデバイス
	*/
	bool Initialize(ID3D11Device* pDevice);

	/** 破棄関数 */
	void Finalize(void);

	/** 
	* 頂点シェーダーを読み込む関数
	* @param[in] pFileName シェーダファイル名
	* @param[in] pFuncName 関数名
	* @return インデックス番号
	* @attention 読み込みが失敗したらINT_MAXがかえってくる
	*/
	int LoadVertexShader(const char* pFileName, const char* pFuncName);

	/**
	* ピクセルシェーダーを読み込む関数
	* @param[in] pFileName シェーダファイル名
	* @param[in] pFuncName 関数名
	* @return インデックス番号
	* @attention 読み込みが失敗したらINT_MAXがかえってくる
	*/
	int LoadPixelShader(const char* pFileName, const char* pFuncName);

	/**
	* 頂点シェーダーとそのコンパイルデータを解放する
	* @param[in] index 解放する頂点シェーダーのインデックス
	*/
	void ReleaseVertexShader(int index);

	/**
	* ピクセルシェーダーとそのコンパイルデータを解放する
	* @param[in] index 解放するピクセルシェーダーのインデックス
	*/
	void ReleasePixelShader(int index);

	/** 頂点シェーダーとそのコンパイルデータを全て解放する */
	void ReleaseVertexShader(void);

	/** ピクセルシェーダーとそのコンパイルデータを全て解放する */
	void ReleasePixelShader(void);

private:
	ID3D11Device*								m_pDevice;					//!< Direct3Dのデバイス
	std::vector<ID3D11VertexShader*>			m_pVertexShaders;			//!< バーテックスシェーダー
	std::vector<ID3D11PixelShader*>				m_pPixelShaders;			//!< ピクセルシェーダー
	

};	// class ShaderManager

}	// namespace dx11
}	// namespace sl

#endif	// DX11_SHADER_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
