//==================================================================================================================================//
//!< @file		xiGamePad.h
//!< @brief		xi::GamePadクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_XI_GAMEPAD_H
#define SL_XI_GAMEPAD_H

#include <windows.h>
#include <XInput.h>
#include "../../../Common/slInputEnum.h"

namespace sl
{
namespace xi
{

//======================================================================//
//!< XInputのGamePadクラス
//======================================================================//
class GamePad
{

public:
	/** Constructor */
	GamePad(void);

	/** Destructor */
	~GamePad(void);

	/** 状態更新関数 */
	void Update(void);

	/** 
	* チェック関数 
	* @param[in] padPartID	チェックしたいパッドのアクションID. XIGAMEPAD_ACTION_ID参照
	* @param[in] padNum		チェックしたいゲームパッドの番号.デフォルトは0
	* @return 状態
	*/
	DEVICE_STATE CheckState(int actionID, int  padNum = 0);

private:
	/** コントローラーの状態を格納する構造体 */
	struct CONTROLER_STATE
	{
		XINPUT_STATE	m_State;			//!< XInputState
		bool			m_IsConnected;		//!< 接続しているかどうかののフラグ
	};

	static const int		m_PadMaxVal = 4;										//!< パッドの最大接続数
	CONTROLER_STATE			m_Pads[m_PadMaxVal];									//!< ゲームパッド
	DEVICE_STATE			m_CurrentPadState[m_PadMaxVal][XIGAMEPAD_ID_MAX];		//!< 現在のボタンや部位の状態
	DEVICE_STATE			m_OldPadState[m_PadMaxVal][XIGAMEPAD_ID_MAX];			//!< 前のボタンや部位の状態

	/** 
	* ボタンの状態チェック関数 
	* @param[in] actionID	チェックしたいパッドのアクションID(ボタン).XIGAMEPAD_ACTION_ID参照
	* @param[in] padNum		チェックしたいゲームパッドの番号
	* @return 状態
	*/
	DEVICE_STATE CheckButton(int actionID, int padNum);


	/** 
	* ボタン以外の部位の状態チェック関数 
	* @param[in] actionID	チェックしたいパッドのアクションID(ボタン).XIGAMEPAD_ACTION_ID参照
	* @param[in] padNum		チェックしたいゲームパッドの番号
	* @return 状態
	*/
	DEVICE_STATE CheckPart(int actionID, int padNum);

};

}	// namespace xi
}	// namespace sl

#endif	// SL_XI_GAMEPAD_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
