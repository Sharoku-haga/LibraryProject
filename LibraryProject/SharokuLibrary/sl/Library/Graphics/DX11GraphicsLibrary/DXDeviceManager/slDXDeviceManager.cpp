//==================================================================================================================================//
//!< @file		slDXDeviceManager.cpp
//!< @brief		sl::DXDeviceManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/09/29	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDXDeviceManager.h"
#include "../../../Utility/slTemplateFunction.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DXDeviceManager::DXDeviceManager()
	: m_pDevice(NULL)
	, m_pDeviceContext(NULL)
{}

DXDeviceManager::~DXDeviceManager()
{
	sl::SafeReleaseDX(m_pDeviceContext);
	sl::SafeReleaseDX(m_pDevice);
}

bool DXDeviceManager::CreateDevice()
{
	// デバイス作成時に使用するビデオカードの性能一覧
	/** @todo 現在はシェーダー モデル 5 などの Direct3D 11.0 でサポートされている機能のみに限定 */
	D3D_FEATURE_LEVEL	pFeatureLevels[] = { D3D_FEATURE_LEVEL_11_0 };		

	D3D_FEATURE_LEVEL				adoptedFeatureLevel;				//!< 採用されたフィーチャーレベル(確認用変数)

	HRESULT hr = D3D11CreateDevice(
		NULL,								// 使用するアダプターを設定。NULLの場合はデフォルトのアダプター。
		D3D_DRIVER_TYPE_HARDWARE,			// ドライバーの種類。pAdapterが NULL 以外の場合は、D3D_DRIVER_TYPE_UNKNOWNを指定する。
		NULL,								// ソフトウェアラスタライザを実装するDLLへのハンドル。D3D_DRIVER_TYPE を D3D_DRIVER_TYPE_SOFTWARE に設定している場合は NULL にできない。
		0,									// デバイスを作成時に使用されるパラメータ
		pFeatureLevels,						// D3D_FEATURE_LEVELのポインタ
		1,									// D3D_FEATURE_LEVEL配列の要素数
		D3D11_SDK_VERSION,					// DirectX SDKのバージョン
		&m_pDevice,							// 初期化されたデバイス
		&adoptedFeatureLevel,				// 採用されたフィーチャーレベル
		&m_pDeviceContext);					// 初期化されたデバイスコンテキスト

	if(FAILED(hr))
	{
		return false;
	}

	return true;
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
