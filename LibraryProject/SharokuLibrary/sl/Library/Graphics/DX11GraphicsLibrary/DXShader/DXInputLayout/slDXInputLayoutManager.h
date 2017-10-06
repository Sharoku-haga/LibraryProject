//==================================================================================================================================//
//!< @file		slDXInputLayoutManager.h		
//!< @brief		sl::DXInputLayoutManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/04	更新履歴：
//==================================================================================================================================//

#ifndef SL_DX_INPUT_LAYOUT_MANAGER_H
#define SL_DX_INPUT_LAYOUT_MANAGER_H

#include <d3dx11.h>
#include <vector>
#include "../../../../Utility/slTypes.h"
#include "../../../slGraphicsID.h"

namespace sl
{

//===================================================================================//
//!< DirectXの入力頂点レイアウトを管理するクラス
//===================================================================================//
class DXInputLayoutManager
{

public:
	/** 
	* Constructor 
	* @param[in] pDevice DirectXのデバイス
	*/
	explicit DXInputLayoutManager(ID3D11Device*	pDevice);

	/** Destructor */
	~DXInputLayoutManager();

	/** 
	* 入力頂点レイアウトを生成する関数
	* @param[in] pVertexShaderFilePath	バーテックスシェーダーファイルへのパス
	* @param[in] pVertexShaderFuncName	バーテックスシェーダーの関数名
	* @param[in] pInputElementDesc		入力頂点レイアウト構成を格納した配列の先頭ポインタ
	* @param[in] elementDescSize		入力頂点レイアウト構成を格納した配列のサイズ
	* @return 入力頂点レイアウトのID
	*/
	InputLayoutID CreateInputLayout(const t_char* pVertexShaderFilePath
								, const t_char* pVertexShaderFuncName
								, D3D11_INPUT_ELEMENT_DESC* pInputElementDesc
								, unsigned int elementDescSize);

	/**
	* 指定した入力頂点レイアウトを取得する関数
	* @param[in] rID	取得したい入力頂点レイアウトID
	* @return 取得したい入力頂点レイアウトへのポインタ
	*/
	inline ID3D11InputLayout* GetInputLayout(const InputLayoutID& rID) { return m_pInputLayout[rID.m_Num]; }

	/** 
	* 指定した入力頂点レイアウトを解放する関数 
	* @param[in] rID 登録した入力頂点レイアウトのID 
	*/
	void Release(const InputLayoutID & rID);

	/**  全ての入力頂点レイアウトを解放する関数 */
	void ReleaseALL(void);

private:
	ID3D11Device*						m_pDevice;					//!< DirectXのデバイス
	std::vector<ID3D11InputLayout*>		m_pInputLayout;				//!< 生成した入力頂点レイアウトを格納するvector

};	// class DXInputLayoutManager

}	// namespace sl

#endif	// SL_DX_INPUT_LAYOUT_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
