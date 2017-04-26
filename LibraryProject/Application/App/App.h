//==================================================================================================================================//
//!< @file		App.h
//!< @brief		Appクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef APP_H
#define APP_H

#include "sl/sl.h"

namespace app
{

class App
{

public:
	/** Constructor */
	App(void);

	/** Destructor */
	~App(void);

	/** 
	* 初期化関数 
	* @param[in] pGraphicsDevice グラフィックデバイス
	*/
	void Initialize(sl::dx11::GraphicsDevice* pGraphicsDevice);

	/** 破棄関数 */
	void Finalize(void);

	/** 
	 * 更新関数
	 * @return アプリケーションが終了したかどうか true→終了 false→継続
	 */
	bool Update(void);

private:
	sl::dx11::GraphicsDevice*	m_pGraphicsDevice;		//!< sl::dx11::GraphicsDeviceのインスタンスへのポインタ
	sl::dx11::TextureManager*	m_pTextureManager;		//!< sl::dx11::TextureManagerのインスタンスへのポインタ
	sl::dx11::Vertex2DManager*	m_pVertex2DManagaer;	//!< sl::dx11::Vertex2DManagerのインスタンスへのポインタ
	bool						m_IsEnd;				//!< 終了したかどうかのフラグ

	int							m_TexID;
	int							m_VtxID;


	/** コントロール関数 */
	void Control(void);

	/** 描画関数 */
	void Draw(void);

};

}	// namespace app


#endif	// APP_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
