﻿//==================================================================================================================================//
//!< @file		slISoundLibrary.cpp
//!< @brief		sl::ISoundLibraryクラスのインターフェイス
//!< @author	T.Haga
//!< @data		作成日時：2017/11/01	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slISoundLibrary.h"
#include "SoundLibrary/slSoundLibrary.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

ISoundLibrary& ISoundLibrary::Instance()
{
	static SoundLibrary lib;
	return lib;
}

}	// namespace sl
//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
