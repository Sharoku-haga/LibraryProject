//==================================================================================================================================//
//!< @file		slDXSamplerStateManager.cpp
//!< @brief		sl::DXSamplerStateManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/01	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDXSamplerStateManager.h"
#include "../../../Utility/slTemplateFunction.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DXSamplerStateManager::DXSamplerStateManager()
	: m_pDefaultSamplerState(NULL)
{}

DXSamplerStateManager::~DXSamplerStateManager()
{
	SafeReleaseDX(m_pDefaultSamplerState);
}

bool DXSamplerStateManager::CreateDefaultSamplerState(ID3D11Device*	pDevice)
{
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
	samplerDesc.Filter			= D3D11_FILTER_MIN_MAG_MIP_LINEAR;		// サンプリング時に使用するフィルタ.線形補間
	//samplerDesc.Filter			= D3D11_FILTER_ANISOTROPIC;			// 異方性補間.
	samplerDesc.AddressU		= D3D11_TEXTURE_ADDRESS_WRAP;			// 0 ～ 1 の範囲外にあるu座標の描画方法.整数区切りごとにテクスチャーを繰り返す設定
	samplerDesc.AddressV		= D3D11_TEXTURE_ADDRESS_WRAP;			// 0 ～ 1 の範囲外にあるv座標の描画方法.整数区切りごとにテクスチャーを繰り返す設定
	samplerDesc.AddressW		= D3D11_TEXTURE_ADDRESS_WRAP;			// 0 ～ 1 の範囲外にあるw座標の描画方法.整数区切りごとにテクスチャーを繰り返す設定
	samplerDesc.MipLODBias		= 0;									// 計算されたミップマップ レベルからのオフセット
	samplerDesc.MaxAnisotropy	= 0;									// Filter に D3D11_FILTER_ANISOTROPIC または D3D11_FILTER_COMPARISON_ANISOTROPIC が指定されている場合に使用
	samplerDesc.ComparisonFunc	= D3D11_COMPARISON_ALWAYS;				// 比較オプション.現在は常に比較は合格の設定
	samplerDesc.MinLOD			= 0;									// アクセスをクランプするミップマップ範囲の下限
	samplerDesc.MaxLOD			= D3D11_FLOAT32_MAX;					// アクセスをクランプするミップマップ範囲の上限

	if (FAILED(pDevice->CreateSamplerState(&samplerDesc, &m_pDefaultSamplerState)))
	{
		return false;
	}
	return true;
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
