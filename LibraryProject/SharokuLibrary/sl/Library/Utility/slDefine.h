//==================================================================================================================================//
//!< @file		slDefine.h
//!< @brief		マクロ関連をまとめているヘッダファイル
//!< @author	T.Haga
//!< @data		作成日時：2017/08/30	更新履歴 : 2017/11/01
//==================================================================================================================================//

#ifndef SL_DEFINE_H
#define SL_DEFINE_H

#include "../../slBuild.h"

/** エラーID番号 */
#define ERROR_ID_NUMBER -1

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
	int m_Num;										\
	name##__(){}									\
	name##__(int idNum) : m_Num(idNum) {}			\
};													\
typedef struct name##__  name   


#endif	// SL_DEFINE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
