//==================================================================================================================================//
//!< @file		dx11Vertex2DManager.cpp
//!< @brief		dx11::Vertex2DManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "../../../Common/slTemplate.h"
#include "dx11Vertex2DManager.h"

/* Namespace -------------------------------------------------------------------------------------------------- */

namespace sl
{
namespace dx11
{

/* Static Variable -------------------------------------------------------------------------------------------- */

const int	Vertex2DManager::m_VertexCount;

/* Public Functions ------------------------------------------------------------------------------------------- */

Vertex2DManager::Vertex2DManager()
	: m_pDevice(NULL)
	, m_pDeviceContext(NULL)
	, m_hWnd(NULL)
	, m_pVertexShader(NULL)
	, m_pVertexCompiledShader(NULL)
	, m_pVertexLayout(NULL)
	, m_pPixelShader(NULL)
	, m_pBlendState(NULL)
	, m_pConstantBuffer(NULL)
{}

Vertex2DManager::~Vertex2DManager()
{
	Finalize();
}

bool Vertex2DManager::Initialize(GraphicsDevice* pGraphicsDevice)
{
	m_pDevice = pGraphicsDevice->GetDevice();
	m_pDeviceContext = pGraphicsDevice->GetDeviceContext();
	m_hWnd = pGraphicsDevice->GetHWnd();

	RECT clientRect;
	GetClientRect(m_hWnd, &clientRect);
	m_ClientWidth	= static_cast<float>(clientRect.right);
	m_ClientHeight	= static_cast<float>(clientRect.bottom);

	if(RESULT_FAILED(InitVertexShader()))
	{
		return false;
	}

	if(RESULT_FAILED(InitVertexLayout()))
	{
		ReleaseSafely(m_pVertexCompiledShader);
		ReleaseSafely(m_pVertexShader);
		return false;
	}

	if(RESULT_FAILED(InitPixelShader()))
	{
		ReleaseSafely(m_pVertexLayout);
		ReleaseSafely(m_pVertexCompiledShader);
		ReleaseSafely(m_pVertexShader);
		return false;
	}

	if(RESULT_FAILED(InitBlendState()))
	{
		ReleaseSafely(m_pPixelShader);
		ReleaseSafely(m_pVertexLayout);
		ReleaseSafely(m_pVertexCompiledShader);
		ReleaseSafely(m_pVertexShader);
		return false;
	}

	if(RESULT_FAILED(InitConstantBuffer()))
	{
		ReleaseSafely(m_pBlendState);
		ReleaseSafely(m_pPixelShader);
		ReleaseSafely(m_pVertexLayout);
		ReleaseSafely(m_pVertexCompiledShader);
		ReleaseSafely(m_pVertexShader);
		return false;
	}

	return true;
}

void Vertex2DManager::Finalize(void)
{
	ReleaseALL();
	ReleaseSafely(m_pConstantBuffer);
	ReleaseSafely(m_pBlendState);
	ReleaseSafely(m_pPixelShader);
	ReleaseSafely(m_pVertexLayout);
	ReleaseSafely(m_pVertexCompiledShader);
	ReleaseSafely(m_pVertexShader);
}

int Vertex2DManager::CreateVertex(const fRect& rSize, const fRect& rUV)
{
	int id = INT_MAX;

	Vertex2D* pVeretex2D = NULL;

	pVeretex2D = new Vertex2D(m_pDevice, m_pDeviceContext);
	
	if(RESULT_FAILED(pVeretex2D->CreateNewBuffer(rSize, rUV)))
	{
		delete pVeretex2D;
		return INT_MAX;
	}

	id = m_Vertex2Ds.size();
	m_Vertex2Ds.push_back(pVeretex2D);

	return id;
}

void Vertex2DManager::ReleaseVertex2D(int id)
{
	delete m_Vertex2Ds[id];
	m_Vertex2Ds[id] = NULL;
	m_Vertex2Ds.erase((m_Vertex2Ds.begin() + id));
}

void Vertex2DManager::ReleaseALL(void)
{
	for(auto& vtx2D : m_Vertex2Ds)
	{
		if(vtx2D != NULL)
		{
			delete vtx2D;
			vtx2D = NULL;
		}
	}
	std::vector<Vertex2D*>().swap(m_Vertex2Ds);
}

void Vertex2DManager::SetupShadar(void)
{
	m_pDeviceContext->VSSetShader( m_pVertexShader, NULL, 0);
	m_pDeviceContext->PSSetShader( m_pPixelShader, NULL, 0);
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

void Vertex2DManager::SetupBlendState(void)
{
	m_pDeviceContext->OMSetBlendState(m_pBlendState, NULL, 0xffffffff);
}

void Vertex2DManager::SetupConstantBuffer(const D3DXVECTOR2& pos, const D3DXVECTOR3& scale, float angle)
{
	D3DXMATRIX matWorld, matTranslate,matRotate;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matWorld, scale.x, scale.y, 1.0f);
	D3DXMatrixRotationZ(&matRotate, angle);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matRotate);
	D3DXMatrixTranslation(&matTranslate, pos.x, pos.y, 0);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matTranslate);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	SHADER_CONSTANT_BUFFER constantBuffer;
	if (SUCCEEDED(m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource)))
	{
		constantBuffer.m_MatWorld = matWorld;
		D3DXMatrixTranspose(&constantBuffer.m_MatWorld, &constantBuffer.m_MatWorld);

		constantBuffer.m_WindowSize.x = m_ClientWidth;
		constantBuffer.m_WindowSize.y = m_ClientHeight;
	
		memcpy_s(mappedResource.pData, mappedResource.RowPitch, reinterpret_cast<void*>(&constantBuffer), sizeof(constantBuffer));
		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);
	}
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext->IASetInputLayout(m_pVertexLayout);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

