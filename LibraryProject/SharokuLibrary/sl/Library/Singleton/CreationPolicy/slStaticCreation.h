//==================================================================================================================================//
//!< @file		slStaticCreation.h
//!< @brief		sl::StaticCreationクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/04	更新履歴：2017/09/24
//==================================================================================================================================//

#ifndef SL_STATIC_CREATION_H
#define SL_STATIC_CREATION_H

#include"../../Utility/slDefine.h"

namespace sl
{

//===================================================================================//
//!< 静的領域にインスタンスを生成するクラス
//!< シングルトンパターンの生成ポリシークラスの1つ
//===================================================================================//
template<class Ty>
class StaticCreation
{

public:
	/**
	* インスタンス生成関数
	* @return Ty型クラスのインスタンスへのポインタ
	*/
	static Ty* Create()
	{
		static Ty staticClass;
		return &staticClass;
	}

	/** 
	* 破棄関数.
	* デストラクタをよぶ
	* @param[out] pInstance 破棄したいインスタンスへのポインタ
	*/
	static void Destroy(Ty* pInstance)
	{
		pInstance->~Ty();
	}

private:
	/** Constructor */
	StaticCreation() noexcept = default;

	/** Destructor */
	~StaticCreation() = default;

	/** コピー禁止 */
	SL_DISALLOW_COPY_AND_ASSIGN(StaticCreation);

};	// class StaticCreation

}	// namespace sl

#endif	// SL_STATIC_CREATION_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
