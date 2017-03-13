﻿//==================================================================================================================================//
//!< @file		slTemplate.h
//!< @brief		クラス共通でつかうテンプレートをまとめたヘッダファイル
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_TEMPLATE_H 
#define SL_TEMPLATE_H

// 試作型DirectX関連解放関数テンプレート
template<typename T>
void ReleaseSafely(T* variable)
{
	if(variable != NULL)
	{
		variable->Release();
		variable = NULL;
	}
}


#endif	//  SL_TEMPLATE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//