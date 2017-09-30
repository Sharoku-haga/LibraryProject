//==================================================================================================================================//
//!< @file		slDXBlendStateManager.cpp
//!< @brief		sl::DXBlendStateManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/01	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDXBlendStateManager.h"
#include "../../../Utility/slTemplateFunction.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DXBlendStateManager::DXBlendStateManager()
	: m_pDefaultBlendState(NULL)
{}

DXBlendStateManager::~DXBlendStateManager()
{
	SafeReleaseDX(m_pDefaultBlendState);
}

bool DXBlendStateManager::CreateDefaultBlendState(ID3D11Device*	pDevice)
{
	if(m_pDefaultBlendState != NULL)
	{
		return true;
	}

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
	blendDesc.AlphaToCoverageEnable					= false;							// アルファトゥカバレッジをマルチサンプリング テクニックとして使用の有無。現在は無効
	blendDesc.IndependentBlendEnable				= false;							// 同時処理のレンダー ターゲットで独立したブレンディング→TRUE, RenderTarget[0] のメンバーのみが使用→false
	blendDesc.RenderTarget[0].BlendEnable			= true;								// ブレンディングの有無. 現在は設定は有効
	blendDesc.RenderTarget[0].SrcBlend				= D3D11_BLEND_SRC_ALPHA;			// 最初のRGBデータソースを指定
	blendDesc.RenderTarget[0].DestBlend				= D3D11_BLEND_INV_SRC_ALPHA;		// 2番目のRGBデータソースを指定
	blendDesc.RenderTarget[0].BlendOp				= D3D11_BLEND_OP_ADD;				// RGBデータソースの組合せ方法
	blendDesc.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND_ONE;					// 最初のアルファデータソースを指定
	blendDesc.RenderTarget[0].DestBlendAlpha		= D3D11_BLEND_ZERO;					// 2 番目のアルファ データソースを指定
	blendDesc.RenderTarget[0].BlendOpAlpha			= D3D11_BLEND_OP_ADD;				// アルファデータソースの組み合わせ方法. 現在設定は加算
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;		// 書き込みマスク

	if (FAILED(pDevice->CreateBlendState(&blendDesc, &m_pDefaultBlendState)))
	{
		return false;
	}

	return true;
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
