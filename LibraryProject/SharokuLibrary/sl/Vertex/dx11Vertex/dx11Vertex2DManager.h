//==================================================================================================================================//
//!< @file		dx11Vertex2DManager.h
//!< @brief		dx11::Vertex2DManagerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef DX11_VERTEX2D_MANAGER_H
#define DX11_VERTEX2D_MANAGER_H

#include <d3dx11.h>
#include <d3dx10.h>
#include <vector>
#include "../../Common/slDefine.h"
#include "dx11Vertex2D.h"
#include "../../Graphics/dx11GraphicsDevice/dx11GraphicsDevice.h"

namespace sl
{
namespace dx11
{

class Vertex2DManager
{

public:
	/** Constructor */
	Vertex2DManager(void);

	/** Destructor */
	~Vertex2DManager(void); 

	/** 
	* 初期化関数
	* @param[in]
	* @return 結果 true→成功 false→失敗
	*/
	bool Initialize(GraphicsDevice* pGraphicsDevice);

	/** 破棄関数 */
	void Finalize(void);

	/**
	* 頂点バッファを生成する関数
	* @param[in] rSize	サイズ
	* @param[in] rUV	UV
	* @return	登録した頂点バッファのID
	*/
	int CreateVertex(const fRect& rSize, const fRect& rUV);

	/** 
	* 指定した頂点を解放する関数
	* @param[in] id 解放したい頂点のid
 	*/
	void ReleaseVertex2D(int id);

	/** 登録している頂点バッファを全て解放する関数 */
	void ReleaseALL(void);

	/** 使用するシェーダーをセットアップする関数 */
	void SetupShadar(void);

	/** 使用するブレンドステイトをセットアップする関数 */
	void SetupBlendState(void);

	/**
	* コンスタントバッファをセットアップ(書き込む)する関数
	* @param[in] pos		位置座標
	* @param[in] scale		スケール. デフォルト値はD3DXVECTOR3(1.f, 1.f, 1.f)
	* @param[in] angle		角度
	*/
	void SetupConstantBuffer(const D3DXVECTOR2& pos, const D3DXVECTOR3& scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f), float angle = 0.0f);
	/**
	* 指定した頂点バッファの取得する関数	
	* @param[in] index 
	* @return 指定したバックバッファを取得する関数
	*/
	ID3D11Buffer* GetBuffer(int index) { return m_Vertex2Ds[index]->GetBuffer(); } 

	/**
	* 頂点数を取得する関数.2Dので4つ
	* @return 頂点数
	*/
	int GetVertexCount(void) { return m_VertexCount; }

private:
	static const int			m_VertexCount = 4;				//!< 頂点数
	ID3D11Device*				m_pDevice;						//!< デバイス
	ID3D11DeviceContext*		m_pDeviceContext;				//!< デバイスコンテキスト	
	HWND						m_hWnd;							//!< 結びついているハンドル
	ID3D11VertexShader*			m_pVertexShader;				//!< バーテックスシェーダー
	ID3DBlob*					m_pVertexCompiledShader;		//!< バーテックスシェーダーのブロフ
	ID3D11InputLayout*			m_pVertexLayout;				//!< 頂点レイアウト
	ID3D11PixelShader*			m_pPixelShader;					//!< ピクセルシェーダー
	ID3D11BlendState*			m_pBlendState;					//!< ブレンドステイト
	ID3D11Buffer*				m_pConstantBuffer;				//!< コンスタントバッファ
	std::vector<Vertex2D*>		m_Vertex2Ds;					//!< Veretex2Dを格納する動的配列 
	float						m_ClientWidth;					//!< クライアント領域の横幅
	float						m_ClientHeight;					//!< クライアント領域の縦幅

	/**
	 * コンスタントバッファ
	 * 定数バッファは16バイト区切りにする
	 */
	struct SHADER_CONSTANT_BUFFER
	{
		D3DXMATRIX  m_MatWorld;			//!< ワールド変換行列
		D3DXVECTOR4 m_WindowSize;		//!< ウィンドウの縦横サイズ
	};

	/**
	 * 頂点シェーダーの初期化関数
	 * @return 結果 true→成功 false→失敗
	 */
	bool InitVertexShader(void);

	/**
	 * 頂点入力レイアウトの初期化関数
	 * @return 結果 true→成功 false→失敗
	 */
	bool InitVertexLayout(void);

	/**
	 * ピクセルシェーダーの初期化関数
	 * @return 結果 true→成功 false→失敗
	 */
	bool InitPixelShader(void);

	/**
	 * ブレンドステートの初期化関数
	 * @return 結果 true→成功 false→失敗
	 */
	bool InitBlendState(void);

	/**
	 * 定数バッファの初期化関数
	 * @return 結果 true→成功 false→失敗
	 */
	bool InitConstantBuffer(void);

};

}	// namespace dx11
}	// namespace sl

#endif	// DX11_VERTEX2D_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