bool Vertex2DManager::InitVertexShader(void)
{
	ID3DBlob* pErrors = NULL;
	if (FAILED(D3DX11CompileFromFile(
		TEXT("../SharokuLibrary/sl/Library/Vertex/dx11Vertex/dx11CommonHLSL/dx11CommonVS.hlsl"),
		NULL,
		NULL,
		"VS",
		"vs_5_0",
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
		0,
		NULL,
		&m_pVertexCompiledShader,
		&pErrors,
		NULL)))
	{
		MessageBox(0, "VertexShaderのコンパイルに失敗しました", NULL, MB_OK);
		pErrors->Release();
		return false;
	}

	m_pDevice->CreateVertexShader(
		m_pVertexCompiledShader->GetBufferPointer(),
		m_pVertexCompiledShader->GetBufferSize(),
		NULL,
		&m_pVertexShader);

	return true;
}

bool Vertex2DManager::InitVertexLayout(void)
{
	D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,						D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, sizeof(D3DXVECTOR3),						D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, sizeof(D3DXVECTOR3) + sizeof(D3DXCOLOR),		D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	if (FAILED(m_pDevice->CreateInputLayout(
		InputElementDesc,
		sizeof(InputElementDesc) / sizeof(InputElementDesc[0]),
		m_pVertexCompiledShader->GetBufferPointer(),
		m_pVertexCompiledShader->GetBufferSize(),
		&m_pVertexLayout)))
	{
		MessageBox(0, "頂点レイアウトの作成に失敗しました", NULL, MB_OK);
		return false;
	}

	return true;
}

bool Vertex2DManager::InitPixelShader(void)
{
	ID3DBlob* pCompiledShader = NULL;
	ID3DBlob* pErrors = NULL;
	if (FAILED(D3DX11CompileFromFile(
		TEXT("../SharokuLibrary/sl/Library/Vertex/dx11Vertex/dx11CommonHLSL/dx11CommonPS.hlsl"),
		NULL,
		NULL,
		"PS",
		"ps_5_0",
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
		0,
		NULL,
		&pCompiledShader,
		&pErrors,
		NULL)))
	{
		MessageBox(0, "PixelShaderのコンパイルに失敗しました", NULL, MB_OK);
		pErrors->Release();
		return false;
	}

	m_pDevice->CreatePixelShader(
		pCompiledShader->GetBufferPointer(), 
		pCompiledShader->GetBufferSize(), 
		NULL, 
		&m_pPixelShader);
	
	pCompiledShader->Release();

	return true;
}

bool Vertex2DManager::InitBlendState(void)
{
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
	blendDesc.AlphaToCoverageEnable					= false;							// アルファトゥカバレッジをマルチサンプリング テクニックとして使用の有無。現在は無効
	blendDesc.IndependentBlendEnable				= false;							// 同時処理のレンダー ターゲットで独立したブレンディング→TRUE, RenderTarget[0] のメンバーのみが使用→false
	blendDesc.RenderTarget[0].BlendEnable			= false;								// ブレンディングの有無. 現在は設定は有効
	blendDesc.RenderTarget[0].SrcBlend				= D3D11_BLEND_SRC_ALPHA;			// 最初のRGBデータソースを指定
	blendDesc.RenderTarget[0].DestBlend				= D3D11_BLEND_INV_SRC_ALPHA;		// 2番目のRGBデータソースを指定
	blendDesc.RenderTarget[0].BlendOp				= D3D11_BLEND_OP_ADD;				// RGBデータソースの組合せ方法
	blendDesc.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND_ONE;					// 最初のアルファデータソースを指定
	blendDesc.RenderTarget[0].DestBlendAlpha		= D3D11_BLEND_ZERO;					// 2 番目のアルファ データソースを指定
	blendDesc.RenderTarget[0].BlendOpAlpha			= D3D11_BLEND_OP_ADD;				// アルファデータソースの組み合わせ方法. 現在設定は加算
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;		// 書き込みマスク

	if (FAILED(m_pDevice->CreateBlendState(&blendDesc, &m_pBlendState)))
	{
		MessageBox(0, "BlendStateに失敗しました", NULL, MB_OK);
		return false;
	}

	return true;
}

bool Vertex2DManager::InitConstantBuffer(void)
{
	D3D11_BUFFER_DESC ConstantBufferDesc;
	ZeroMemory(&ConstantBufferDesc, sizeof(D3D11_BUFFER_DESC));
	ConstantBufferDesc.ByteWidth			= sizeof(SHADER_CONSTANT_BUFFER);
	ConstantBufferDesc.Usage				= D3D11_USAGE_DYNAMIC;
	ConstantBufferDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
	ConstantBufferDesc.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
	ConstantBufferDesc.MiscFlags			= 0;
	ConstantBufferDesc.StructureByteStride	= 0;

	if (FAILED(m_pDevice->CreateBuffer(&ConstantBufferDesc, NULL, &m_pConstantBuffer)))
	{
		MessageBox(0, "ConstantBufferの生成に失敗しました", NULL, MB_OK);
		return false;
	}

	return true;
}

}	// namespace dx11
}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
