//==================================================================================================================================//
//!< @file		slDXDeviceManager.h
//!< @brief		sl::DXDeviceManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/29	更新履歴：
//==================================================================================================================================//

#ifndef SL_DX_DEVICE_MANAGER_H
#define SL_DX_DEVICE_MANAGER_H

#include <windows.h>
#include <d3dx11.h>
#include "../../../Utility/slDefine.h"

namespace sl
{

//===================================================================================//
//!< DirectXのデバイスを管理するクラス
//===================================================================================//
class DXDeviceManager
{

public:
	/** Constructor */
	DXDeviceManager();

	/** Destructor */
	~DXDeviceManager();

	/**
	* デバイス関連を生成する関数 
	* @return true→成功 false→失敗
	*/
	bool CreateDevice();

	/**
	* デバイスを取得する関数
	* @return DirectX11のデバイス
	*/
	inline ID3D11Device*	GetDevice(void) const { return m_pDevice;  }

	/**
	* デバイスコンテキストを取得する関数
	* @return DirectX11のデバイスコンテキスト
	*/
	inline ID3D11DeviceContext*	GetDeviceContext(void) const { return m_pDeviceContext;  }

private:
	ID3D11Device*					m_pDevice;					//!< Direct3Dのデバイス
	ID3D11DeviceContext*			m_pDeviceContext;			//!< Direct3Dのデバイスコンテキスト

	/** コピー禁止 */
	SL_DISALLOW_COPY_AND_ASSIGN(DXDeviceManager);

};	// class DXDeviceManager

}	// namespace sl

#endif	// SL_DX_DEVICE_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
