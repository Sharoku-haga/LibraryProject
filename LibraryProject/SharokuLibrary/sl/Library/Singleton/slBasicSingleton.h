//==================================================================================================================================//
//!< @file		slBasicSingleton.h
//!< @brief		sl::BasicSingletonクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/04	更新履歴：2017/09/24
//==================================================================================================================================//

#ifndef SL_BASIC_SINGLETON_H
#define SL_BASIC_SINGLETON_H

#include "../Utility/slDefine.h"
#include "CreationPolicy/slStaticCreation.h"
#include "CreationPolicy/slUsingNewCreation.h"
#include "LifeTimePolicy/slDefaultLifeTime.h"

namespace sl
{

//===================================================================================//
//!< 基本的なシングルトンパターンのテンプレートクラス
//!< 機能の組みかえができる
//!< @attention クラスTyに必ずCreationPolicyをフレンドクラスとして明記する
//===================================================================================//
template< class Ty
		, template<class> class CreationPolicy = StaticCreation
		, template<class> class LifeTimePolicy = DefaultLifeTime>
class BasicSingleton
{

public:
	/**
	* インスタンスへの参照を取得する関数.
	* Ty型クラスのインスタンスがなければ作成を行う
	* @return インスタンスへの参照
	*/
	static Ty& Instance()
	{
		if(m_pInstance == nullptr)
		{
			MakeInstance();
		}

		return *m_pInstance;
	}

private:
	static Ty*			m_pInstance;				//!< Ty型クラスのインスタンスへのポインタ
	static bool			m_Destroyed;				//!< 破棄されたかどうかのフラグ ture→破棄された false→破棄されていない

	/** Constructor */
	BasicSingleton() noexcept = default;

	/** Destructor */
	~BasicSingleton() = default;

	/** コピー禁止 */
	SL_DISALLOW_COPY_AND_ASSIGN(BasicSingleton);

	/** インスタンスを作成する関数 */
	static void MakeInstance()
	{
		if(m_Destroyed)
		{
			LifeTimePolicy<Ty>::HandleOnDeadReference();
			m_Destroyed = false;
		}
		m_pInstance = CreationPolicy<Ty>::Create();
		LifeTimePolicy<Ty>::ScheduleDestruction(m_pInstance, DestroySingleton);
	}

	/** 破棄関数 */
	static void DestroySingleton()
	{
		CreationPolicy<Ty>::Destroy(m_pInstance);
		m_pInstance = nullptr;
		m_Destroyed = true;
	}

};	// class BasicSingleton


/* Static Variable -------------------------------------------------------------------------------------------- */

template< class Ty
		, template<class> class CreationPolicy = StaticCreation
		, template<class> class LifeTimePolicy = DefaultLifeTime>
Ty* BasicSingleton<Ty, CreationPolicy, LifeTimePolicy>::m_pInstance = nullptr;

template< class Ty
		, template<class> class CreationPolicy = StaticCreation
		, template<class> class LifeTimePolicy = DefaultLifeTime>
bool BasicSingleton<Ty, CreationPolicy, LifeTimePolicy>::m_Destroyed = false;

}	// namespace sl

#endif	// SL_BASIC_SINGLETON_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
