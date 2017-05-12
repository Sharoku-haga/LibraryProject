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
	*/
	void Initialize(void);

	/** 破棄関数 */
	void Finalize(void);

	/** 
	 * 更新関数
	 * @return アプリケーションが終了したかどうか true→終了 false→継続
	 */
	bool Update(void);

private:

	enum CONTROLLER_BTN
	{
		ATTACK,
		JUMP,
		UP,
		DOWN,
		RIGHT,
		LEFT
	};
	sl::ISharokuLibrary*		m_pLibrary;				//!< ライブラリ
	bool						m_IsEnd;				//!< 終了したかどうかのフラグ
	sl::GraphicsIDs				m_IDs;					//!< グラフィック関連ID群
	sl::SLVECTOR2				m_Pos;					//!< 座標確認

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
