//==================================================================================================================================//
//!< @file		slISoundLibrary.h	
//!< @brief		sl::ISoundLibraryのインターフェースクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/31	更新履歴：2017/11/01
//==================================================================================================================================//

#ifndef SL_ISOUND_LIBRARY_H
#define SL_ISOUND_LIBRARY_H

#include "../../Utility/slDefine.h"
#include "../../Utility/slTypes.h"
#include "../slSoundDeclaration..h"

namespace sl
{

struct WindowHandle;

//===================================================================================//
//!< サウンド関連ライブラリのインターフェースクラス
//===================================================================================//
interface ISoundLibrary
{

public:
	/**
	* 実体を取得する関数
	* @return このクラスを継承したクラス
	*/
	static ISoundLibrary& Instance();

	/** 
	* 初期化関数 
	* @param[in] handle ウィンドウハンドル
	* @return 結果 true→成功 false→失敗
	*/
	virtual bool Initialize(const WindowHandle& handle) = 0;

	/** 
	* サウンドデータを生成する関数
	* @param[in] pFileName サウンドファイル名
	* @return サウンドデータの登録ID. エラーの場合はERROR_ID_NUMBER
	*/
	virtual SOUND_DATA_ID CreateSoundData(t_char* pFileName) = 0;

	/**
	* サウンドを再生する関数
	* @param[in] rID	再生したいサウンドのデータ 
	* @param[in] rMode	再生モード
	*/
	virtual void PlaybackSound(const SOUND_DATA_ID& rID, const PLAYBACK_MODE& rMode) = 0;

	/**
	* サウンドを停止する関数
	* @param[in] rID	停止したいサウンドのデータ 
	*/
	virtual void StopSound(const SOUND_DATA_ID& rID) = 0;

	/**
	* 指定したサウンドデータを停止する関数
	* @param[in] rID	再生したいサウンドのデータ 
	*/
	virtual void ReleaseSoundData(const SOUND_DATA_ID& rID) = 0;

	/** 保管しているサウンドデータをすべて解放する関数 */
	virtual void ReleaseSoundDataALL() = 0;

protected:
	/** Constructor */
	ISoundLibrary() = default;

	/** Destructor */
	virtual ~ISoundLibrary() = default;

	SL_DISALLOW_COPY_AND_ASSIGN(ISoundLibrary);

};	// interface ISoundLibrary 

}	// namespace sl

#endif	// SL_ISOUND_LIBRARY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
