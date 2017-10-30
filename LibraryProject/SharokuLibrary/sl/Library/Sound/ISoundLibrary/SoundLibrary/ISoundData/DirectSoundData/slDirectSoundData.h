//==================================================================================================================================//
//!< @file		slDirectSoundData.h
//!< @brief		sl::DirectSoundDataクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/31	更新履歴：
//==================================================================================================================================//

#ifndef SL_DIRECT_SOUND_DATA_H
#define SL_DIRECT_SOUND_DATA_H

#include <dsound.h>
#include "../slISoundData.h"

namespace sl
{

//===================================================================================//
//!< DirectSoundによるサウンドデータクラス
//===================================================================================//
class DirectSoundData : public ISoundData
{

public:
	/** 
	* Constructor 
	* @param[in] pSoundBuffer サウンドバッファのポインタ
	*/
	explicit DirectSoundData(LPDIRECTSOUNDBUFFER8	pSoundBuffer);

	/** Destructor */
	virtual ~DirectSoundData();

	/**
	* 音を再生する関数.
	* @param[in] isLoop ループ再生するかどうかのフラグ true→ループする false→ループしない
	*/
	virtual void PlayBack(bool isLoop)override;

	/** 音を止める関数 */
	virtual void Stop()override;

	/** 音の再生位置をリセットする関数 */
	virtual void Reset()override;

private:
	LPDIRECTSOUNDBUFFER8		m_pSoundBuffer;		// サウンドバッファ

};	// class DirectSoundData

}	// namespace sl

#endif	// SL_DIRECT_SOUND_DATA_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

