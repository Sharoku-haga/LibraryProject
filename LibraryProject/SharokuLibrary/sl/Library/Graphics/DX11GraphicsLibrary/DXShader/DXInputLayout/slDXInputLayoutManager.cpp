//==================================================================================================================================//
//!< @file		slDXInputLayoutManager.cpp		
//!< @brief		sl::DXInputLayoutManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/04	更新履歴：2017/10/06
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDXInputLayoutManager.h"
#include "../../../../Utility/slTemplateFunction.h"
#include "../../../../Debugger/slDebugFunction.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DXInputLayoutManager::DXInputLayoutManager(ID3D11Device* pDevice)
	: m_pDevice(pDevice)
{}

DXInputLayoutManager::~DXInputLayoutManager()
{
	ReleaseALL();
}

InputLayoutID DXInputLayoutManager::CreateInputLayout(const t_char* pVertexShaderFilePath
													, const t_char* pVertexShaderFuncName
													, D3D11_INPUT_ELEMENT_DESC* pInputElementDesc
													, unsigned int elementDescSize)
{
	int layoutIDNum = INT_MAX;

	ID3DBlob* pCompiledShader = NULL;
	ID3DBlob* pErrors = NULL;
	if (FAILED(D3DX11CompileFromFile(
		pVertexShaderFilePath,
		NULL,
		NULL,
		pVertexShaderFuncName,
		"vs_5_0",
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
		0,
		NULL,
		&pCompiledShader,
		&pErrors,
		NULL)))
	{
		t_char* pPath = const_cast<t_char*>(pVertexShaderFilePath);
		slOutputDebugString(pPath);
		slOutputDebugString("頂点レイアウトの為のVertexShaderのコンパイルに失敗しました");
		pErrors->Release();
		return InputLayoutID(layoutIDNum);
	}

	ID3D11InputLayout* pInputLayout = NULL;
	HRESULT res = m_pDevice->CreateInputLayout(
		pInputElementDesc,
		elementDescSize,
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		&pInputLayout);

	if(FAILED(res))
	{
		t_char* pPath = const_cast<t_char*>(pVertexShaderFilePath);
		slOutputDebugString(pPath);
		slOutputDebugString("\n頂点レイアウトの為のVertexShaderのコンパイルに失敗しました");
		return InputLayoutID(layoutIDNum);
	}

	layoutIDNum = m_pInputLayout.size();
	m_pInputLayout.push_back(pInputLayout);

	// 終わったので解放
	pCompiledShader->Release();
	
	return InputLayoutID(layoutIDNum);
}

void DXInputLayoutManager::Release(const InputLayoutID & rID)
{
	SafeReleaseDX(m_pInputLayout[rID.m_Num]);
}

void DXInputLayoutManager::ReleaseALL(void)
{
	for(auto& pInputLayout : m_pInputLayout)
	{
		SafeReleaseDX(pInputLayout);
	}
	std::vector<ID3D11InputLayout*>().swap(m_pInputLayout);
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
