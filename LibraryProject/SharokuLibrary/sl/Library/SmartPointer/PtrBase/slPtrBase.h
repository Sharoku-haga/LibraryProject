//==================================================================================================================================//
//!< @file		slPtrBase.h
//!< @brief		sl::PtrBaseクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/17	更新履歴：
//==================================================================================================================================//

#ifndef SL_PTR_BASE_H
#define SL_PTR_BASE_H

#include "../PtrSharedInfo/PtrSharedInfoBase.h"
#include "../PtrSharedInfo/PtrSharedInfo.h"
#include "../Deleter/slDeleter.h"
#include "../../Utility/slTemplateFunction.h"

namespace sl
{

//===================================================================================//
//!< シェアードとウィークポインタのベースクラス
//!< デフォルトのデリータはDefaultDeleterクラス
//===================================================================================//
template<class Ty>
class PtrBase
{

public:
	/** Constructor */
	PtrBase()noexcept;

	/** 
	* Constructor 
	* @param[in] pResource リソースへのポインタ 
	*/
	explicit PtrBase(Ty* pResource);

	/** 
	* Constructor 
	* @param[in] pResource 変換可能なリソースへのポインタ 
	*/
	template<class OtherTy>
	explicit PtrBase(OtherTy* pResource);

	/** 
	* Constructor 
	* @param[in] pResource リソースへのポインタ
	* @param[in] Del	   設定したいデリータ
	*/
	template<class Deleter>
	PtrBase(Ty* pResource, Deleter Del);
				
	/** 
	* Constructor 
	* @param[in] pResource 変換可能なリソースへのポインタ
	* @param[in] Del	   設定したいデリータ
	*/
	template< class OtherTy
			, class Deleter>
	PtrBase(OtherTy* pResource, Deleter Del);

	/** CopyConstructor */
	PtrBase(const PtrBase& rPtr);

	/** 変換可能な型の場合のCopyConstructor */
	template<class OtherTy>
	PtrBase(const PtrBase<OtherTy>& rPtr);

	/** MoveConstructor */
	PtrBase(PtrBase&& rRight)noexcept;

	/** 変換可能な型の場合のMoveConstructor */
	template<class OtherTy>
	PtrBase(PtrBase<OtherTy>&& rRight)noexcept;

	/** Destructor */
	~PtrBase() = default;

	/**
	* スワップ関数
	* @param[out] rPtr 中身を交換したいポインタ
	*/
	void Swap(PtrBase& rPtr)noexcept;

	/**
	* Getter
	* @return リソースへのポインタ
	*/
	inline Ty* Get() const { return m_pResource; }

	/**
	* 参照カウント数を確認する関数
	* @return 参照カウント数 or 参照されていない場合などは0が戻る
	*/
	u_long UseRefCount();

	/**
	* リソースが有効かどうか確認するoperator bool
	* @return ture→有効 false→無効
	*/
	explicit operator bool() const noexcept
	{
		return m_pResource != nullptr;
	}

protected:
	/** 参照数を増やす関数 */
	void AddRefCount();

	/** 監視数を増やす関数 */
	void AddObserverCount();

	/** 参照を解放する関数 */
	void ReleaseReference();

	/** 監視を解放する関数 */
	void ReleaseObserver();

	/**
	* 監視カウント数を確認する関数
	* @return 監視カウント数 or リソース無効の場合などは0が戻る
	*/
	u_long UseObserverCount();

private:
	Ty*							m_pResource;			//!< リソースへのポインタ
	PtrSharedInfoBase*			m_pInfo;				//!< ポインタの共有情報	

	/** フレンドクラス */
	template<class Ty0>
	friend class PtrBase;

};	// class PtrBase

}	// namespace sl

#include "slPtrBase_private.inl"

#endif	// SL_PTR_BASE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
