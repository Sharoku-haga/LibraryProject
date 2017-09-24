//==================================================================================================================================//
//!< @file		slUsingNewCreation.h
//!< @brief		sl::UsingNewCreationクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/04	更新履歴：2017/09/24
//==================================================================================================================================//

#ifndef SL_USING_NEW_CREATION_H
#define SL_USING_NEW_CREATION_H

#include "../../Utility/slDefine.h"

namespace sl
{

//===================================================================================//
//!< newを使用してインスタンスを生成するクラス
//!< シングルトンパターンの生成ポリシークラスの1つ
//===================================================================================//
template<class Ty>
class UsingNewCreation
{

public:
	/**
	* インスタンス生成関数
	* @return Ty型クラスのインスタンスへのポインタ
	*/
	static Ty* Create()
	{
		return new Ty();
	}

	/** 
	* 破棄関数 
	* deleteを行う
	* @param[out] pInstance 破棄したいインスタンスへのポインタ
	*/
	static void Destroy(Ty* pInstance)
	{
		delete pInstance;
	}

private:
	/** Constructor */
	UsingNewCreation() noexcept = default;

	/** Destructor */
	~UsingNewCreation() = default;

	/** コピー禁止 */
	SL_DISALLOW_COPY_AND_ASSIGN(UsingNewCreation);

};	// class UsingNewCreation

}	// namespace sl

#endif	// SL_USING_NEW_CREATION_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
