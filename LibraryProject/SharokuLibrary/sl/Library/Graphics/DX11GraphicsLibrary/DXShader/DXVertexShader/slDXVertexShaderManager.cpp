//==================================================================================================================================//
//!< @file		slDXVertexShaderManager.cpp		
//!< @brief		sl::DXVertexShaderManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/03	更新履歴：2017/10/06
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDXVertexShaderManager.h"
#include "../../../../Utility/slTemplateFunction.h"
#include "../../../../Debugger/slDebugFunction.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DXVertexShaderManager::DXVertexShaderManager(ID3D11Device*	pDevice)
	: m_pDevice(pDevice)
{}

DXVertexShaderManager::~DXVertexShaderManager()
{
	ReleaseALL();
}

VertexShaderID DXVertexShaderManager::CreateVertexShader(const t_char* pFilePath, const t_char* pShaderFuncName)
{
	int shaderIDNum = INT_MAX;

	ID3DBlob* pCompiledShader = NULL;
	ID3DBlob* pErrors = NULL;
	if (FAILED(D3DX11CompileFromFile(
		pFilePath,
		NULL,
		NULL,
		pShaderFuncName,
		"vs_5_0",
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
		0,
		NULL,
		&pCompiledShader,
		&pErrors,
		NULL)))
	{
		t_char* pPath = const_cast<t_char*>(pFilePath);
		slOutputDebugString(pPath);
		slOutputDebugString("VertexShaderのコンパイルに失敗しました");
		pErrors->Release();
		return VertexShaderID(shaderIDNum);
	}

	ID3D11VertexShader*	pVertexShader = NULL;
	HRESULT res = m_pDevice->CreateVertexShader(
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		NULL,
		&pVertexShader);

	if(FAILED(res))
	{
		t_char* pPath = const_cast<t_char*>(pFilePath);
		slOutputDebugString(pPath);
		slOutputDebugString("VertexShaderの生成に失敗しました");
		return VertexShaderID(shaderIDNum);
	}

	shaderIDNum = m_pVertexShader.size();
	m_pVertexShader.push_back(pVertexShader);

	// 終わったので解放
	pCompiledShader->Release();
	
	return VertexShaderID(shaderIDNum);
}


void DXVertexShaderManager::Release(const VertexShaderID & rID)
{
	SafeReleaseDX(m_pVertexShader[rID.m_Num]);
}

void DXVertexShaderManager::ReleaseALL(void)
{
	for(auto& pVertexShader : m_pVertexShader)
	{
		SafeReleaseDX(pVertexShader);
	}
	std::vector<ID3D11VertexShader*>().swap(m_pVertexShader);
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
