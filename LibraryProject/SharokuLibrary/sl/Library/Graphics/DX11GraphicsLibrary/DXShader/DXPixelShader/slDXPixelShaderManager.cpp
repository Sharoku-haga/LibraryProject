//==================================================================================================================================//
//!< @file		slDXPixelShaderManager.cpp
//!< @brief		sl::DXPixelShaderManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/03	更新履歴：2017/10/04
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDXPixelShaderManager.h"
#include "../../../../Utility/slTemplateFunction.h"
#include "../../../../Debugger/slDebugFunction.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DXPixelShaderManager::DXPixelShaderManager(ID3D11Device*	pDevice)
	: m_pDevice(pDevice)
{}

DXPixelShaderManager::~DXPixelShaderManager()
{
	ReleaseALL();
}

PixelShaderID DXPixelShaderManager::CreatePixelShader(const t_char* pFilePath, const t_char* pShaderFuncName)
{
	int shaderIDNum = INT_MAX;

	ID3DBlob* pCompiledShader = NULL;
	ID3DBlob* pErrors = NULL;
	if (FAILED(D3DX11CompileFromFile(
		pFilePath,
		NULL,
		NULL,
		pShaderFuncName,
		"ps_5_0",
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
		0,
		NULL,
		&pCompiledShader,
		&pErrors,
		NULL)))
	{
		t_char* pPath = const_cast<t_char*>(pFilePath);
		slOutputDebugString(pPath);
		slOutputDebugString("PixelShaderのコンパイルに失敗しました");
		pErrors->Release();
		return PixelShaderID(shaderIDNum);
	}

	ID3D11PixelShader* pPixelShader = NULL;
	HRESULT res = m_pDevice->CreatePixelShader(
				pCompiledShader->GetBufferPointer(), 
				pCompiledShader->GetBufferSize(), 
				NULL, 
				&pPixelShader);

	if(FAILED(res))
	{
		t_char* pPath = const_cast<t_char*>(pFilePath);
		slOutputDebugString(pPath);
		slOutputDebugString("\nPixelShaderのコンパイルに失敗しました");
		return PixelShaderID(shaderIDNum);
	}

	shaderIDNum = m_pPixelShader.size();
	m_pPixelShader.push_back(pPixelShader);
	
	// 終わったので解放
	pCompiledShader->Release();

	return PixelShaderID(shaderIDNum);
}

void DXPixelShaderManager::Release(const PixelShaderID& rID)
{
	SafeReleaseDX(m_pPixelShader[rID.m_Num]);
}

void DXPixelShaderManager::ReleaseALL(void)
{
	for(auto& pPixelShader : m_pPixelShader)
	{
		SafeReleaseDX(pPixelShader);
	}
	std::vector<ID3D11PixelShader*>().swap(m_pPixelShader);
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
