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
//!< ユニークポインタ
//!< リソースへのポインタの所有権を唯一持っているように振舞う
//===================================================================================//
template< class Ty
		, class Deleter = DefaultDeleter<Ty>>
class UniquePtr
{

public:
	/** Constructor */
	UniquePtr() noexcept;

	/**
	* Constructor 
	* @param[in] pointer リソースへのポインタ
	*/
	explicit UniquePtr(Ty* pointer);

	/** MoveConstructor */
	UniquePtr(UniquePtr&& rRight) noexcept;

	/** 変換可能な型の場合のMoveConstructor */
	template< class OtherTy
			, class OtherDeleter>
	UniquePtr(UniquePtr<OtherTy, OtherDeleter>&& rRight) noexcept;

	/** Destructor */
	~UniquePtr();

	/* 
	* リソースの所有権を放棄する関数 
	* @return リソースへのポインタ 
	*/
	Ty* Release() noexcept;

	/** 
	* リソースの所有権を解放し、新たに再設定する関数 
	* デフォルト引数で呼んだ場合は、リソースの所有権を解放するのみ
	* @param[in] 再設定したいリソースへのポインタ
	*/
	void Reset(Ty* pointer = nullptr);

	/**
	* スワップ関数(交換関数)
	* @param[in] rUiniquePtr 交換したいユニークポインタ
	*/
	void Swap(UniquePtr& rPtr)noexcept;

	/** 
	* Getter
	* @return 所有しているリソースへのポインタ
	*/
	inline Ty*  Get() const { return m_pResource;}

	/** 
	* 単項演算子 : アロー演算子
	* @return リソースへのポインタ
	*/
	Ty* operator -> () const { return m_pResource; }

	/** 
	* 単項演算子 : 間接参照演算子
	* @return リソースへの参照
	*/
	Ty& operator * () const { return *m_pResource; }

	/** 
	* 有効なリソースを所有しているかを判断 
	* @return true→所有している false→所有していない
	*/
	explicit operator bool() const noexcept 
	{ 
		return m_pResource != nullptr; 
	}
	
	/** 代入演算子 = UniquePtrをMoveする */
	UniquePtr& operator = (UniquePtr&& rRight);

	/** 代入演算子 = 変換可能な型をもつUniquePtrをMoveする */
	template< class OtherTy
			, class OtherDeleter>
	UniquePtr& operator = (UniquePtr< OtherTy, OtherDeleter>&& rRight);

private:
	Ty*		m_pResource;			//!< リソースへのポインタ

	/** コピー禁止 */
	SL_DISALLOW_COPY_AND_ASSIGN(UniquePtr);

};	// class UniquePtr


/**
* ユニークポインタ作成関数
* @param[in] args T型クラスのコンストラクタに渡す引数
* @return 作成したユニークポインタ
* @todo この関数で使用されているstd::forwardをなくしたい
*/
template< class Ty
		, class Deleter = DefaultDeleter<Ty>
		, class... Args >
UniquePtr<Ty, Deleter> MakeUniquePtr(Args&&... args);

/**
* 比較演算子 ==
* @param[in] rLeft	比較したい左辺のユニークポインタ
* @param[in] rRight 比較したい右辺のユニークポインタ
* @return ture→等しい false→等しくない
*/
template< class Ty
		, class Deleter
		, class OtherTy
		, class OtherDeleter >
const bool operator == (const UniquePtr<Ty, Deleter>& rLeft, const UniquePtr<OtherTy, OtherDeleter>& rRight) noexcept;

/**
* 比較演算子 !=
* @param[in] rLeft	比較したい左辺のユニークポインタ
* @param[in] rRight 比較したい右辺のユニークポインタ
* @return ture→等しない false→等しい
*/
template< class Ty
		, class Deleter
		, class OtherTy
		, class OtherDeleter >
const bool operator != (const UniquePtr<Ty, Deleter>& rLeft, const UniquePtr<OtherTy, OtherDeleter>& rRight) noexcept;

}	// namespace sl

#include "slUniquePtr_private.inl"

#endif	// SL_UNIQUE_PTR_H
	
//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
