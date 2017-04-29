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
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_IsEnd(false)
{}

App::~App(void)
{
	Finalize();
}

void App::Initialize()
{
	m_IDs.m_TexID = m_pLibrary->LoadTexture("rinne.png");
	//m_IDs.m_TexID = m_pLibrary->LoadTexture("BLUE.png");

	sl::fRect size = {0.0f, 0.0f, 300.f, 300.f};
	sl::fRect uv = {0.0f, 0.0f, 1.0f, 1.0f};

	m_IDs.m_VtxID= m_pLibrary->CreateVertex2D(size, uv);
}

void App::Finalize(void)
{
	m_pLibrary->ReleaseVertexALL();
	m_pLibrary->ReleaseTexALL();
}

bool App::Update(void)
{
	Control();

	m_pLibrary->StartRender();

	Draw();

	m_pLibrary->EndRender();

	return m_IsEnd;
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void App::Control(void)
{}

void App::Draw(void)
{
	m_pLibrary->Draw2D(m_IDs, sl::SLVECTOR2(0.0f,0.0f));
}

}	// namespace app

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
