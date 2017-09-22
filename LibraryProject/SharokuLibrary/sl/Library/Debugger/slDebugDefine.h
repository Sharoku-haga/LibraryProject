//==================================================================================================================================//
//!< @file		slDebugDefine.h
//!< @brief		デバック関連のdefineをまとめたヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/22	更新履歴：
//==================================================================================================================================//

#ifndef SL_DEBUG_DEFINE_H
#define	SL_DEBUG_DEFINE_H

#include "slDebugFunction.h"

#ifdef _DEBUG

/** 強制ブレーク */	
#define slDebugBreak()	DebugBreak()	

/** デバック出力ログ */
#define slDebugOutputLog(...)		sl::slOutputDebugString(__VA_ARGS__)

/** 自作アサート. コメントをつけるときに使用 */
#define slAssert(expression, ...)																									\
		if(!(expression))																											\
		{																															\
			slDebugOutputLog("======================================== AssertLogStart ========================================");	\
			slDebugOutputLog("File : %s", __FILE__);																				\
			slDebugOutputLog("Line : %d", __LINE__);																				\
			slDebugOutputLog(__VA_ARGS__);																							\
			slDebugOutputLog("========================================= AssertLogEnd =========================================");	\
			slDebugBreak();																											\
		}		


/** 自作アサート. 式のチェックのみの場合に使用 */
#define slAssertCheckExpression(expression)		slAssert(expression,	#expression)

#else

#define slDebugBreak()	(void(0))

#define slDebugOutputLog(...)	(void(0))

#define slAssert(expression, ...) (void(0))

#define slAssertCheckExpression(expression)	(void(0))

#endif


#endif	// SL_DEBUG_DEFINE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

