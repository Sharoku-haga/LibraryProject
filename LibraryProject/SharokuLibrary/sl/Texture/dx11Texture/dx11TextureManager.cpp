//==================================================================================================================================//
//!< @file		dx11TextureManager.cpp
//!< @brief		dx11::TextureManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "../../Common/slTemplate.h"
#include "dx11TextureManager.h"

/* Namespace -------------------------------------------------------------------------------------------------- */

namespace sl
{
namespace dx11
{

/* Public Functions ------------------------------------------------------------------------------------------- */

TextureManager::TextureManager(ID3D11Device* pDevice, ID3D11DeviceContext*	pDeviceContext)
	: m_pDevice(pDevice)
	, m_pDeviceContext(pDeviceContext)
	, m_pSamplerState(NULL)
{
	if(RESULT_FAILED(InitSamplerState()))
	{
		MessageBox(0, "サンプラーの作成に失敗しました", NULL, MB_OK);
	}
}

TextureManager::~TextureManager(void)
{
	ReleaseALL();
	ReleaseSafely(m_pSamplerState);
}

int TextureManager::LoadTexture(const t_char* pFileName)
{
	D3DX11_IMAGE_LOAD_INFO loadImageInfo;							// テクスチャーを読み込む方法を制御するための情報
	ZeroMemory(&loadImageInfo, sizeof(D3DX11_IMAGE_LOAD_INFO));

	/**@note D3DX11_DEFAULTを指定すれば自動的にソースファイルから取得した値を使用する */
	loadImageInfo.Width				= D3DX11_DEFAULT;				// テクスチャーの横幅
	loadImageInfo.Height			= D3DX11_DEFAULT;				// テクスチャーの縦幅
	loadImageInfo.Depth				= D3DX11_DEFAULT;				// テクスチャーの深度
	loadImageInfo.FirstMipLevel		= D3DX11_DEFAULT;				// テクスチャーの最高解像度のミップマップレベル
	loadImageInfo.MipLevels			= 1;							// テクスチャー内のミップマップ レベルの最大数
	loadImageInfo.Usage				= D3D11_USAGE_DEFAULT;			// テクスチャー リソースの用途. 現在はGPUによる読み取りおよび書き込みアクセスを必要とするリソースとして設定.
	loadImageInfo.BindFlags			= D3D11_BIND_SHADER_RESOURCE;	// リソースをパイプラインにバインドする方法
	loadImageInfo.CpuAccessFlags	= 0;							// CPU がテクスチャー リソースに対して持つアクセス許可。基本的に設定しない方がいい(最適化が行われるため)
	loadImageInfo.MiscFlags			= 0;							// その他リソースのプロパティ。D3D11_RESOURCE_MISC_FLAGで色々と設定できるらしい
	loadImageInfo.Format			= DXGI_FORMAT_FROM_FILE;		// テクスチャーの読み込み後のフォーマット.現在は既定値.
	//loadImageInfo.Format			= DXGI_FORMAT_R32G32B32A32_FLOAT;
	loadImageInfo.Filter			= D3DX11_FILTER_POINT;			// テクスチャーのフィルタリングの設定(再サンプリング時のみ).現在は元のイメージから最も近いピクセルのサンプリングで計算する設定
	loadImageInfo.MipFilter			= D3DX11_FILTER_POINT;			// テクスチャー ミップレベルのフィルタリング(ミップマップを生成する場合のみ).現在は元のイメージから最も近いピクセルのサンプリングで計算する設定
	loadImageInfo.pSrcInfo			= NULL;							// オリジナルイメージに関する情報. 現在はなしで設定

	ID3D11ShaderResourceView* pResourceView = NULL;
	int texID = INT_MAX;			// 適当な値で初期化(0で初期化しないのはIDに登録される為)
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(
		m_pDevice,
		pFileName,
		&loadImageInfo,
		NULL,
		&pResourceView,
		NULL)))
	{
		/** @todo ここの部分はデバックウィンドウに表示できるように変更した方がいいかもしれない */
		MessageBox(0, "テクスチャが読み込めません。", NULL, MB_OK);
		OutputDebugString(pFileName);
		return texID;
	}
	else
	{
		texID = m_pTextureRV.size();
	}
	m_pTextureRV.push_back(pResourceView);
	return texID;
}

void TextureManager::SetUpTexture(int id)
{
	//m_pDeviceContext->VSSetSamplers(0, 1, &m_pSamplerState);
	//m_pDeviceContext->VSSetShaderResources(0, 1, &m_pTextureRV[id]);
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSamplerState);
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureRV[id]);
}

void TextureManager::Release(int id)
{
	m_pTextureRV[id]->Release();
	m_pTextureRV[id] = NULL;
}

void TextureManager::ReleaseALL(void)
{
	for(auto& texRV : m_pTextureRV)
	{
		if(texRV != NULL)
		{
			texRV->Release();
			texRV = NULL;
		}
	}
	std::vector<ID3D11ShaderResourceView*>().swap(m_pTextureRV);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

bool TextureManager::InitSamplerState(void)
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

	if (FAILED(m_pDevice->CreateSamplerState(&samplerDesc, &m_pSamplerState)))
	{
		MessageBox(0, "SamplerStateの設定に失敗しました", NULL, MB_OK);
		return false;
	}
	return true;
}

}	// namespace dx11
}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
