﻿//==================================================================================================================================//
//!< @file		slPoint.h
//!< @brief		Point構造体関連をまとめたヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/09	更新履歴：
//==================================================================================================================================//

#ifndef SL_POINT_H
#define SL_POINT_H

namespace sl
{

//===================================================================================//
//!< 点の情報を格納する為の構造体 
//===================================================================================//

//===================================================================================//
//!< メンバーがlong型
//===================================================================================//
typedef struct long_Point
{
	long	m_X;	//!< x座標情報
	long	m_Y;	//!< y座標情報

	/** Constructor */
	long_Point() {}
	long_Point(long x, long y): m_X(x), m_Y(y){}

}lPoint;

//===================================================================================//
//!< メンバーがint型
//===================================================================================//
typedef struct int_Point
{
	int	m_X;	//!< x座標情報
	int	m_Y;	//!< y座標情報

	/** Constructor */
	int_Point() {}
	int_Point(int x, int y): m_X(x), m_Y(y){}

}iPoint;

}	// namespace sl

#endif	// SL_POINT_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
