//==================================================================================================================================//
//!< @file		slDX11Library.cpp
//!< @brief		slDX11Libraryクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDX11Library.h"
#include "Window/dx11Window/dx11Window.h"
#include "../Common/slTemplate.h"

/* Namespace -------------------------------------------------------------------------------------------------- */

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DX11Library::DX11Library(void)
	: m_pWindow(NULL)
{}

DX11Library::~DX11Library(void)
{
	Finalize();
}

void DX11Library::Initialize(t_char*  pWinTitle, int winWidth, int winHeight)
{
	m_pWindow = new dx11::Window();
	m_pWindow->Initialize(pWinTitle, winWidth, winHeight);
}

void DX11Library::Finalize(void)
{
	DeleteSafly(m_pWindow);
}

bool DX11Library::UpdateWindow(void)
{
	return m_pWindow->Update();
}

void DX11Library::ChangeWindowMode(bool isFullScreen)
{

}

void DX11Library::StartRender(void)
{

}

void DX11Library::EndRender(void)
{

}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
