//==================================================================================================================================//
//!< @file		slDefaultLifeTime.h
//!< @brief		sl::DefaultLifeTimeクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/04	更新履歴：2017/09/17
//==================================================================================================================================//

#ifndef SL_DEFAULT_LIFE_TIME_H
#define SL_DEFAULT_LIFE_TIME_H

#include <cassert>
#include <cstdlib>
#include "../../Utility/slDefine.h"

namespace sl
{

//===================================================================================//
//!< デフォルトの寿命管理クラス
//!< 寿命管理ポリシークラスの1つ 
//===================================================================================//
template<class T>
class DefaultLifeTime
{

public:
	/**
	* 死んだ参照を処理する関数
	* 死んだ参照が検出されたときに呼ばれる
	* この関数は呼ばれてはいけないので、assertで止まるようになっている
	*/
	static void HandleOnDeadReference()
	{
		assert(false);		
	}

	/**
	* プログラム終了時に呼び出される関数を登録する関数
	* @param[in] pInstance T型インスタンスへのポインタ ※このクラスでは使用しない
	* @param[in] (*func)() 登録したい関数
	*/
	static void ScheduleDestruction(T* pInstance, void(*func)())
	{
		std::atexit(func);
	}

private:
	DefaultLifeTime() noexcept = default;
	~DefaultLifeTime() = default;
	SL_DISALLOW_COPY_AND_ASSIGN(DefaultLifeTime);

};	// class DefaultLifeTime

}	// namespace sl

#endif	// SL_DEFAULT_LIFE_TIME_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

