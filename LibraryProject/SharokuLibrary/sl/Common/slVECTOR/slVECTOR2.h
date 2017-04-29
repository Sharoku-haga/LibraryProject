//==================================================================================================================================//
//!< @file		slVECTOR2.h
//!< @brief		SLVECTOR2構造体ヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_VECTOR2_H 
#define SL_VECTOR2_H

namespace sl
{

//======================================================================//
//!< 独自の2Dベクター構造体
//======================================================================//

/** @todo 試作型。必要になった場合に随時追加実装を行っていく  */
typedef struct SLVECTOR2
{

public:

	// Constructor ----------------------------------------------------- //
	SLVECTOR2(void) {}
	SLVECTOR2(float x, float y);

	// 代入演算子 ----------------------------------------------------- //
	SLVECTOR2& operator = (const SLVECTOR2& rhs) = default;

	// 複合代入演算子 ------------------------------------------------- //
	SLVECTOR2& operator += (const SLVECTOR2& rhs);
	SLVECTOR2& operator -= (const SLVECTOR2& rhs);
	SLVECTOR2& operator *= (float rhs);
	SLVECTOR2& operator /= (float rhs);

	// 単項演算子 ----------------------------------------------------- //
	SLVECTOR2 operator + (void)const;
	SLVECTOR2 operator - (void)const;

	// 二項演算子 ----------------------------------------------------- //
	SLVECTOR2 operator + ( const SLVECTOR2& rhs) const;
    SLVECTOR2 operator - ( const SLVECTOR2& rhs) const;
    SLVECTOR2 operator * ( float rhs) const;
    SLVECTOR2 operator / ( float rhs) const;

	// 比較演算子 ----------------------------------------------------- //
	bool operator == (const SLVECTOR2& rhs)const;
	bool operator != (const SLVECTOR2& rhs)const;

	// グローバル関数. 乗算の際にが右辺で計算する場合の処理 ----------- //
	friend SLVECTOR2 operator * (float lhs, const SLVECTOR2& rhs);

	// Menber Variable ------------------------------------------------ //
	float x;
	float y;

}SLVECTOR2;

}	// namespace sl

#endif	//   SL_VECTOR_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

