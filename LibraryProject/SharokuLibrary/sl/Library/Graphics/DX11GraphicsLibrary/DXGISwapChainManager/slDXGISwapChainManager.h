//==================================================================================================================================//
//!< @file		slDXGISwapChainManager.h
//!< @brief		sl::DXGISwapChainManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/09/29	更新履歴：
//==================================================================================================================================//

#ifndef SL_DXGI_SWAP_CHAIN_MANAGER_H
#define SL_DXGI_SWAP_CHAIN_MANAGER_H

#include <windows.h>
#include <d3dx11.h>
#include "../../../Utility/slRect.h"

namespace sl
{

struct WindowHandle;

//===================================================================================//
//!< DXGIのスワップチェイン関連を管理するクラス
//===================================================================================//
class DXGISwapChainManager
{

public:
	/** Constructor */
	DXGISwapChainManager();

	/** Destructor */
	~DXGISwapChainManager();

	/** 
	* DXGIのスワップチェイン関連を生成する関数
	* @param[in] rHandle			関連付けたいウィンドウハンドル
	* @param[in] pDevice			DirectXデバイス
	* @param[in] rBackbufferSize	設定したいバックバッファのサイズ
	*/
	bool CreateDXGISwapChain(const WindowHandle& rHandle, ID3D11Device* pDevice, const fRect& rBackbufferSize);

	/** 
	* 出力スクリーンモードを変更する関数
	* @param[in] isFullScreen		true→フルスクリーン, false→ウィンドウ
	*/
	void ChangeScreenMode(bool isFullScreen);

	/**
	* Getter
	* @return スワップチェインへのポインタ
	*/
	inline IDXGISwapChain* GetDXGISwapChain() const { return m_pDXGISwapChain; }

private:
	IDXGISwapChain*					m_pDXGISwapChain;			//!< スワップチェイン
	IDXGIDevice1*					m_pDXGI;					//!< DXGIオブジェクトを使用するためのインターフェイス
	IDXGIAdapter*					m_pDXGIAdapter;				//!< ディスプレイサブシステムを扱うためのインターフェイス
	IDXGIFactory*					m_pDXGIFactory;				//!< DXGIの各種インターフェイスを取得するためのインターフェイス

};	// class DXGISwapChainManager

}	// namespace sl

#endif	// SL_DXGI_SWAP_CHAIN_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
