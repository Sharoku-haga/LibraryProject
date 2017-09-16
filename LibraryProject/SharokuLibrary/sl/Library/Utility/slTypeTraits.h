//==================================================================================================================================//
//!< @file		slTypeTraits.h
//!< @brief		型特性メタテンプレート関連をまとめたヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/17	更新履歴：
//==================================================================================================================================//

#ifndef SL_TYPE_TRAITS_H
#define SL_TYPE_TRAITS_H

/** 参照を取り除く型特性メタ ------------------------------------------------------- */

template <class Ty>
struct RemoveReference
{
	using Type = Ty;
};

template <class Ty>
struct RemoveReference<Ty&>
{
	using Type = Ty;
};

template <class Ty>
struct RemoveReference<Ty&&>
{
	using Type = Ty;
};

/** 
* Move 右辺値修飾を行う
* @param[in]  右辺値修飾したい値
* @return 右辺値修飾した値
*/
template<class Ty> 
inline constexpr typename RemoveReference<Ty>::Type&& Move(Ty&& arg) 
{	
	return (static_cast<typename RemoveReference<Ty>::Type&&>(arg));
}

#endif	// SL_TYPE_TRAITS_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

