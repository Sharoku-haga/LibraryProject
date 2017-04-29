//==================================================================================================================================//
//!< @file		dx11Vertex2D.h
//!< @brief		dx11::Vertex2Dクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef DX11_VERTEX2D_H
#define DX11_VERTEX2D_H

#include <d3dx11.h>
#include <d3dx10.h>
#include "../../../Common/slDefine.h"
#include "../../../Common/slStruct.h"

namespace sl
{
namespace dx11
{

/** 基本頂点情報 */
struct BasicVertex
{
	D3DXVECTOR3		m_Pos;			//!< 位置情報
	D3DXCOLOR		m_Color;		//!< 色情報
	D3DXVECTOR2		m_UV;			//!< テクスチャーのUV情報
};

//======================================================================//
//!< DirectX11の2Dの頂点情報のクラス
//======================================================================//
class Vertex2D
{

public:
	/** 
	* Constructor
	* @param[in] pDevice			デバイス
	* @param[in] pDeviveContext		デバイスコンテクスト
	*/
	Vertex2D(ID3D11Device* pDevice, ID3D11DeviceContext*	pDeviceContext);

	/** Destructor */
	~Vertex2D(void);

	/** バッファ解放関数 */
	void ReleaseBuffer(void);

	/** 
	* 2Dの頂点情報を作成する関数
	* @param[in] rSize		サイズ
	* @param[in] rUV		UV値
	* @return	結果 true→成功 false→失敗
	*/
	bool CreateNewBuffer(const fRect& rSize, const fRect& rUV);

	/** 
	* バッファを取得する関数
	* @return 生成したバッファ
	*/
	inline ID3D11Buffer* GetBuffer() const{ return m_pVertexBuffer; }

	/** 
	* サイズ情報を設定する関数
	* @param[in] size	設定したいサイズ
	*/
	void SetSize(fRect size);

	/**
	* UV情報を設定する関数
	* @param[in] uv		設定したいUV値
	*/
	void SetUV(fRect uv);

	/**
	* 色情報を設定する関数
	* @param[in] color
	*/
	void SetColor(D3DXCOLOR color);

private:
	static const int							m_VertexCount = 4;			//!< 頂点数
	ID3D11Device*								m_pDevice;					//!< Direct3Dのデバイス
	ID3D11DeviceContext*						m_pDeviceContext;			//!< Direct3Dのコンテキスト
	ID3D11Buffer*								m_pVertexBuffer;			//!< 頂点バッファ
	BasicVertex									m_Vertexs[m_VertexCount];	//!< 頂点情報管理の配列

	/** 
	* 2Dの頂点情報を作成する関数
	* @return	結果 true→成功 false→失敗
	*/
	bool CreateBuffer(void);
			
};

}	// namespace dx11
}	// namespace sl

#endif	// DX11_VERTEX2D_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
