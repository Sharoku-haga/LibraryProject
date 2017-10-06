//==================================================================================================================================//
//!< @file		slWeakPtr.h
//!< @brief		sl::WeakPtrクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/06	更新履歴：2017/09/17
//==================================================================================================================================//

#ifndef SL_WEAK_PTR_H
#define SL_WEAK_PTR_H

#include "../SharedPtr/slSharedPtr.h"

namespace sl
{

//===================================================================================//
//!< ウィークポインタクラス
//!< SharedPtrが管理しているリソースポインタを監視し、使用する
//===================================================================================//
template<class Ty>
class WeakPtr : public PtrBase<Ty> 
{

public:
	/** Constructor */
	WeakPtr()noexcept;

	/** 
	* Constructor
	* @param[in] rPtr 監視したいSharedPtr
	*/
	explicit WeakPtr(const SharedPtr<Ty>& rPtr);

	/** 
	* Constructor
	* @param[in] rPtr 監視したい変更可能な型をもつSharedPtr
	*/
	template<class OtherTy>
	explicit WeakPtr(const SharedPtr<OtherTy>& rPtr);

	/** CopyConstructor */
	WeakPtr(const WeakPtr& rPtr);

	/** 変換可能な型の場合のCopyConstructor */
	template<class OtherTy>
	WeakPtr(const WeakPtr<OtherTy>& rPtr);

	/** MoveConstructor */
	WeakPtr(WeakPtr&& rRight);

	/** 変換可能な型の場合のMoveConstructor */
	template<class OtherTy>
	WeakPtr(WeakPtr<OtherTy>&& rRight);

	/** Destructor */
	~WeakPtr();

	/**
	* 現在監視しているリソースポインタ(SharedPtr)を取得する関数
	* @return 現在監視しているリソースポインタ(SharedPtr)
	*/
	SharedPtr<Ty> Lock();

	/** リセット関数.監視を解放する関数 */
	void Reset();

	/**
	* 監視しているリソースが無効かどうか確認する関数
	* @return ture→無効 false→有効
	*/
	bool IsExpired();

	/** 代入演算子 = WeakPtrをCopyする */
	WeakPtr& operator = (const WeakPtr& rPtr);

	/** 代入演算子 = 変換可能な型をもつWeakPtrをCopyする */
	template<class OtherTy>
	WeakPtr& operator = (const WeakPtr<OtherTy>& rPtr);

	/** 代入演算子 = SharedPtrをCopyする */
	WeakPtr& operator = (const SharedPtr<Ty>& rPtr);

	/** 代入演算子 = 変換可能な型をもつSharedPtrをCopyする */
	template<class OtherTy>
	WeakPtr& operator = (const SharedPtr<OtherTy>& rRight);

	/** 代入演算子 = WeakPtrをMoveする */
	WeakPtr& operator = (WeakPtr&& rPtr);

	/** 代入演算子 = 変換可能な型をもつWeakPtrをMoveする */
	template<class OtherTy>
	WeakPtr& operator = (WeakPtr<OtherTy>&& rRight);

};	// class WeakPtr

}	// namespace sl

#include "slWeakPtr_private.inl"

#endif	// SL_WEAK_PTR_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
