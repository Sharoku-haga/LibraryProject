//==================================================================================================================================//
//!< @file		dx11ShaderManager.h
//!< @brief		dx11::ShaderManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "dx11ShaderManager.h"
#include "../../slBuild.h"
#include "../../Common/slTemplate.h"

/* Namespace -------------------------------------------------------------------------------------------------- */

namespace sl
{
namespace dx11
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

#ifdef SHADER_VERSION_5_0
const LPCSTR VertexShaderVersion		= "vs_5_0";
const LPCSTR PixelShaderVersion			= "ps_5_0";
#elif SHADER_VERSION_4_0
const LPCSTR VertexShaderVersion		= "vs_4_0";
const LPCSTR PixelShaderVersion			= "ps_4_0";
#endif

}

/* Public Functions ------------------------------------------------------------------------------------------- */

ShaderManager::ShaderManager(void)
	: m_pDevice(NULL)
{
	// 読み込みに失敗した際に参照する値としてNULLを追加
	m_pVertexShaders.push_back(NULL);
	m_pPixelShaders.push_back(NULL);
}

ShaderManager::~ShaderManager(void)
{
	Finalize();
}

bool ShaderManager::Initialize(ID3D11Device* pDevice)
{
	if(pDevice == NULL)
	{
		MessageBox(0, "渡されたDeviceは存在しません。", NULL, MB_OK);
		return false;
	}
	else
	{
		m_pDevice = pDevice;
	}

	return true;
}

void ShaderManager::Finalize(void)
{
	ReleaseVertexShader();
	ReleasePixelShader();
}

int ShaderManager::LoadVertexShader(const char* pFileName, const char* pFuncName)
{
	// hlslファイル読み込み ブロブ作成 
	ID3DBlob*	pCompiledShader = NULL;
	ID3DBlob*	pErrors			= NULL;

	// ブロブからシェーダーファイルを読み込み.
	if(FAILED(D3DX11CompileFromFile(
		pFileName, 
		NULL, 
		NULL, 
		pFuncName, 
		VertexShaderVersion, 
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, 
		0, 
		NULL, 
		&pCompiledShader, 
		&pErrors, 
		NULL)))
	{
		ReleaseSafely(pErrors);
		MessageBox(0, "シェーダーファイル読み込み失敗", NULL, MB_OK);
		return INT_MAX;
	}

	ReleaseSafely(pErrors);			// 参照カウンタを減らす

	ID3D11VertexShader* pVertexShader = NULL;

	if(FAILED(m_pDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &pVertexShader)))
	{
		ReleaseSafely(pCompiledShader);
		MessageBox(0, "バーテックスシェーダーの作成に失敗", NULL, MB_OK);
		return INT_MAX;
	}

	ReleaseSafely(pCompiledShader);

	int index = 0;
	index = m_pVertexShaders.size();
	m_pVertexShaders.push_back(pVertexShader);
	return index;
}

int ShaderManager::LoadPixelShader(const char* pFileName, const char* pFuncName)
{
	// hlslファイル読み込み ブロブ作成 
	ID3DBlob*	pCompiledShader = NULL;
	ID3DBlob*	pErrors			= NULL;

	// ブロブからシェーダーファイルを読み込み.
	if(FAILED(D3DX11CompileFromFile(
		pFileName,
		NULL,
		NULL,
		pFuncName,
		PixelShaderVersion,
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
		0,
		NULL,
		&pCompiledShader,
		&pErrors,
		NULL)))
	{
		ReleaseSafely(pErrors);
		MessageBox(0, "シェーダーファイル読み込み失敗", NULL, MB_OK);
		return INT_MAX;
	}

	ReleaseSafely(pErrors);

	ID3D11PixelShader*	pPixelShader = NULL;

	if(FAILED(m_pDevice->CreatePixelShader(
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		NULL,
		&pPixelShader)))
	{
		ReleaseSafely(pCompiledShader);
		MessageBox(0, "ピクセルシェーダーの作成に失敗", NULL, MB_OK);
		return INT_MAX;
	}

	ReleaseSafely(pCompiledShader);

	int index = 0;
	index = m_pPixelShaders.size();
	m_pPixelShaders.push_back(pPixelShader);
	return index;
}

void ShaderManager::ReleaseVertexShader(int index)
{
	if(m_pVertexShaders[index] != NULL)
	{
		m_pVertexShaders[index]->Release();
		m_pVertexShaders[index] = NULL;
		m_pVertexShaders.erase(m_pVertexShaders.begin() + index);
	}
}

void ShaderManager::ReleasePixelShader(int index)
{
	if(m_pPixelShaders[index] != NULL)
	{
		m_pPixelShaders[index]->Release();
		m_pPixelShaders[index] = NULL;
		m_pPixelShaders.erase(m_pPixelShaders.begin() + index);
	}
}

void ShaderManager::ReleaseVertexShader(void)
{
	for(auto& itr : m_pVertexShaders)
	{
		itr->Release();
		itr = NULL;
	}
	std::vector<ID3D11VertexShader*>().swap(m_pVertexShaders);
}

void ShaderManager::ReleasePixelShader(void)
{
	for(auto& itr : m_pPixelShaders)
	{
		itr->Release();
		itr = NULL;
	}
	std::vector<ID3D11PixelShader*>().swap(m_pPixelShaders);
}

}	// namespace dx11
}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
