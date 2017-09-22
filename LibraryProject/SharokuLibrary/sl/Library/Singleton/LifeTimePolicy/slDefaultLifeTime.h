//==================================================================================================================================//
//!< @file		slDefaultLifeTime.h
//!< @brief		sl::DefaultLifeTimeクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/04	更新履歴：2017/09/24
//==================================================================================================================================//

#ifndef SL_DEFAULT_LIFE_TIME_H
#define SL_DEFAULT_LIFE_TIME_H

#include <cstdlib>
#include "../../Utility/slDefine.h"
#include "../../Debugger/slDebugDefine.h"

namespace sl
{

//===================================================================================//
//!< デフォルトの寿命管理クラス
//!< 寿命管理ポリシークラスの1つ 
//===================================================================================//
template<class Ty>
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
		slAssertCheckExpression(false);		
	}

	/**
	* プログラム終了時に呼び出される関数を登録する関数
	* @param[in] pInstance Ty型インスタンスへのポインタ ※このクラスでは使用しない
	* @param[in] (*func)() 登録したい関数
	*/
	static void ScheduleDestruction(Ty* pInstance, void(*func)())
	{
		std::atexit(func);
	}

private:
	/** Constructor */
	DefaultLifeTime() noexcept = default;

	/** Destructor */
	~DefaultLifeTime() = default;

	/** コピー禁止 */
	SL_DISALLOW_COPY_AND_ASSIGN(DefaultLifeTime);

};	// class DefaultLifeTime

}	// namespace sl

#endif	// SL_DEFAULT_LIFE_TIME_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

