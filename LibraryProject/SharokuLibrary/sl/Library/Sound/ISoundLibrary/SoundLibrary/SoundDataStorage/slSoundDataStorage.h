//==================================================================================================================================//
//!< @file		slSoundDataStorage.h
//!< @brief		sl::SoundDataStorageクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/31	更新履歴：
//==================================================================================================================================//

#ifndef SL_SOUND_DATA_STORAGE_H
#define SL_SOUND_DATA_STORAGE_H

#include <map>
#include "../../../slSoundDeclaration..h"

namespace sl
{

class ISoundData;

//===================================================================================//
//!< サウンドデータの保管などを行うクラス 
//===================================================================================//
class SoundDataStorage
{

public:
	/** Constructor */
	SoundDataStorage();

	/** Destructor */
	~SoundDataStorage();

	/**
	* サウンドデータを加える関数
	* @param[in] pData	サウンドデータ	
	* @return サウンドのID
	*/
	SOUND_DATA_ID AddSoundData(ISoundData* pData);

	/**
	* 指定したサウンドデータを解放する関数
	* @param[in] rID	解放したいサウンドデータのID
	*/
	void ReleaseSoundData(const SOUND_DATA_ID& rID);

	/** サウンドデータを全て解放する関数 */
	void ReleaseALL();

	/**
	* Getter
	* @param[in] rID 取得したいサウンドデータのID
	* @return サウンドデータへのポインタ
	*/
	inline ISoundData*const GetSoundData(const SOUND_DATA_ID& rID) 
	{ 
		return m_pSoundDatas[rID.m_Num];  
	}

private:
	std::map<int, ISoundData*>		m_pSoundDatas;		//!< サウンドデータを格納するmap
	int								m_IDNumCount;		//!< ID番号のカウント数

	/** 
	* 現在使用できるIDを検索する関数 
	* @return 使用できるID
	*/
	int SearchAvailableIDNum();

};	// class SoundDataStorage

}	// namespace sl

#endif	// SL_SOUND_DATA_STORAGE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//


