//==================================================================================================================================//
//!< @file		slUserManualSingleton.h
//!< @brief		sl::UserManualSingletonクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/04
//==================================================================================================================================//

#ifndef SL_USER_MANUAL_SINGLETON_H
#define SL_USER_MANUAL_SINGLETON_H

#include <cassert>
#include "../Common/slDefine.h"

namespace sl
{

//======================================================================//
//!< ユーザーが生成と破棄を行うシングルトンパターンのテンプレートクラス
//!< @attention クラスTに必ずフレンドクラスとして明記すること
//======================================================================//
template<class T>
class UserManualSingleton
{

public:
	/** インスタンスを生成する関数 */
	static void Create()
	{
		assert(m_pInstance == nullptr);	
		m_pInstance = new T();
	}

	/** インスタンスを破棄する関数 */
	static void Destroy()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}

	/**
	* インスタンスへの参照を取得する関数
	* @return T型インスタンスへの参照
	*/
	static T& Instance()
	{
		assert(m_pInstance != nullptr);	
		return *m_pInstance;
	}

private:
	static T*	m_pInstance;		//!< T型クラスのインスタンスへのポインタ

	inline UserManualSingleton() noexcept = default;
	inline ~UserManualSingleton() = default;
	SL_DISALLOW_COPY_AND_ASSIGN(UserManualSingleton);

};	// class UserManualSingleton


template<class T>
T* UserManualSingleton<T>::m_pInstance = nullptr;

}	// namespace sl

#endif	// SL_USER_MANUAL_SINGLETON_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
