//==================================================================================================================================//
//!< @file		slSoundDataStorage.cpp
//!< @brief		sl::SoundDataStorageクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/31	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slSoundDataStorage.h"
#include "../ISoundData/slISoundData.h"
#include "../../../../Utility/slTemplateFunction.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

SoundDataStorage::SoundDataStorage()
	: m_IDNumCount(0)
{}

SoundDataStorage::~SoundDataStorage()
{
	ReleaseALL();
}

SOUND_DATA_ID SoundDataStorage::AddSoundData(ISoundData* pData)
{
	SOUND_DATA_ID id;		// 戻り値のID

	if(m_IDNumCount == INT_MAX)
	{	// IDの値がMAX値なら空いているIDを検索してそこにデータ格納

		id.m_Num = SearchAvailableIDNum();
		m_pSoundDatas[id.m_Num] = pData;
		return id;
	}

	m_pSoundDatas[m_IDNumCount] = pData;
	id.m_Num = m_IDNumCount;
	++m_IDNumCount;

	return id;
}

void SoundDataStorage::ReleaseSoundData(const SOUND_DATA_ID& rID)
{
	SafeDelete(m_pSoundDatas[rID.m_Num]);
	m_pSoundDatas.erase(rID.m_Num);
}

void SoundDataStorage::ReleaseALL()
{
	for(auto& pData : m_pSoundDatas)
	{
		SafeDelete(pData.second);
	}
	m_pSoundDatas.clear();
	m_IDNumCount = 0;
}

/* Private Functions ------------------------------------------------------------------------------------------ */

int SoundDataStorage::SearchAvailableIDNum()
{
	int id;

	/** @todo ここは少し見直しした方がいいかもしれない */
	for(id = 0; id < INT_MAX; ++id)
	{
		if(m_pSoundDatas.find(id) == m_pSoundDatas.end())
		{
			break;
		}
	}
	
	return id;
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
