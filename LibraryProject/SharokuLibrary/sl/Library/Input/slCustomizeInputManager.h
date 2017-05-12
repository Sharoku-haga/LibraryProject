//==================================================================================================================================//
//!< @file		slCustomizeInputManager.h
//!< @brief		sl::CustomizeInputManager�N���X�w�b�_
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_CUSTOMIZE_INPUT_MANAGER_H
#define SL_CUSTOMIZE_INPUT_MANAGER_H

#include <map>
#include "../../Common/slInputEnum.h"

namespace sl
{

namespace di
{

class InputManager;
class KeyDevice;

}	// namespace di

namespace xi
{

class GamePad;

}

//======================================================================//
//!< Input�̐ݒ���J�X�^�}�C�Y���A���̐ݒ���Ǘ�����N���X<br>
//!< �����ł���Input�̐ݒ�Ƃ̓L�[�Ȃǂ�Input�f�o�C�X�̃{�^���Ȃǂ�
//!< �N���C�A���g���Ŏ��R��ID��ݒ肵�Ďg����悤�ɂ��邱��
//======================================================================//
class CustomizeInputManager
{

public:

	/** 
	* Contructor
	* @param[in] pInputManager di::InputManager�̃C���X�^���X�ւ̃|�C���^
	* @param[in] pGamePad	   xi::GamePad�̃C���X�^���X�ւ̃|�C���^
	*/
	CustomizeInputManager(di::InputManager* pInputManager, xi::GamePad* pGamePad);

	/** Destructor */
	~CustomizeInputManager(void);

	/** 
	* �o�^�֐�
	* @param[in] ID			�o�^������ID
	* @param[in] device		�f�o�C�X�^�C�v
	* @param[in] inputType	�o�^�������C���v�b�g�^�C�v
	*/
	void RegisterCustomizeType(int ID, HID_TYPE device, int inputType);

	/** 
	* ��ԃ`�F�b�N�֐�
	* @param[in] ID			�o�^����ID
	* @param[in] deviceNum	�f�o�C�X�ԍ�.�f�t�H���g��0
	*/
	DEVICE_STATE CheckState(int ID, int deviceNum = 0);

private:
	/** �J�X�^�}�C�Y���\���� */
	struct CUSTOMIZE_INFO
	{
		HID_TYPE	m_DeviceType;			//!< �f�o�C�X�^�C�v
		int			m_InputType;			//!< �C���v�b�g�^�C�v
	};

	di::KeyDevice*					m_pKeyDevice;			//!< di::KeyDevice�N���X�̃C���X�^���X�ւ̃|�C���^
	xi::GamePad*					m_pXiGamePad;			//!< xi::GamePad�N���X�̃C���X�^���X�ւ̃|�C���^
	std::map<int, CUSTOMIZE_INFO>	m_CustomizeInfos;		//!< �J�X�^�}�C�Y���������i�[����map

};

}	// namespace sl

#endif	//SL_CUSTOMIZE_INPUT_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
