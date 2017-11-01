//==================================================================================================================================//
//!< @file		slSoundLibrary.h
//!< @brief		sl::SoundLibraryクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/31	更新履歴：2017/11/01
//==================================================================================================================================//

#ifndef SL_SOUND_LIBRARY
#define SL_SOUND_LIBRARY

#include "../slISoundLibrary.h"

namespace sl
{

class ISoundDevice;
class SoundDataStorage;
struct WindowHandle;

//===================================================================================//
//!< サウンド関連ライブラリクラス
//===================================================================================//
class SoundLibrary : public ISoundLibrary
{

public:
	/** Constructor */
	SoundLibrary();

	/** Destructor */
	virtual ~SoundLibrary();

	/** 
	* 初期化関数 
	* @param[in] handle ウィンドウハンドル
	* @return 結果 true→成功 false→失敗
	*/
	virtual bool Initialize(const WindowHandle& handle)override;

	/** 
	* サウンドデータを生成する関数
	* @param[in] pFileName サウンドファイル名
	* @return サウンドデータの登録ID.エラーの場合はERROR_ID_NUMBER
	*/
	virtual SOUND_DATA_ID CreateSoundData(t_char* pFileName)override;

	/**
	* サウンドを再生する関数
	* @param[in] rID	再生したいサウンドのデータ 
	* @param[in] rMode	再生モード
	*/
	virtual void PlaybackSound(const SOUND_DATA_ID& rID, const PLAYBACK_MODE& rMode)override;

	/**
	* サウンドを停止する関数
	* @param[in] rID	停止したいサウンドのデータ 
	*/
	virtual void StopSound(const SOUND_DATA_ID& rID)override;

	/**
	* 指定したサウンドデータを停止する関数
	* @param[in] rID	再生したいサウンドのデータ 
	*/
	virtual void ReleaseSoundData(const SOUND_DATA_ID& rID)override;

	/** 保管しているサウンドデータをすべて解放する関数 */
	virtual void ReleaseSoundDataALL()override;

private:
	ISoundDevice*				m_pDevice;			//!< サウンドデバイスインターフェースクラスのインスタンスへのポインタ
	SoundDataStorage*			m_pStorage;			//!< サウンドデータを保管クラスのインスタンスへのポインタ

};	// class SoundLibrary

}	// namespace sl

#endif	// SL_SOUND_LIBRARY

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
