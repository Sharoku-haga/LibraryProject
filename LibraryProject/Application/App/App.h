//==================================================================================================================================//
//!< @file		App.h
//!< @brief		App�N���X�w�b�_
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
	* �������֐� 
	*/
	void Initialize(void);

	/** �j���֐� */
	void Finalize(void);

	/** 
	 * �X�V�֐�
	 * @return �A�v���P�[�V�������I���������ǂ��� true���I�� false���p��
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
	sl::ISharokuLibrary*		m_pLibrary;				//!< ���C�u����
	bool						m_IsEnd;				//!< �I���������ǂ����̃t���O
	sl::GraphicsIDs				m_IDs;					//!< �O���t�B�b�N�֘AID�Q
	sl::SLVECTOR2				m_Pos;					//!< ���W�m�F

	/** �R���g���[���֐� */
	void Control(void);

	/** �`��֐� */
	void Draw(void);

};

}	// namespace app


#endif	// APP_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
