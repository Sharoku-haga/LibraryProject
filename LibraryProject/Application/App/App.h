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
	* @param[in] pGraphicsDevice �O���t�B�b�N�f�o�C�X
	*/
	void Initialize(sl::dx11::GraphicsDevice* pGraphicsDevice);

	/** �j���֐� */
	void Finalize(void);

	/** 
	 * �X�V�֐�
	 * @return �A�v���P�[�V�������I���������ǂ��� true���I�� false���p��
	 */
	bool Update(void);

private:
	sl::dx11::GraphicsDevice*	m_pGraphicsDevice;		//!< sl::dx11::GraphicsDevice�̃C���X�^���X�ւ̃|�C���^
	sl::dx11::TextureManager*	m_pTextureManager;		//!< sl::dx11::TextureManager�̃C���X�^���X�ւ̃|�C���^
	sl::dx11::Vertex2DManager*	m_pVertex2DManagaer;	//!< sl::dx11::Vertex2DManager�̃C���X�^���X�ւ̃|�C���^
	bool						m_IsEnd;				//!< �I���������ǂ����̃t���O

	int							m_TexID;
	int							m_VtxID;


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
