//==================================================================================================================================//
//!< @file		slUniquePtr.h
//!< @brief		sl::UniquePtrクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/06	更新履歴 : 2017/09/17
//==================================================================================================================================//

#ifndef SL_UNIQUE_PTR_H
#define SL_UNIQUE_PTR_H

#include <utility>
#include "../Deleter/slDeleter.h"
#include "../../Utility/slDefine.h"

namespace sl
{

/** @todo Deleter増やすならDeleter取得についての実装も行う --------------------------------------------- */
//===================================================================================//
//!< 自作のユニークポインタ
//!< スマートポインタの1つ
//!< リソースへのポインタの所有権を唯一持っているように振舞う
//===================================================================================//
template< class T
		, template<class> class Deleter = DefaultDeleter>
class UniquePtr
{

public:
	/** Constructor */
	UniquePtr() noexcept;

	/**
	* Constructor 
	* @param[in] pointer リソースへのポインタ
	*/
	explicit UniquePtr(T* pointer)  noexcept;

	/**
	* MoveConstructor
	* @param[out] uiniquePtr 所有権を渡してくれるユニークポインタ
	*/
	UniquePtr(UniquePtr&& uiniquePtr) noexcept;

	/**
	* MoveConstructor
	* @param[out] uiniquePtr 所有権を渡してくれる変換可能なユニークポインタ
	*/
	template< class OtherT
			, template<class> class OtherDeleter>
	UniquePtr(UniquePtr<OtherT, OtherDeleter>&& uiniquePtr) noexcept;

	/** Destructor */
	~UniquePtr();

	/* 
	* リソースの所有権を放棄する関数 
	* @return リソースへのポインタ 
	*/
	T* Release() noexcept;

	/** 
	* リソースの所有権を解放し、新たに再設定する関数 
	* デフォルト引数で呼んだ場合は、リソースの所有権を解放するのみ
	* @param[in] 再設定したいリソースへのポインタ
	*/
	void Reset(T* pointer = nullptr);

	/**
	* スワップ関数(交換関数)
	* @param[in] rUiniquePtr 交換したいユニークポインタ
	*/
	void Swap(UniquePtr& rUiniquePtr)noexcept;

	/** 
	* 所有権を保持しているリソースへのポインタを取得する関数
	* @return 所有しているリソースへのポインタ
	*/
	inline T*  Get() noexcept{ return m_Pointer;}
	inline const T*  Get()  const noexcept{ return m_Pointer; }

	/** 
	* 単項演算子 : アロー演算子
	* @return リソースへのポインタ
	*/
	T* operator -> () const noexcept{ return m_Pointer; }

	/** 
	* 単項演算子 : 間接参照演算子
	* @return リソースへの参照
	*/
	T& operator * () const { return *m_Pointer; }

	/** 
	* 有効なリソースを所有しているかを判断 
	* @return true→所有している false→所有していない
	*/
	explicit operator bool() const noexcept 
	{ 
		return m_Pointer != nullptr; 
	}
	
	/**
	* 代入演算子 =
	* 自身が所有しているリソースを解放し、pUniqueからリソースの所有権をうけとる
	* @param[out] uiniquePtr 所有権を渡してくれるユニークポインタ
	* @return 自身の参照
	*/
	UniquePtr& operator = (UniquePtr&& uiniquePtr);

	/**
	* 代入演算子 =
	* 自身が所有しているリソースを解放し、pUniqueからリソースの所有権をうけとる
	* こちらは変換可能なpUnique場合のもの
	* @param[out] uiniquePtr 所有権を渡してくれるユニークポインタ
	* @return 自身の参照
	*/
	template< class OtherT
			, template<class>class OtherDeleter>
	UniquePtr& operator = (UniquePtr< OtherT, OtherDeleter>&& uiniquePtr);

private:
	T*		m_Pointer;			//!< リソースへのポインタ

	/** コピー禁止 */
	SL_DISALLOW_COPY_AND_ASSIGN(UniquePtr);

};	// class UniquePtr


/**
* ユニークポインタ作成関数
* @param[in] args T型クラスのコンストラクタに渡す引数
* @return 作成したユニークポインタ
* @todo この関数で使用されているstd::forwardをなくしたい
*/
template< class T
		, template<class> class Deleter = DefaultDeleter
		, class... Args >
UniquePtr<T, Deleter> MakeUniquePtr(Args&&... args);

/**
* 比較演算子 ==
* @param[in] rLeft	比較したい左辺のユニークポインタ
* @param[in] rRight 比較したい右辺のユニークポインタ
* @return ture→等しい false→等しくない
*/
template< class T
		, template<class T> class Deleter
		, class OtherT
		, template<class OtherT>class OtherDeleter >
const bool operator == (const UniquePtr<T, Deleter>& rLeft, const UniquePtr<OtherT, OtherDeleter>& rRight) noexcept;

/**
* 比較演算子 !=
* @param[in] rLeft	比較したい左辺のユニークポインタ
* @param[in] rRight 比較したい右辺のユニークポインタ
* @return ture→等しない false→等しい
*/
template< class T
		, template<class T> class Deleter
		, class OtherT
		, template<class OtherT>class OtherDeleter >
const bool operator != (const UniquePtr<T, Deleter>& rLeft, const UniquePtr<OtherT, OtherDeleter>& rRight) noexcept;

}	// namespace sl

#include "slUniquePtr_private.inl"

#endif	// SL_UNIQUE_PTR_H
	
//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
