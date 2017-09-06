﻿//==================================================================================================================================//
//!< @file		slRect.h
//!< @brief		Rect構造体をまとめたヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/05
//==================================================================================================================================//

#ifndef SL_RECT_H
#define SL_RECT_H

namespace sl
{

/** 
* 四角形の左上隅および右下隅の情報を格納する為の構造体
* メンバーがfloat型。
*/
typedef struct float_Rect 
{
	float	m_Left;			//!< 四角形の左上隅(x軸情報)
	float	m_Top;			//!< 四角形の左上隅(y軸情報)
	float	m_Right;		//!< 四角形の右下隅(x軸情報)
	float	m_Bottom;		//!< 四角形の右下隅(y軸情報)

	/** Constructor */
	float_Rect() {}
	float_Rect(float left, float top, float right, float bottom)
		: m_Left()
		, m_Top()
		, m_Right()
		, m_Bottom()
	{}

}fRect;


}	// namespace sl

#endif	//SL_RECT_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
