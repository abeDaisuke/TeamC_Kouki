/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//���\�[�X�̍쐬
		void CreateResourses();
		//�r���[�̍쐬
		void CreateViewLight();
		//�v���[�g�̍쐬
		void CreatePlate();
		//�ǂ�������I�u�W�F�N�g�̍쐬
		void CreateSeekObject();
		//�Œ�̃{�b�N�X�̍쐬
		void CreateFixedBox();
		//�㉺�ړ����Ă���{�b�N�X�̍쐬
		void CreateMoveBox();
		//�q�b�g���鋅�̂̍쐬
		void CreateSphere();
		//�������̃X�v���C�g�쐬
		void CreateTraceSprite();
		//�ǖ͗l�̃X�v���C�g�쐬
		void CreateWallSprite();
		//�X�N���[������X�v���C�g�쐬
		void CreateScrollSprite();
		//����ŉ�]���闧����
		void CreateRollingCube();
		//�`�󂪕ς�鋅��
		void CreateTransSphere();
		//�X�p�[�N�̍쐬
		void CreateSpark();
		//�v���C���[�̍쐬
		void CreatePlayer();
	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
	};


}
//end basecross

