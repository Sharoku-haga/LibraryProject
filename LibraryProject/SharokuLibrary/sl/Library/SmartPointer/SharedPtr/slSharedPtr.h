//==================================================================================================================================//
//!< @file		slSharedPtr.h
//!< @brief		sl::SharedPtrクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/06	更新履歴 : 2017/09/17
//==================================================================================================================================//

#ifndef SL_SHARED_PTR_H
#define SL_SHARED_PTR_H

#include "../PtrBase/slPtrBase.h"

namespace sl
{

template<class Ty>class WeakPtr;

/** @todo 後でMakeShared関数も作成する */
//===================================================================================//
//!< シェアードポインタクラス
//!< 参照カウント型スマートポインタ
//===================================================================================//
template< class Ty>
class SharedPtr : public PtrBase<Ty>
{

public:
	/** Constructor */
	SharedPtr() noexcept;

	/** 
	* Constructor
	* @param[in] pResource リソースへのポインタ
	*/ 
	explicit SharedPtr(Ty* pResource);

	/** 
	* Constructor 
	* @param[in] pResource 変換可能なリソースへのポインタ 
	*/
	template<class OtherTy>
	explicit SharedPtr(OtherTy* pResource);

	/** 
	* Constructor
	* @param[in] rWeakPtr ウィークポインタ
	*/ 
	explicit SharedPtr(const WeakPtr<Ty>& rWeakPtr);

	/** 
	* Constructor 
	* @param[in] pResource リソースへのポインタ
	* @param[in] Del	   設定したいデリータ
	*/
	template<class Deleter>
	SharedPtr(Ty* pResource, Deleter Del);

	/** 
	* Constructor 
	* @param[in] pResource 変換可能なリソースへのポインタ
	* @param[in] Del	   設定したいデリータ
	*/
	template< class OtherTy
			, class Deleter>
	SharedPtr(OtherTy* pResource, Deleter Del);

	/** CopyConstructor */
	SharedPtr(const SharedPtr& rPtr);

	/** 変換可能な型の場合のCopyConstructor */
	template<class OtherTy>
	SharedPtr(const SharedPtr<OtherTy>& rPtr);

	/** MoveConstructor */
	SharedPtr(SharedPtr&& rRight) noexcept;

	/** 変換可能な型の場合のMoveConstructor */
	template<class OtherTy>
	SharedPtr(SharedPtr<OtherTy>&& rRight) noexcept;

	/** Destructor */
	~SharedPtr();

	/** リセット関数.参照を解放するのみ */
	void Reset();

	/** 
	* リセット関数.参照を解放し、新しいリソースを参照する
	* @param[in] pResource リソースへのポインタ
	*/
	void Reset(Ty* pResource);

	/** 
	* リセット関数.参照を解放し、変換可能な新しいリソースを参照する
	* @param[in] pResource 変換可能なリソースへのポインタ
	*/
	template<class OtherTy>
	void Reset(OtherTy* pResource);

	/** 
	* リセット関数.参照を解放し、新しいリソースを参照&デリータを設定する
	* @param[in] pResource リソースへのポインタ
	* @param[in] Del	   設定したいデリータ
	*/
	template<class Deleter>
	void Reset(Ty* pResource, Deleter Del);

	/** 
	* リセット関数.参照を解放し、変換可能な新しいリソースを参照 & デリータを設定する
	* @param[in] pResource リソースへのポインタ
	* @param[in] Del	   設定したいデリータ
	*/
	template< class OtherTy
			, class Deleter>
	void Reset(OtherTy* pResource, Deleter rDel);

	/** 
	* 単項演算子 : アロー演算子
	* @return リソースへのポインタ
	*/
	Ty* operator ->() const { return this->Get(); }

	/** 
	* 単項演算子 : 間接参照演算子
	* @return リソースへの参照
	*/
	Ty& operator *() const { return *(this->Get()); }

	/** 代入演算子 = SharedPtrをCopyする */
	SharedPtr& operator = (const SharedPtr& rPtr);

	/** 代入演算子 = 変換可能な型をもつSharedPtrをCopyする */
	template<class OtherTy>
	SharedPtr& operator = (const SharedPtr<OtherTy>& rPtr);

	/** 代入演算子 = SharedPtrをMoveする */
	SharedPtr& operator = (SharedPtr&& rRight);

	/** 代入演算子 = 変換可能な型をもつSharedPtrをMoveする */
	template<class OtherTy>
	SharedPtr& operator = (SharedPtr<OtherTy>&& rRight);

};	// class SharedPtr 


//===================================================================================//
//!< SharedPtr関連関数 
//===================================================================================//

/**
* 比較演算子 ==
* @param[in] rLeft	比較したい左辺のユニークポインタ
* @param[in] rRight 比較したい右辺のユニークポインタ
* @return ture→等しい false→等しくない
*/
template< class Ty1
		, class Ty2>
const bool operator == (const SharedPtr<Ty1>& rLeft, const SharedPtr<Ty2>& rRight) noexcept;

/**
* 比較演算子 !=
* @param[in] rLeft	比較したい左辺のユニークポインタ
* @param[in] rRight 比較したい右辺のユニークポインタ
* @return ture→等しない false→等しい
*/
template< class Ty1
	, class Ty2>
	const bool operator != (const SharedPtr<Ty1>& rLeft, const SharedPtr<Ty2>& rRight) noexcept;

}	// namespace sl

#include "slSharedPtr_private.inl"

#endif	// SL_SHARED_PTR_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
