//==================================================================================================================================//
//!< @file		dx11Vertex2D.cpp
//!< @brief		dx11::Vertex2Dクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "../../../Common/slTemplate.h"
#include "dx11Vertex2D.h"

/* Namespace -------------------------------------------------------------------------------------------------- */

namespace sl
{
namespace dx11
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

//const D3DXCOLOR  DefaultColor = 0xffffffff;				// デフォルトのカラーの値
const D3DXCOLOR  DefaultColor = 0xffffffff;				// デフォルトのカラーの値(テスト用)

}


/* Static Variavle -------------------------------------------------------------------------------------------- */

const int							Vertex2D::m_VertexCount;

/* Public Functions ------------------------------------------------------------------------------------------- */

Vertex2D::Vertex2D(ID3D11Device* pDevice, ID3D11DeviceContext*	pDeviceContext)
	: m_pDevice(pDevice)
	, m_pDeviceContext(pDeviceContext)
	, m_pVertexBuffer(NULL)
{}
	
Vertex2D::~Vertex2D(void)
{
	ReleaseBuffer();
}

void Vertex2D::ReleaseBuffer()
{
	ReleaseSafely(m_pVertexBuffer);
}

bool Vertex2D::CreateNewBuffer(const fRect& rSize, const fRect& rUV)
{
	BasicVertex vertex[] = {
		{D3DXVECTOR3(   rSize.m_Left,	rSize.m_Top,  0.0f), DefaultColor, D3DXVECTOR2(  rUV.m_Left,	   rUV.m_Top)},
		{D3DXVECTOR3(  rSize.m_Right,	rSize.m_Top,  0.0f), DefaultColor, D3DXVECTOR2( rUV.m_Right,	   rUV.m_Top)},
		{D3DXVECTOR3(   rSize.m_Left, rSize.m_Bottom,  0.0f), DefaultColor, D3DXVECTOR2(  rUV.m_Left, rUV.m_Bottom)},
		{D3DXVECTOR3(  rSize.m_Right, rSize.m_Bottom,  0.0f), DefaultColor, D3DXVECTOR2( rUV.m_Right, rUV.m_Bottom)},
	};

	for(int i = 0; i < m_VertexCount; ++i)
	{
		m_Vertexs[i].m_Pos		= vertex[i].m_Pos;
		m_Vertexs[i].m_Color	= vertex[i].m_Color;
		m_Vertexs[i].m_UV		= vertex[i].m_UV;
	}

	return (CreateBuffer());
}

void Vertex2D::SetSize(fRect size)
{
	m_Vertexs[0].m_Pos = D3DXVECTOR3( size.m_Left, size.m_Top, 0.0f);
	m_Vertexs[1].m_Pos = D3DXVECTOR3( size.m_Right, size.m_Top, 0.0f);
	m_Vertexs[2].m_Pos = D3DXVECTOR3( size.m_Left, size.m_Bottom, 0.0f);
	m_Vertexs[3].m_Pos = D3DXVECTOR3( size.m_Right, size.m_Bottom, 0.0f);
}
void Vertex2D::SetUV(fRect uv)
{
	m_Vertexs[0].m_UV = D3DXVECTOR2( uv.m_Left, uv.m_Top);
	m_Vertexs[1].m_UV = D3DXVECTOR2( uv.m_Right, uv.m_Top);
	m_Vertexs[2].m_UV = D3DXVECTOR2( uv.m_Left, uv.m_Bottom);
	m_Vertexs[3].m_UV = D3DXVECTOR2( uv.m_Right, uv.m_Bottom);
}

void Vertex2D::SetColor(D3DXCOLOR color)
{
	m_Vertexs[3].m_Color = color;
	m_Vertexs[0].m_Color = color;
	m_Vertexs[1].m_Color = color;
	m_Vertexs[2].m_Color = color;
}

/* Private Functions ------------------------------------------------------------------------------------------ */

bool Vertex2D::CreateBuffer()
{
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
	bufferDesc.ByteWidth			= sizeof(BasicVertex) * m_VertexCount;				// バッファーのサイズ (バイト単位)
	bufferDesc.Usage				= D3D11_USAGE_DEFAULT;								// バッファーで想定されている読み込みおよび書き込みの方法
	bufferDesc.BindFlags			= D3D11_BIND_VERTEX_BUFFER;							// バッファーをどのようにパイプラインにバインドするかの識別
	bufferDesc.CPUAccessFlags		= 0;												// CPU アクセスのフラグ
	bufferDesc.MiscFlags			= 0;												// リソースに使用される、あまり一般的でないその他のオプションのフラグ
	bufferDesc.StructureByteStride	= 0;												// 構造体が構造化バッファーを表す場合のその構造体のサイズ 

	D3D11_SUBRESOURCE_DATA initVertexData;
	ZeroMemory(&initVertexData, sizeof(D3D11_SUBRESOURCE_DATA));
	initVertexData.pSysMem = m_Vertexs;

	if(FAILED(m_pDevice->CreateBuffer(&bufferDesc, &initVertexData, &m_pVertexBuffer)))
	{
		MessageBox(0, "頂点バッファの生成に失敗しました", NULL, MB_OK);				
		return false;
	}

	return true;
}

}	// namespace dx11
}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
