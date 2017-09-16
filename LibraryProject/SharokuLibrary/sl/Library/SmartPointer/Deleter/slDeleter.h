//==================================================================================================================================//
//!< @file		slDeleter.h
//!< @brief		デリータクラスをまとめたヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/10 更新履歴 : 2017/09/17
//==================================================================================================================================//

#ifndef SL_DELETER_H
#define SL_DELETER_H

#include "../../Utility/slTemplateFunction.h"

namespace sl
{

//===================================================================================//
//!< デフォルトのデリータクラス
//===================================================================================//
template<class T>
class DefaultDeleter
{

public:
	/** Constructor */
	DefaultDeleter()noexcept = default;

	/** Destructor */
	~DefaultDeleter() = default;

	/**
	* 関数呼び出し演算子のオーバーロード
	* @param[in] pointer 解放したいインスタンスへのポインタ
	*/
	void operator () (T*& pointer)
	{
		SafeDelete<T>(pointer);
	}

};	// class DefaultDeleter

//===================================================================================//
//!< 配列のデリータクラス
//===================================================================================//
template<class T>
class ArrayDeleter
{

public:
	/** Constructor */
	ArrayDeleter()noexcept = default;

	/** Destructor */
	~ArrayDeleter() = default;

	/**
	* 関数呼び出し演算子のオーバーロード
	* @param[in] pointer 解放したい配列のポインタ
	*/
	void operator () (T*& pointer)
	{
		SafeArrayDelete<T>(pointer);
	}

};	// class ArrayDeleter

}	// namespace sl

#endif	// SL_DELETER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
