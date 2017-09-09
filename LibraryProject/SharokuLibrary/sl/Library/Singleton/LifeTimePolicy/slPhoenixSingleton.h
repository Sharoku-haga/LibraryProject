﻿//==================================================================================================================================//
//!< @file		slPhoenixSingleton.h
//!< @brief		sl::PhoenixSingletonクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/04
//==================================================================================================================================//

#ifndef SL_PHOENIX_SINGLETON_H
#define SL_PHOENIX_SINGLETON_H

#include "../../Utility/slDefine.h"
#include <cstdlib>

namespace sl
{

//======================================================================//
//!< フェニックスシングルトンを実装するクラス.
//!< フェニックスシングルトンとは一度インスタンスが破棄された後に
//!< 再生成を行うシングルトンパターンのこと
//!< 寿命管理ポリシークラスの1つ 
//!< @data このクラスはまだ改良の余地あり
//======================================================================//
template<class T>
class PhoenixSingleton
{

public:
	/**
	* 死んだ参照を処理する関数
	* 死んだ参照が検出されたときに呼ばれる
	*/
	static void HandleOnDeadReference()
	{}

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
	PhoenixSingleton() noexcept = default;
	~PhoenixSingleton() = default;
	SL_DISALLOW_COPY_AND_ASSIGN(PhoenixSingleton);

};	// class PhoenixSingleton

}	// namespace sl


#endif	// SL_PHOENIX_SINGLETON_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

