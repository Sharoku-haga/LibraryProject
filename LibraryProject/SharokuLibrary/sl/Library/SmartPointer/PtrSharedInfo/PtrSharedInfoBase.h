//==================================================================================================================================//
//!< @file		slPtrSharedInfoBase.h
//!< @brief		sl::PtrSharedInfoBaseクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/17	更新履歴：
//==================================================================================================================================//

#ifndef SL_PTR_SHARED_INFO_BASE_H
#define	SL_PTR_SHARED_INFO_BASE_H

#include "../../Utility/slTypes.h"

namespace sl
{

//===================================================================================//
//!< ポインタ共有情報を管理するベースクラス
//===================================================================================//
class PtrSharedInfoBase
{

public:
	/** Constructor */
	PtrSharedInfoBase();

	/** CopyConstructor */
	PtrSharedInfoBase(const PtrSharedInfoBase& rInfo);

	/** MoveConstructor */
	PtrSharedInfoBase(PtrSharedInfoBase&& rRight);

	/** Destructor */
	~PtrSharedInfoBase() = default;

	/** 参照カウント数を増やす関数 */
	void AddRefCount();

	/** 監視カウント数を増やす関数 */
	void AddObserverCount();

	/** 
	* 参照を解放する関数
	* 参照が0になればリソースを解放する
	*/
	void ReleaseReference();

	/** 監視(WeakPtrを含む)から解放する関数 */
	void ReleaseObserver();

	/** 
	* Getter
	* @return 参照カウント数
	*/
	inline u_long GetRefCount() const { return m_RefCount;}
	
	/** 
	* Getter
	* @return 監視カウント数
	*/
	inline u_long GetObserverCount() const { return m_ObserverCount;}

protected:
	/** リソース破棄関数 */
	virtual void DestroyResource() = 0;

private:
	u_long		m_RefCount;				//!< 参照カウント数
	u_long		m_ObserverCount;		//!< 監視カウント数

};	// class PtrSharedInfoBase

}	// namespace sl

#endif	// SL_PTR_SHARED_INFO_BASE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
