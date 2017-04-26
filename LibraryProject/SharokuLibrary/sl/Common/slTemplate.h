//==================================================================================================================================//
//!< @file		slTemplate.h
//!< @brief		クラス共通でつかうテンプレートをまとめたヘッダファイル
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_TEMPLATE_H 
#define SL_TEMPLATE_H

#include <windows.h>

namespace sl
{

// 安全デリートテンプレート
template<typename T>
void DeleteSafly(T* variable)
{
	if(variable != nullptr)
	{
		delete variable;
		variable = nullptr;
	}
}


// DirectX関連解放関数テンプレート
template<typename T>
void ReleaseSafely(T* variable)
{
	if(variable != NULL)
	{
		variable->Release();
		variable = NULL;
	}
}

}	// namespace sl

#endif	//  SL_TEMPLATE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
