//==================================================================================================================================//
//!< @file		slDXRasterizerStateManager.cpp
//!< @brief		sl::DXRasterizerStateManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/01	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDXRasterizerStateManager.h"
#include "../../../Utility/slTemplateFunction.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DXRasterizerStateManager::DXRasterizerStateManager()
	: m_pDefaultRasterizerState(NULL)
{}

DXRasterizerStateManager::~DXRasterizerStateManager()
{
	SafeReleaseDX(m_pDefaultRasterizerState);
}

bool DXRasterizerStateManager::CreateDefaultRasterizerState(ID3D11Device*	pDevice)
{
	// ラスタライザを設定
	/** @todo この辺りの設定は面白そうなので後でさわってみる */
	D3D11_RASTERIZER_DESC rasterizerDesc;
	rasterizerDesc.FillMode					= D3D11_FILL_SOLID;			// レンダリング時に使用する描画モード. 現在はポリゴン描画モード
	rasterizerDesc.CullMode					= D3D11_CULL_BACK;			// 特定の方向を向いている三角形の描画の有無の指定. 後ろ向きの三角形を描画しない指定をしている
	rasterizerDesc.FrontCounterClockwise	= FALSE;					// 三角形が前向きか後ろ向きかを決定する。時計回りを表面
//	rasterizerDesc.FrontCounterClockwise	= TRUE;						// 反時計回りを表面
	rasterizerDesc.DepthBias				= 0;						// 指定のピクセルに加算する深度値. 今回は0.0f。
	rasterizerDesc.DepthBiasClamp			= 0.0f;						// ピクセルの最大深度バイアス(同一平面上に存在しないかのように表示するためののもの). 今回は0.0f。
	rasterizerDesc.SlopeScaledDepthBias		= 0.0f;						// 指定のピクセルのスロープに対するスカラ
	rasterizerDesc.DepthClipEnable			= FALSE;					// 距離に基づいてクリッピング. 今回は無効.
	rasterizerDesc.ScissorEnable			= FALSE;					// シザー矩形カリング. 今回は無効.
	rasterizerDesc.MultisampleEnable		= FALSE;					// マルチサンプリングのアンチエイリアシング. 今回は無効.
	rasterizerDesc.AntialiasedLineEnable	= FALSE;					// 線のアンチエイリアシング(線を描画中で MultisampleEnable が false の場合にのみ適用).今回は無効.

	// 設定を元に作成
	if(FAILED(pDevice->CreateRasterizerState(&rasterizerDesc, &m_pDefaultRasterizerState)))
	{
		return false;
	}
	return true;
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
