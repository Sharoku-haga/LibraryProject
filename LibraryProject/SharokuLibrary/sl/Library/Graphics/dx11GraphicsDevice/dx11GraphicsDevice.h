//==================================================================================================================================//
//!< @file		dx11GraphicsDevice.h
//!< @brief		dx11::GraphicsDeviceクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_DX11_GRAPHICS_DEVICE_H
#define SL_DX11_GRAPHICS_DEVICE_H

#include <windows.h>
//#include <d3dx10.h>
#include <d3dx11.h>
#include "../../../Common/slDefine.h"

namespace sl
{
namespace dx11
{

//======================================================================//
//!< DirectX11のDevice関連クラス
//======================================================================//
class GraphicsDevice
{

public:
	/** Constructor */
	GraphicsDevice(void);

	/** Desutructor */
	~GraphicsDevice(void);

	/** コピー禁止 */
	SL_DISALLOW_COPY_AND_ASSIGN(GraphicsDevice);

	/**
	* 初期化関数
	* @param[in] hWnd 結び付けたいウィンドウのハンドル
	* @return 結果 true→成功, flase→失敗
	*/
	bool Initialize(HWND hWnd);

	/** 
	* 終了関数
	* @attention 明示的に終了したい場合だけ使用すること
	*/
	void Finalize(void);

	/** 描画開始処理 */
	void StartRender(void);

	/** 描画終了処理 */
	void EndRender(void);

	/** 
	* スクリーンモードを変更する関数
	* @param[in] isFullScreen		true→フルスクリーン, false→ウィンドウモード
	*/
	void ChangeWindowMode(bool isFullScreen);

	/** Getter -------------------------------------------- */

	/**
	* デバイスを取得する関数
	* @return DirectX11のデバイス
	*/
	inline ID3D11Device*			GetDevice(void) { return m_pDevice;  }

	/**
	* デバイスコンテキストを取得する関数
	* @return DirectX11のデバイス
	*/
	inline ID3D11DeviceContext*		GetDeviceContext(void) { return m_pDeviceContext; }

	/**
	* 結びついているハンドルを取得する関数
	* @return ウィンドウハンドル
	*/
	inline HWND	GetHWnd(void) { return m_hWnd;  }

private:
	HWND							m_hWnd;						//!< 結びついてるウィンドウのハンドル
	ID3D11Device*					m_pDevice;					//!< Direct3Dのデバイス
	ID3D11DeviceContext*			m_pDeviceContext;			//!< Direct3Dのデバイスコンテキスト
	D3D_FEATURE_LEVEL				m_FeatureLevel;				//!< フィーチャーレベル
	IDXGISwapChain*					m_pDXGISwapChain;			//!< スワップチェイン
	IDXGIDevice1*					m_pDXGI;					//!< DXGIオブジェクトを使用するためのインターフェイス
	IDXGIAdapter*					m_pDXGIAdapter;				//!< ディスプレイサブシステムを扱うためのインターフェイス
	IDXGIFactory*					m_pDXGIFactory;				//!< DXGIの各種インターフェイスを取得するためのインターフェイス
	ID3D11RenderTargetView*			m_pRenderTargetView;		//!< レンダリングターゲットビュー
	ID3D11DepthStencilView*			m_pDepthStencilView;		//!< 深度ステンシルビュー
	ID3D11Texture2D*				m_pDepthStencilBuffer;		//!< 深度ステンシルバッファ
	ID3D11RasterizerState*			m_pRasterizerState;			//!< ラスタライザの設定

	/** 
	* DeviceとDeviceContextの初期化関数
	* @return 結果 true→成功, flase→失敗
	*/
	bool InitDevice(void);

	/** 
	* DXGI関連の初期化関数
	* @return 結果 true→成功, flase→失敗
	*/
	bool InitDXGI(HWND hWnd);

	/** 
	* View関連の初期化関数 
	* @return 結果 true→成功, flase→失敗	
	*/
	bool InitView(void);

	/**
	* ラスタライザの初期化関数
	* @return 結果 true→成功, flase→失敗
	*/
	bool InitRasterizerState(void);

	/** DeviceとDeviceContextの解放関数 */
	void ReleaseDevice(void);

	/** DXGI関連の解放関数 */
	void ReleaseDXGI(void);

	/** View関連の解放関数 */
	void ReleaseView(void);

};	// class GraphicsDevice

}	// namespace dx11
}	// namespace sl

#endif	// SL_DX11_GRAPHICS_DEVICE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
