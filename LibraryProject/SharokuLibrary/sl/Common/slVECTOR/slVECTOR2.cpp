//==================================================================================================================================//
//!< @file		slVECTOR2.cpp
//!< @brief		SLVECTOR2構造体実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slVECTOR2.h"

/* Namespace -------------------------------------------------------------------------------------------------- */

namespace sl
{

//----------------------------------------------------------------------------//
// SLVECTOR2の実装
//----------------------------------------------------------------------------//

/* Public Functions ------------------------------------------------------------------------------------------- */

SLVECTOR2::SLVECTOR2(float x, float y)
	: x(x)
	, y(y)
{}

SLVECTOR2& SLVECTOR2::operator += (const SLVECTOR2& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}

SLVECTOR2& SLVECTOR2::operator -= (const SLVECTOR2& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}

SLVECTOR2& SLVECTOR2::operator *= (float rhs)
{
	this->x *= rhs;
	this->y *= rhs;
	return *this;
}

SLVECTOR2& SLVECTOR2::operator /= (float rhs)
{
	this->x /= rhs;
	this->y /= rhs;
	return *this;
}

SLVECTOR2 SLVECTOR2::operator + (void)const
{
	return *this;
}

SLVECTOR2 SLVECTOR2::operator - (void)const
{
	SLVECTOR2 tmp;
	tmp.x = -this->x;
	tmp.y = -this->y;
	return tmp;
}

SLVECTOR2 SLVECTOR2::operator + (const SLVECTOR2& rhs) const
{
	SLVECTOR2 tmp;
	tmp.x = this->x + rhs.x;
	tmp.y = this->y + rhs.y;
	return tmp;
}

SLVECTOR2 SLVECTOR2::operator - (const SLVECTOR2& rhs) const
{
	SLVECTOR2 tmp;
	tmp.x = this->x - rhs.x;
	tmp.y = this->y - rhs.y;
	return tmp;
}

SLVECTOR2 SLVECTOR2::operator * (float rhs) const
{
	SLVECTOR2 tmp;
	tmp.x = this->x * rhs;
	tmp.y = this->y * rhs;
	return tmp;
}

SLVECTOR2 SLVECTOR2::operator / (float rhs) const
{
	SLVECTOR2 tmp;
	tmp.x = this->x / rhs;
	tmp.y = this->y / rhs;
	return tmp;
}

bool SLVECTOR2::operator == (const SLVECTOR2& rhs)const
{
	return (this->x == rhs.x && this->y == rhs.y );
}

bool SLVECTOR2::operator != (const SLVECTOR2& rhs)const
{
	return (this->x != rhs.x && this->y != rhs.y);
}

//----------------------------------------------------------------------------//
// SLVECTOR2関連の関数
//----------------------------------------------------------------------------//

SLVECTOR2 operator * (float lhs, const SLVECTOR2& rhs)
{
	SLVECTOR2 tmp;
	tmp.x = lhs * rhs.x;
	tmp.y = lhs * rhs.y;
	return tmp;
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
