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
	, m_Pos({0.0f, 0.0f})
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

	m_pLibrary->RegisterCustomizeType(UP, sl::GAMEPAD, sl::XIGAMEPAD_LSTICK_UP);
	m_pLibrary->RegisterCustomizeType(DOWN, sl::GAMEPAD, sl::XIGAMEPAD_LSTICK_DOWN);
	m_pLibrary->RegisterCustomizeType(RIGHT, sl::GAMEPAD, sl::XIGAMEPAD_LSTICK_RIGHT);
	m_pLibrary->RegisterCustomizeType(LEFT, sl::GAMEPAD, sl::XIGAMEPAD_LSTICK_LEFT);
	m_pLibrary->RegisterCustomizeType(ATTACK, sl::GAMEPAD, sl::XIGAMEPAD_A);
	m_pLibrary->RegisterCustomizeType(JUMP, sl::GAMEPAD, sl::XIGAMEPAD_B);
}

void App::Finalize(void)
{
	m_pLibrary->ReleaseVertexALL();
	m_pLibrary->ReleaseTexALL();
}

bool App::Update(void)
{
	m_pLibrary->UpdateInputDevice();

	Control();

	m_pLibrary->StartRender();

	Draw();

	m_pLibrary->EndRender();

	return m_IsEnd;
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void App::Control(void)
{
	if(m_pLibrary->CheckCustomizeState(RIGHT) == sl::ON)
	{
		m_Pos.x += 10.0f;
	}
	if(m_pLibrary->CheckCustomizeState(LEFT) == sl::ON)
	{
		m_Pos.x -= 10.0f;
	}
	if(m_pLibrary->CheckCustomizeState(UP) == sl::ON)
	{
		m_Pos.y -= 10.0f;
	}
	if(m_pLibrary->CheckCustomizeState(DOWN) == sl::ON)
	{
		m_Pos.y += 10.0f;
	}

	if(m_pLibrary->CheckCustomizeState(ATTACK) == sl::ON)
	{
		m_Pos.x += 10.0f;
	}
	if(m_pLibrary->CheckCustomizeState(JUMP) == sl::ON)
	{
		m_Pos.x -= 10.0f;
	}
}

void App::Draw(void)
{
	m_pLibrary->Draw2D(m_IDs, m_Pos);
}

}	// namespace app

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
