//==================================================================================================================================//
//!< @file		slDX11Library.h
//!< @brief		slDX11Libraryクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_DX11_LIBRARY_H
#define SL_DX11_LIBRARY_H

#include "../slISharokuLibrary.h"

namespace sl
{

namespace dx11
{
	
class Window;

}	// namespace dx11

//======================================================================//
//!< DirectX11のライブラリのFacadeクラス
//======================================================================//
class DX11Library : public ISharokuLibrary
{

public:

	/** Constructor */
	DX11Library(void);

	/** Destructor */
	virtual ~DX11Library(void);

	//-----------------------------------------------------------------//
	// 初期化&破棄関連関数
	//-----------------------------------------------------------------//

	/** 
	* 初期化関数 
	* @param[in] pWinTitle		ウィンドウのタイトル
	* @param[in] winWidth		ウィンドウの横幅
	* @param[in] winHeight		ウィンドウの縦幅
	*/
	virtual void Initialize(t_char*  pWinTitle, int winWidth, int winHeight)override;

	/** 破棄関数 */
	virtual void Finalize(void)override;

	//-----------------------------------------------------------------//
	// Window関連関数
	//-----------------------------------------------------------------//

	/** 
	* ウィンドウ更新関数
	* @return ウィンドウが破棄されたかどうか true = 破棄された false = 破棄されていない
	*/
	virtual bool UpdateWindow(void)override;

	/** 
	* スクリーンモードを変更する関数
	* @param[in] isFullScreen		true→フルスクリーン, false→ウィンドウモード
	*/
	virtual void ChangeWindowMode(bool isFullScreen)override;

	//-----------------------------------------------------------------//
	// 描画関連関数
	//-----------------------------------------------------------------//

	/** 描画開始処理 */
	virtual void StartRender(void)override;

	/** 描画終了処理 */
	virtual void EndRender(void)override;


private:
	dx11::Window*			m_pWindow;
};

}	// namespace sl

#endif // SL_DX11_LIBRARY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
