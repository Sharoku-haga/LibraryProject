//==================================================================================================================================//
//!< @file		slBasicSingleton.h
//!< @brief		sl::BasicSingletonクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/04
//==================================================================================================================================//

#ifndef SL_BASIC_SINGLETON_H
#define SL_BASIC_SINGLETON_H

#include "../Utility/slDefine.h"
#include "CreationPolicy/slStaticCreation.h"
#include "CreationPolicy/slUsingNewCreation.h"
#include "LifeTimePolicy/slDefaultLifeTime.h"

namespace sl
{

//======================================================================//
//!< 基本的なシングルトンパターンのテンプレートクラス
//!< 機能の組みかえができる
//!< @attention クラスTに必ずCreationPolicyをフレンドクラスとして明記する
//======================================================================//
template< class T
		, template<class> class CreationPolicy = StaticCreation
		, template<class> class LifeTimePolicy = DefaultLifeTime
		>
class BasicSingleton
{

public:
	/**
	* インスタンスへの参照を取得する関数
	* @return インスタンスへの参照
	*/
	static T& Instance()
	{
		if(m_pInstance == nullptr)
		{
			MakeInstance();
		}

		return *m_pInstance;
	}

private:
	static T*			m_pInstance;				//!< T型クラスのインスタンスへのポインタ
	static bool			m_Destroyed;				//!< 破棄されたかどうかのフラグ ture→破棄された false→破棄されていない

	inline BasicSingleton() noexcept = default;
	inline ~BasicSingleton() = default;
	SL_DISALLOW_COPY_AND_ASSIGN(BasicSingleton);

	/** インスタンスを作成する関数 */
	static void MakeInstance()
	{
		if(m_Destroyed)
		{
			LifeTimePolicy<T>::HandleOnDeadReference();
			m_Destroyed = false;
		}
		m_pInstance = CreationPolicy<T>::Create();
		LifeTimePolicy<T>::ScheduleDestruction(m_pInstance, DestroySingleton);
	}

	/** 破棄関数 */
	static void DestroySingleton()
	{
		CreationPolicy<T>::Destroy(m_pInstance);
		m_pInstance = nullptr;
		m_Destroyed = true;
	}

};	// class BasicSingleton

template< class T
		, template<class> class CreationPolicy = StaticCreation
		, template<class> class LifeTimePolicy = DefaultLifeTime
		>
T* BasicSingleton<T, CreationPolicy, LifeTimePolicy>::m_pInstance = nullptr;

template< class T
		, template<class> class CreationPolicy = StaticCreation
		, template<class> class LifeTimePolicy = DefaultLifeTime
		>
bool BasicSingleton<T, CreationPolicy, LifeTimePolicy>::m_Destroyed = false;

}	// namespace sl

#endif	// SL_BASIC_SINGLETON_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
