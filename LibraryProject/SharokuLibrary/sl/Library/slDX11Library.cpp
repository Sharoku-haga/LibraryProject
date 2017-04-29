//==================================================================================================================================//
//!< @file		slDX11Library.cpp
//!< @brief		slDX11Libraryクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDX11Library.h"
#include "Window/dx11Window/dx11Window.h"
#include "Graphics/dx11GraphicsDevice/dx11GraphicsDevice.h"
#include "Texture/dx11Texture/dx11TextureManager.h"
#include "Vertex/dx11Vertex/dx11Vertex2DManager.h"
#include "../Common/slTemplate.h"

/* Namespace -------------------------------------------------------------------------------------------------- */

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DX11Library::DX11Library(void)
	: m_pWindow(nullptr)
	, m_pGraphicsDevice(nullptr)
	, m_pTextureManager(nullptr)
	, m_pVertex2DManager(nullptr)
{}

DX11Library::~DX11Library(void)
{
	Finalize();
}

void DX11Library::Initialize(t_char*  pWinTitle, int winWidth, int winHeight)
{
	m_pWindow = new dx11::Window();
	m_pWindow->Initialize(pWinTitle, winWidth, winHeight);

	m_pGraphicsDevice = new dx11::GraphicsDevice();
	m_pGraphicsDevice->Initialize(m_pWindow->GetHwnd());

	m_pTextureManager = new dx11::TextureManager(m_pGraphicsDevice->GetDevice(), m_pGraphicsDevice->GetDeviceContext());

	m_pVertex2DManager = new dx11::Vertex2DManager();
	m_pVertex2DManager->Initialize(m_pGraphicsDevice);
}

void DX11Library::Finalize(void)
{
	DeleteSafly(m_pVertex2DManager);
	DeleteSafly(m_pTextureManager);
	DeleteSafly(m_pGraphicsDevice);
	DeleteSafly(m_pWindow);
}

bool DX11Library::UpdateWindow(void)
{
	return m_pWindow->Update();
}

void DX11Library::ChangeWindowMode(bool isFullScreen)
{
	m_pGraphicsDevice->ChangeWindowMode(isFullScreen);
}

int DX11Library::LoadTexture(const t_char* pFileName)
{
	return m_pTextureManager->LoadTexture(pFileName);
}

void DX11Library::ReleaseTex(int texID)
{
	m_pTextureManager->Release(texID);
}

void DX11Library::ReleaseTexALL(void)
{
	m_pTextureManager->ReleaseALL();
}

int DX11Library::CreateVertex2D(const fRect& rSize, const fRect& rUV)
{
	return m_pVertex2DManager->CreateVertex(rSize, rUV);
}

void DX11Library::ReleaseVertex2D(int vtxID)
{
	m_pVertex2DManager->ReleaseVertex2D(vtxID);
}

void DX11Library::ReleaseVertexALL(void)
{
	m_pVertex2DManager->ReleaseALL();
}

void DX11Library::StartRender(void)
{
	m_pGraphicsDevice->StartRender();
}

void DX11Library::EndRender(void)
{
	m_pGraphicsDevice->EndRender();
}

void DX11Library::Draw2D(GraphicsIDs ids, SLVECTOR2 pos, SLVECTOR3 scale, float angle)
{
	m_pVertex2DManager->SetupShadar();
	m_pVertex2DManager->SetupConstantBuffer(D3DXVECTOR2(pos.x, pos.y), D3DXVECTOR3(scale.x, scale.y, scale.z), angle);
	m_pVertex2DManager->SetupBlendState();
	m_pTextureManager->SetUpTexture(ids.m_TexID);
	UINT stride = sizeof(sl::dx11::BasicVertex);
	UINT offset = 0;
	ID3D11Buffer* pVertexBuffer = m_pVertex2DManager->GetBuffer(ids.m_VtxID);
	m_pGraphicsDevice->GetDeviceContext()->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	m_pGraphicsDevice->GetDeviceContext()->Draw(m_pVertex2DManager->GetVertexCount(), 0);
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
