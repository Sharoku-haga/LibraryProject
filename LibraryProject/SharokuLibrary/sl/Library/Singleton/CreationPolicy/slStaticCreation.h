//==================================================================================================================================//
//!< @file		slStaticCreation.h
//!< @brief		sl::StaticCreationクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/04
//==================================================================================================================================//

#ifndef SL_STATIC_CREATION_H
#define SL_STATIC_CREATION_H

#include"../../Common/slDefine.h"

namespace sl
{

//======================================================================//
//!< 静的領域にインスタンスを生成するクラス
//!< シングルトンパターンの生成ポリシークラスの1つ
//======================================================================//
template<class T>
class StaticCreation
{

public:
	/**
	* インスタンス生成関数
	* @return T型インスタンスへのポインタ
	*/
	static T* Create()
	{
		static T staticClass;
		return &staticClass;
	}

	/** 破棄関数 */
	static void Destroy(T* pInstance)
	{
		pInstance->~T();
	}

private:
	StaticCreation() noexcept = default;
	~StaticCreation() = default;
	SL_DISALLOW_COPY_AND_ASSIGN(StaticCreation);

};	// class StaticCreation

}	// namespace sl

#endif	// SL_STATIC_CREATION_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
