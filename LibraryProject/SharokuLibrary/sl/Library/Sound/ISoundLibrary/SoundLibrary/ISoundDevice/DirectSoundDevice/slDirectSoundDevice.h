//==================================================================================================================================//
//!< @file		slDirectSoundDevice.h		
//!< @brief		sl::DirectSoundDeviceクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/31	更新履歴：
//==================================================================================================================================//

#ifndef SL_DIRECT_SOUND_DEVICE_H
#define SL_DIRECT_SOUND_DEVICE_H

#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include "../slISoundDevice.h"
#include "../../../../../Window/slWindowDeclaration.h"

namespace sl
{

//===================================================================================//
//!< ダイレクトサウンドのデバイスを管理するクラス
//===================================================================================//
class DirectSoundDevice : public ISoundDevice
{

public:
	/** 
	* Constructor
	* @param[in] rHandle	ウィンドウハンドル
	*/
	explicit DirectSoundDevice(const WindowHandle& rHandle);

	/** Destructor */
	virtual ~DirectSoundDevice();
	
	/** 
	* 初期化関数
	* @return 結果 true→成功 false→失敗
	*/
	virtual bool Initlialize()override;

	/** 
	* サウンドデータを作成する関数
	* @param[in]		pFileName ファイル名
	* @param[out]		pData	  作成したサウンドデータのポインタを格納するポインタ
	* @return 作成結果 true→成功 false→失敗
	*/
	virtual bool CreateSoundData(t_char* pFileName, UniquePtr<ISoundData>& pData)override;

private:
	WindowHandle		m_WinHandle;		//!< ウィンドウハンドル
	IDirectSound8*		m_pDSound8;			//!< DirectSoundのインターフェイス

	/**
	* WAVEファイルオープン関数.
	* @param[in]	pFileName		音楽ファイル名
	* @param[out]   pWaveFormatEx	waveフォーマット
	* @param[out]	pWaveData		waveデータ
	* @param[out]	pDataSize		データサイズ
	* @return	true→成功 false→失敗
	*/
	bool OpenWave(TCHAR* pFileName, WAVEFORMATEX* pWaveFormatEx
				, char** pWaveData, DWORD* pDataSize);

};	// class DirectSoundDevice

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

#endif	// SL_DIRECT_SOUND_DEVICE_H