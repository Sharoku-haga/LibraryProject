//==================================================================================================================================//
//!< @file		slTemplateFunction.h
//!< @brief		テンプレート関数群のヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/09	更新履歴：2017/09/17
//==================================================================================================================================//

#ifndef SL_TEMPLATE_FUNCTION_H
#define SL_TEMPLATE_FUNCTION_H

#include "../../slBuild.h"
#include "slTypeTraits.h"

namespace sl
{

//===================================================================================//
//!< ライブラリ共通
//===================================================================================//

/** 
* 安全解放テンプレート関数
* @param[in] pointer 解放したいインスタンスへのポインタ
*/
template<class Ty>
inline void SafeDelete(Ty*& pointer)
{
	if(pointer != nullptr)
	{
		delete pointer;
		pointer = nullptr;
	}
}

/** 
* 安全解放テンプレート関数.配列版
* @param[in] arrayPointer 解放したい配列のポインタ
*/
template<class Ty>
inline void SafeArrayDelete(Ty*& arrayPointer)
{
	if(arrayPointer != nullptr)
	{
		delete[] arrayPointer;
		arrayPointer = nullptr;
	}
}

/** 
* スワップテンプレート関数
* @param[in] rA 2番目の引数(rB)と値を交換したい値	 
* @param[in] rB 1番目の引数(rA)と値を交換したい値
*/
template<class Ty>
void SwapTemplate(Ty& rA, Ty& rB)noexcept
{
	Ty temp = Move(rA);
	rA = Move(rB);
	rB = Move(temp);
}

//===================================================================================//
//!< DirectX用
//===================================================================================//

#ifdef DIRECT_X_11

/** 
* DirectX用 解放テンプレート関数
* @param[in] dxPointer 解放したいDirectX関連のポインタ
*/
template <class Ty>
inline void SafeReleaseDX(Ty*& dxPointer)
{
	if(dxPointer != nullptr)
	{
		dxPointer->Release();
		dxPointer = nullptr;
	}
}

#endif	// DIRECT_X_11

}	// namespace sl

#endif	// SL_TEMPLATE_FUNCTION_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

