//==================================================================================================================================//
//!< @file		slUserManualSingleton.h
//!< @brief		sl::UserManualSingletonクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/04	更新履歴：2017/09/24
//==================================================================================================================================//

#ifndef SL_USER_MANUAL_SINGLETON_H
#define SL_USER_MANUAL_SINGLETON_H

#include "../Utility/slDefine.h"
#include "../Debugger/slDebugDefine.h"

namespace sl
{

//===================================================================================//
//!< ユーザーが生成と破棄を行うシングルトンパターンのテンプレートクラス
//!< @attention クラスTyに必ずフレンドクラスとして明記すること
//===================================================================================//
template<class Ty>
class UserManualSingleton
{

public:
	/** インスタンスを生成する関数 */
	static void Create()
	{
		slAssertCheckExpression(m_pInstance == nullptr);	
		m_pInstance = new Ty();
	}

	/** インスタンスを破棄する関数 */
	static void Destroy()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}

	/**
	* インスタンスへの参照を取得する関数
	* @return Ty型クラスのインスタンスへの参照
	*/
	static Ty& Instance()
	{
		slAssertCheckExpression(m_pInstance != nullptr);	
		return *m_pInstance;
	}

private:
	static Ty*	m_pInstance;		//!< Ty型クラスのインスタンスへのポインタ

	/** Constructor */
	UserManualSingleton() noexcept = default;

	/** Destructor */
	~UserManualSingleton() = default;

	/** コピー禁止 */
	SL_DISALLOW_COPY_AND_ASSIGN(UserManualSingleton);

};	// class UserManualSingleton


/* Static Variable -------------------------------------------------------------------------------------------- */

template<class Ty>
Ty* UserManualSingleton<Ty>::m_pInstance = nullptr;

}	// namespace sl

#endif	// SL_USER_MANUAL_SINGLETON_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
