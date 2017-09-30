//==================================================================================================================================//
//!< @file		slDefine.h
//!< @brief		マクロ関連をまとめているヘッダファイル
//!< @author	T.Haga
//!< @data		作成日時：2017/08/30	更新履歴 : 2017/09/17
//==================================================================================================================================//

#ifndef SL_DEFINE_H
#define SL_DEFINE_H

#include "../../slBuild.h"

/** インターフェイスマクロ */
#ifndef	interface
	#define interface struct
#endif	// #ifndef	interface 

/** falseかどうかのチェックマクロ */
#define RESULT_FALSE(result) ((static_cast<bool>(result)) == false)

/** コピー禁止マクロ */
#define SL_DISALLOW_COPY_AND_ASSIGN(...)			\
__VA_ARGS__(const __VA_ARGS__&) = delete;			\
void operator=(const __VA_ARGS__&) = delete;

/** ID(int型)をメンバにもつ構造体作成マクロ */
#define SL_DECLARE_ID(name)							\
struct name##__										\
{													\
	int m_ID;										\
	name##__(){}									\
	name##__(int id) : m_ID(id) {}					\
};													\
typedef struct name##__  name   


#endif	// SL_DEFINE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
