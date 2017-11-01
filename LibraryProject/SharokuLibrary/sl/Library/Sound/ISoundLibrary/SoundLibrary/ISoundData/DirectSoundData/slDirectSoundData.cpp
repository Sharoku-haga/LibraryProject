//==================================================================================================================================//
//!< @file		slDirectSoundData.cpp
//!< @brief		sl::DirectSoundDataクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/31	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDirectSoundData.h"
#include "../../../../../Utility/slTemplateFunction.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DirectSoundData::DirectSoundData(LPDIRECTSOUNDBUFFER8	pSoundBuffer)
	: m_pSoundBuffer(pSoundBuffer)
{}

DirectSoundData::~DirectSoundData()
{
	SafeReleaseDX(m_pSoundBuffer);
}

void DirectSoundData::PlayBack(bool isLoop)
{
	if(isLoop)
	{
		m_pSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
	}
	else
	{
		m_pSoundBuffer->Play(0, 0, 0);
	}
}

void DirectSoundData::Stop()
{
	m_pSoundBuffer->Stop();
}

void DirectSoundData::Reset()
{
	m_pSoundBuffer->SetCurrentPosition(0);
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
