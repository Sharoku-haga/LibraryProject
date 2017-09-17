//==================================================================================================================================//
//!< @file		slCompressedPair.h
//!< @brief		sl::CompressedPairクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/17	更新履歴：2017/09/17
//==================================================================================================================================//

#ifndef SL_COMPRESSED_PAIR_H
#define SL_COMPRESSED_PAIR_H

#include <utility>
#include <type_traits>

namespace sl
{

//===================================================================================//
//!< 引数タグ構造体
//!< 下記のCompressedPairクラスのConstructorの引数判断で使用
//===================================================================================//

/** Constructorの引数が可変長引数のみ場合のタグ構造体 */
struct Zero_then_variadic_args_t{};	

/** Constructorの引数が通常引数+可変長引数の場合のタグ構造体 */
struct One_then_variadic_args_t{};	

//===================================================================================//
//!< 圧縮ペアを作成するクラス 
//!< @note	1つ目のクラス(この場合Ty1)が空クラス&finalじゃないことが条件
//!< @note	上記を満たしていないとオーバーロードから外され下記クラスへ派生する。
//===================================================================================//
template< class Ty1,
		  class Ty2,
		  bool = std::is_empty<Ty1>::value && !std::is_final<Ty1>::value>
class CompressedPair final : private Ty1 
{

public:
	/**
	* 引数が型Ty2に渡す可変長引数のみ場合のConstructor
	* @param[in] タグ構造体
	* @param[in] val2 型Ty2のConstructorに渡す可変長引数
	*/
	template<class... OtherTy2>
	explicit CompressedPair(Zero_then_variadic_args_t, OtherTy2&&... val2)
		: Ty1()
		, m_Ty2Val(std::forward<OtherTy2>(val2)...)
	{}

	/**
	* 引数が型Ty1に渡す引数 + 型Ty2に渡す可変長引数の場合のConstructor
	* @param[in] タグ構造体
	* @param[in] val1 型Ty1のConstructorに渡す引数
	* @param[in] val2 型Ty2のConstructorに渡す可変長引数
	*/
	template< class OtherTy1
			, class... OtherTy2>
	CompressedPair(One_then_variadic_args_t, OtherTy1&& val1, OtherTy2&&... val2)
		: Ty1(std::forward<OtherTy1>(val1))
		, m_Ty2Val(std::forward<OtherTy2>(val2)...)
	{}

	/** 
	* 型Ty1を取得するGetter 
	* @return Ty1型オブジェクトの参照	
	*/
	Ty1& GetFirst(){ return (*this);}

	/** 
	* 型Ty1を取得するGetter(const)
	* @return Ty1型オブジェクトの参照
	*/
	const Ty1& GetFirst() const { return (*this);}

	/** 
	* 型Ty2の変数を取得するGetter 
	* @return Ty2型の変数の参照
	*/
	Ty2& GetSecond(){ return m_Ty2Val;}

	/** 
	* 型Ty2の変数を取得するGetter(const) 
	* @return Ty2型の変数の参照
	*/
	const Ty2& GetSecond() const { return m_Ty2Val;}

private:
	Ty2  m_Ty2Val;			//!< 型Ty2の変数

};	// class CompressedPair	<Ty1, Ty2, true>

//===================================================================================//
//!< 圧縮ペアを作成するクラス<br>
//!< @note	1つ目のクラス(この場合Ty1)が条件を満たさなかった場合に派生するクラス
//===================================================================================//
template< class Ty1,
		  class Ty2 >
class CompressedPair <Ty1, Ty2, false> final 
{

public:
	/**
	* 引数が型Ty2に渡す可変長引数のみ場合のConstructor
	* @param[in] タグ構造体
	* @param[in] val2 型Ty2のConstructorに渡す可変長引数
	*/
	template<class... OtherTy2>
	explicit CompressedPair(Zero_then_variadic_args_t, OtherTy2&&... val2)
		: m_Ty1Val()
		, m_Ty2Val(std::forward<OtherTy2>(val2)...)
	{}

	/**
	* 引数が型Ty1に渡す引数 + 型Ty2に渡す可変長引数の場合のConstructor
	* @param[in] タグ構造体
	* @param[in] val1 型Ty1のConstructorに渡す引数
	* @param[in] val2 型Ty2のConstructorに渡す可変長引数
	*/
	template< class OtherTy1
			, class... OtherTy2>
	CompressedPair(One_then_variadic_args_t, OtherTy1&& val1, OtherTy2&&... val2)
		: m_Ty1Val(std::forward<OtherTy1>(val1))
		, m_Ty2Val(std::forward<OtherTy2>(val2)...)
	{}

	/** 
	* 型Ty1の変数を取得するGetter 
	* @return Ty1型の変数の参照
	*/
	Ty1& GetFirst(){ return m_Ty1Val;}

	/** 
	* 型Ty1の変数を取得するGetter(const) 
	* @return Ty1型の変数の参照
	*/
	const Ty1& GetFirst() const { return m_Ty1Val;}

	/** 
	* 型Ty2の変数を取得するGetter 
	* @return Ty2型の変数の参照
	*/
	Ty2& GetSecond(){ return m_Ty2Val;}

	/** 
	* 型Ty2の変数を取得するGetter(const) 
	* @return Ty2型の変数の参照
	*/
	const Ty2& GetSecond() const { return m_Ty2Val;}

private:
	Ty1	 m_Ty1Val;		//!< 型Ty1の変数
	Ty2  m_Ty2Val;		//!< 型Ty2の変数

};	// class CompressedPair <Ty1, Ty2, false>

}	// namespace sl

#endif	// SL_COMPRESSED_PAIR_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
