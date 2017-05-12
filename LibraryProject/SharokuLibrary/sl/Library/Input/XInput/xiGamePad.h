//==================================================================================================================================//
//!< @file		xiGamePad.h
//!< @brief		xi::GamePad�N���X�w�b�_
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
//!< XInput��GamePad�N���X
//======================================================================//
class GamePad
{

public:
	/** Constructor */
	GamePad(void);

	/** Destructor */
	~GamePad(void);

	/** ��ԍX�V�֐� */
	void Update(void);

	/** 
	* �`�F�b�N�֐� 
	* @param[in] padPartID	�`�F�b�N�������p�b�h�̃A�N�V����ID. XIGAMEPAD_ACTION_ID�Q��
	* @param[in] padNum		�`�F�b�N�������Q�[���p�b�h�̔ԍ�.�f�t�H���g��0
	* @return ���
	*/
	DEVICE_STATE CheckState(int actionID, int  padNum = 0);

private:
	/** �R���g���[���[�̏�Ԃ��i�[����\���� */
	struct CONTROLER_STATE
	{
		XINPUT_STATE	m_State;			//!< XInputState
		bool			m_IsConnected;		//!< �ڑ����Ă��邩�ǂ����̂̃t���O
	};

	static const int		m_PadMaxVal = 4;										//!< �p�b�h�̍ő�ڑ���
	CONTROLER_STATE			m_Pads[m_PadMaxVal];									//!< �Q�[���p�b�h
	DEVICE_STATE			m_CurrentPadState[m_PadMaxVal][XIGAMEPAD_ID_MAX];		//!< ���݂̃{�^���╔�ʂ̏��
	DEVICE_STATE			m_OldPadState[m_PadMaxVal][XIGAMEPAD_ID_MAX];			//!< �O�̃{�^���╔�ʂ̏��

	/** 
	* �{�^���̏�ԃ`�F�b�N�֐� 
	* @param[in] actionID	�`�F�b�N�������p�b�h�̃A�N�V����ID(�{�^��).XIGAMEPAD_ACTION_ID�Q��
	* @param[in] padNum		�`�F�b�N�������Q�[���p�b�h�̔ԍ�
	* @return ���
	*/
	DEVICE_STATE CheckButton(int actionID, int padNum);


	/** 
	* �{�^���ȊO�̕��ʂ̏�ԃ`�F�b�N�֐� 
	* @param[in] actionID	�`�F�b�N�������p�b�h�̃A�N�V����ID(�{�^��).XIGAMEPAD_ACTION_ID�Q��
	* @param[in] padNum		�`�F�b�N�������Q�[���p�b�h�̔ԍ�
	* @return ���
	*/
	DEVICE_STATE CheckPart(int actionID, int padNum);

};

}	// namespace xi
}	// namespace sl

#endif	// SL_XI_GAMEPAD_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
