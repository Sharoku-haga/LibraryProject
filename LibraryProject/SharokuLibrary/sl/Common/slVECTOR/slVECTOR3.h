//==================================================================================================================================//
//!< @file		slVECTOR3.h
//!< @brief		SLVECTOR3構造体ヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_VECTOR3_H
#define SL_VECTOR3_H

namespace sl
{

//======================================================================//
//!< 独自の3Dベクター構造体
//======================================================================//

/** @todo 試作型。必要になった場合に随時追加実装を行っていく  */
typedef struct SLVECTOR3
{

public:

	// Constructor ----------------------------------------------------- //
	SLVECTOR3(void) {};
	SLVECTOR3(float x, float y, float z);

	// 代入演算子 ----------------------------------------------------- //
	SLVECTOR3& operator = (const SLVECTOR3& rhs) = default;

	// 複合代入演算子 ------------------------------------------------- //
	SLVECTOR3& operator += (const SLVECTOR3& rhs);
	SLVECTOR3& operator -= (const SLVECTOR3& rhs);
	SLVECTOR3& operator *= (float rhs);
	SLVECTOR3& operator /= (float rhs);

	// 単項演算子 ----------------------------------------------------- //
	SLVECTOR3 operator + (void)const;
	SLVECTOR3 operator - (void)const;

	// 二項演算子 ----------------------------------------------------- //
	SLVECTOR3 operator + ( const SLVECTOR3& rhs) const;
    SLVECTOR3 operator - ( const SLVECTOR3& rhs) const;
    SLVECTOR3 operator * ( float rhs) const;
    SLVECTOR3 operator / ( float rhs) const;

	// 比較演算子 ----------------------------------------------------- //
	bool operator == (const SLVECTOR3& rhs)const;
	bool operator != (const SLVECTOR3& rhs)const;

	// グローバル関数. 乗算の際にが右辺で計算する場合の処理 ----------- //
	friend SLVECTOR3 operator * (float lhs, const SLVECTOR3& rhs);

	// Menber Variable ------------------------------------------------ //
	float x;
	float y;
	float z;

}SLVECTOR3;

}

#endif	// SL_VECTOR3_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
