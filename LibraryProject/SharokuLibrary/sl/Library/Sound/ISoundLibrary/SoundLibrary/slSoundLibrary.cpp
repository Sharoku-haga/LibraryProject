//==================================================================================================================================//
//!< @file		slSoundLibrary.cpp
//!< @brief		sl::SoundLibraryクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/31	更新履歴：2017/11/01
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slSoundLibrary.h"
#include "../../../../slBuild.h"
#include "../../../Debugger/slDebugFunction.h"
#include "../../../Utility/slTemplateFunction.h"
#include "../../../SmartPointer/slSmartPointer.h"
#include "SoundDataStorage/slSoundDataStorage.h"
#include "ISoundDevice/slISoundDevice.h"
#include "ISoundDevice/DirectSoundDevice/slDirectSoundDevice.h"
#include "ISoundData/slISoundData.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

SoundLibrary::SoundLibrary()
	: m_pDevice(NULL)
	, m_pStorage(NULL)
{}

SoundLibrary::~SoundLibrary()
{
	SafeDelete(m_pStorage);
	SafeDelete(m_pDevice);
}

bool SoundLibrary::Initialize(const WindowHandle& handle)
{
	
#ifdef DIRECT_SOUND
#ifdef X_AUDIO
	slOutputDebugString("サウンドデバイスは重複しています。slBuild.hの設定を確認してください");
	return false;
#endif	// X_AUDIO
	m_pDevice = new DirectSoundDevice(handle);
	if(RESULT_FALSE(m_pDevice->Initlialize()))
	{
		slOutputDebugString("DirectSoundデバイス初期化に失敗");
		SafeDelete(m_pDevice);
		return false;
	}

#endif // DIRECT_SOUND

#ifdef X_AUDIO
	// XAudioデバイス処理をここに作成
#endif	// X_AUDIO

	// データ保管場所の生成
	m_pStorage = new SoundDataStorage();
	return true;
}

SOUND_DATA_ID SoundLibrary::CreateSoundData(t_char* pFileName)
{
	UniquePtr<ISoundData> pData;

	if(RESULT_FALSE(m_pDevice->CreateSoundData(pFileName, pData)))
	{
		SOUND_DATA_ID id;
		id = ERROR_ID_NUMBER;
		return id;
	}

	return m_pStorage->AddSoundData(pData.Release());
}

void SoundLibrary::PlaybackSound(const SOUND_DATA_ID& rID, const PLAYBACK_MODE& rMode)
{
	ISoundData*	pData = m_pStorage->GetSoundData(rID);
	switch(rMode)
	{

	case PLAYBACK_MODE::NORMAL:
		pData->PlayBack(false);
		break;

	case PLAYBACK_MODE::LOOP:
		pData->PlayBack(true);
		break;

	case PLAYBACK_MODE::RESET_NORMAL:
		pData->Reset();
		pData->PlayBack(false);
		break;

	default:
		// do nothing
		break;
	}
}

void SoundLibrary::StopSound(const SOUND_DATA_ID& rID)
{
	m_pStorage->GetSoundData(rID)->Stop();
}

void SoundLibrary::ReleaseSoundData(const SOUND_DATA_ID& rID)
{
	m_pStorage->ReleaseSoundData(rID);
}

void SoundLibrary::ReleaseSoundDataALL()
{
	m_pStorage->ReleaseALL();
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
