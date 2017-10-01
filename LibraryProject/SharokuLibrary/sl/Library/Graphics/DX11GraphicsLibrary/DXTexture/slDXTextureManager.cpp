//==================================================================================================================================//
//!< @file		slDXTextureManager.cpp		
//!< @brief		sl::DXTextureManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/01	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDXTextureManager.h"
#include "../../../Utility/slTemplateFunction.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DXTextureManager::DXTextureManager(ID3D11Device* pDevice)
	: m_pDevice(pDevice)
{}

DXTextureManager::~DXTextureManager()
{
	ReleaseALL();
}

TextureID DXTextureManager::LoadTexture(const t_char* pFileName)
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
		MessageBox(0, "テクスチャが読み込めません。", NULL, MB_OK);
		OutputDebugString(pFileName);
		return TextureID(texID);
	}
	else
	{
		texID = m_pTextureRV.size();
	}
	m_pTextureRV.push_back(pResourceView);

	return TextureID(texID);
}

void DXTextureManager::Release(const TextureID& rID)
{
	SafeReleaseDX(m_pTextureRV[rID.m_Num]);
}

void DXTextureManager::ReleaseALL(void)
{
	for(auto& pTexRV : m_pTextureRV)
	{
		SafeReleaseDX(pTexRV);
	}
	std::vector<ID3D11ShaderResourceView*>().swap(m_pTextureRV);
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
