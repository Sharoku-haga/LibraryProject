//==================================================================================================================================//
//!< @file		slUsingNewCreation.h
//!< @brief		sl::UsingNewCreationクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/04
//==================================================================================================================================//

#ifndef SL_USING_NEW_CREATION_H
#define SL_USING_NEW_CREATION_H

#include "../../Common/slDefine.h"

namespace sl
{

//======================================================================//
//!< newを使用してインスタンスを生成するクラス
//!< シングルトンパターンの生成ポリシークラスの1つ
//======================================================================//
template<class T>
class UsingNewCreation
{

public:
	/**
	* インスタンス生成関数
	* @return T型インスタンスへのポインタ
	*/
	static T* Create()
	{
		return new T();
	}

	/** 破棄関数 */
	static void Destroy(T* pInstance)
	{
		delete pInstance;
	}

private:
	UsingNewCreation() noexcept = default;
	~UsingNewCreation() = default;
	SL_DISALLOW_COPY_AND_ASSIGN(UsingNewCreation);

};	// class UsingNewCreation

}	// namespace sl

#endif	// SL_USING_NEW_CREATION_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
