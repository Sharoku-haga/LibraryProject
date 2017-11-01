//==================================================================================================================================//
//!< @file		slISoundDevice.h
//!< @brief		sl::ISoundDeviceクラス
//!< @author	T.Haga
//!< @data		作成日時：2017/10/31	更新履歴：
//==================================================================================================================================//

#ifndef SL_ISOUND_DEVICE_H
#define SL_ISOUND_DEVICE_H

#include "../../../../Utility/slDefine.h"
#include "../../../../Utility/slTypes.h"
#include "../../../../SmartPointer/slSmartPointer.h"

namespace sl
{

class ISoundData;

//===================================================================================//
//!< サウンドデバイスのインターフェースクラス
//===================================================================================//
interface ISoundDevice
{

public:
	/** Constructor */
	ISoundDevice() = default;

	/** Destructor */
	virtual ~ISoundDevice() = default;

	/** 
	* 初期化関数
	* @return 結果 true→成功 false→失敗
	*/
	virtual bool Initlialize() = 0;

	/** 
	* サウンドデータを作成する関数
	* @param[in]		pFileName ファイル名
	* @param[out]		pData	  作成したサウンドデータのポインタを格納するポインタ
	* @return 作成結果 true→成功 false→失敗
	*/
	virtual bool CreateSoundData(t_char* pFileName, UniquePtr<ISoundData>& pData) = 0;

};	// interface ISoundDevice

}	// namespace sl


#endif	// SL_ISOUND_DEVICE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
