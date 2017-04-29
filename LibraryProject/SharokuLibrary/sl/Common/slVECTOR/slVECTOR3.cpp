//==================================================================================================================================//
//!< @file		slVECTOR3.cpp
//!< @brief		SLVECTOR3構造体実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slVECTOR3.h"

/* Namespace -------------------------------------------------------------------------------------------------- */

namespace sl
{

//----------------------------------------------------------------------------//
// SLVECTOR3の実装
//----------------------------------------------------------------------------//

/* Public Functions ------------------------------------------------------------------------------------------- */

SLVECTOR3::SLVECTOR3(float x, float y, float z)
	: x(x)
	, y(y)
	, z(z)
{}

SLVECTOR3& SLVECTOR3::operator += (const SLVECTOR3& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
	return *this;
}

SLVECTOR3& SLVECTOR3::operator -= (const SLVECTOR3& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
	return *this;
}

SLVECTOR3& SLVECTOR3::operator *= (float rhs)
{
	this->x *= rhs;
	this->y *= rhs;
	this->z *= rhs;
	return *this;
}

SLVECTOR3& SLVECTOR3::operator /= (float rhs)
{
	this->x /= rhs;
	this->y /= rhs;
	this->z /= rhs;
	return *this;
}

SLVECTOR3 SLVECTOR3::operator + (void)const
{
	return *this;
}

SLVECTOR3 SLVECTOR3::operator - (void)const
{
	SLVECTOR3 tmp;
	tmp.x = -this->x;
	tmp.y = -this->y;
	tmp.z = -this->z;
	return tmp;
}

SLVECTOR3 SLVECTOR3::operator + (const SLVECTOR3& rhs) const
{
	SLVECTOR3 tmp;
	tmp.x = this->x + rhs.x;
	tmp.y = this->y + rhs.y;
	tmp.z = this->z + rhs.z;
	return tmp;
}

SLVECTOR3 SLVECTOR3::operator - (const SLVECTOR3& rhs) const
{
	SLVECTOR3 tmp;
	tmp.x = this->x - rhs.x;
	tmp.y = this->y - rhs.y;
	tmp.z = this->z - rhs.z;
	return tmp;
}

SLVECTOR3 SLVECTOR3::operator * (float rhs) const
{
	SLVECTOR3 tmp;
	tmp.x = this->x * rhs;
	tmp.y = this->y * rhs;
	tmp.z = this->z * rhs;
	return tmp;
}

SLVECTOR3 SLVECTOR3::operator / (float rhs) const
{
	SLVECTOR3 tmp;
	tmp.x = this->x / rhs;
	tmp.y = this->y / rhs;
	tmp.z = this->z / rhs;
	return tmp;
}

bool SLVECTOR3::operator == (const SLVECTOR3& rhs)const
{
	return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z );
}

bool SLVECTOR3::operator != (const SLVECTOR3& rhs)const
{
	return (this->x != rhs.x && this->y != rhs.y && this->z != rhs.z);
}

//----------------------------------------------------------------------------//
// SLVECTOR3関連の関数
//----------------------------------------------------------------------------//

SLVECTOR3 operator * (float lhs, const SLVECTOR3& rhs)
{
	SLVECTOR3 tmp;
	tmp.x = lhs * rhs.x;
	tmp.y = lhs * rhs.y;
	tmp.z = lhs * rhs.z;
	return tmp;
}

}

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
