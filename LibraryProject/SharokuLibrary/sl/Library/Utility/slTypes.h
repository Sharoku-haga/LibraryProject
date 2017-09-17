//==================================================================================================================================//
//!< @file		slTypes.h
//!< @brief		型定義をまとめたファイル
//!< @author	T.Haga
//!< @data		作成日時：2017/8/30		更新履歴：2017/09/17
//==================================================================================================================================//

#ifndef SL_TYPES_H
#define SL_TYPES_H

namespace sl
{

typedef unsigned long u_long;

/** char型の型定義 */
#ifdef  UNICODE
#ifndef SL_T_CHAR_DEFINED
typedef w_char t_char;
#define SL_T_CHAR_DEFINED
#endif	// SL_DEFINE_H
#else 
#ifndef SL_T_CHAR_DEFINED
typedef char t_char;
#define SL_T_CHAR_DEFINED
#endif  // SL_T_CHAR_DEFINED
#endif	// UNICODE

}	// namespace sl

#endif	// SL_TYPES_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
