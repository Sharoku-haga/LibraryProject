//==================================================================================================================================//
//!< @file		App.cpp
//!< @brief		AppƒNƒ‰ƒXŽÀ‘•
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "App.h"

/* Namespace -------------------------------------------------------------------------------------------------- */

namespace app
{

/* Public Functions ------------------------------------------------------------------------------------------- */

App::App(void)
	: m_pGraphicsDevice(nullptr)
	, m_pTextureManager(nullptr)
	, m_pVertex2DManagaer(nullptr)
	, m_IsEnd(false)
	, m_TexID(INT_MAX)
	, m_VtxID(INT_MAX)
{}

App::~App(void)
{
	Finalize();
}

void App::Initialize(sl::dx11::GraphicsDevice* pGraphicsDevice)
{
	m_pGraphicsDevice = pGraphicsDevice;
	m_pTextureManager = new sl::dx11::TextureManager(m_pGraphicsDevice->GetDevice(), m_pGraphicsDevice->GetDeviceContext());
	m_TexID = m_pTextureManager->LoadTexture("rinne.png");
	//m_TexID = m_pTextureManager->LoadTexture("BLUE.png");

	m_pVertex2DManagaer = new sl::dx11::Vertex2DManager();
	if(!m_pVertex2DManagaer->Initialize(m_pGraphicsDevice))
	{
		return;
	}

	sl::fRect size = {0.0f, 0.0f, 300.f, 300.f};
	sl::fRect uv = {0.0f, 0.0f, 1.0f, 1.0f};

	m_VtxID = m_pVertex2DManagaer->CreateVertex(size, uv);
}

void App::Finalize(void)
{
	delete m_pVertex2DManagaer;
	delete m_pTextureManager;
}

bool App::Update(void)
{
	Control();

	m_pGraphicsDevice->StartRender();

	Draw();

	m_pGraphicsDevice->EndRender();

	return m_IsEnd;
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void App::Control(void)
{}

void App::Draw(void)
{
	m_pVertex2DManagaer->SetupShadar();
	m_pVertex2DManagaer->SetupConstantBuffer(D3DXVECTOR2(10.0f, 10.0f));
	m_pVertex2DManagaer->SetupBlendState();
	m_pTextureManager->SetUpTexture(m_TexID);

	UINT stride = sizeof(sl::dx11::BasicVertex);
	UINT offset = 0;
	ID3D11Buffer* pVertexBuffer = m_pVertex2DManagaer->GetBuffer(m_VtxID);
	m_pGraphicsDevice->GetDeviceContext()->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	m_pGraphicsDevice->GetDeviceContext()->Draw(4, 0);
}

}	// namespace app

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
