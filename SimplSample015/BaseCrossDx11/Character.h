/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	//class MultiSpark : public MultiParticle;
	//�p�r: �����̃X�p�[�N�N���X
	//--------------------------------------------------------------------------------------
	class MultiSpark : public MultiParticle {
	public:
		//�\�z�Ɣj��
		MultiSpark(shared_ptr<Stage>& StagePtr);
		virtual ~MultiSpark();
		//������
		virtual void OnCreate() override;
		void InsertSpark(const Vector3& Pos);
	};

	//--------------------------------------------------------------------------------------
	///	�������̃X�v���C�g
	//--------------------------------------------------------------------------------------
	class TraceSprite : public GameObject {
		bool m_Trace;
		Vector2 m_StartScale;
		Vector2 m_StartPos;
		float m_TotalTime;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionColor> m_BackupVertices;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	Trace	�����������邩�ǂ���
		@param[in]	StartScale	�����X�P�[��
		@param[in]	StartPos	�����ʒu
		*/
		//--------------------------------------------------------------------------------------
		TraceSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vector2& StartScale, const Vector2& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~TraceSprite();
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
	};


	//--------------------------------------------------------------------------------------
	///	�ǖ͗l�̃X�v���C�g
	//--------------------------------------------------------------------------------------
	class WallSprite : public GameObject {
		bool m_Trace;
		Vector2 m_StartScale;
		Vector2 m_StartPos;
		wstring m_TextureKey;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	TextureKey	�e�N�X�`���L�[
		@param[in]	Trace	�����������邩�ǂ���
		@param[in]	StartScale	�����X�P�[��
		@param[in]	StartPos	�����ʒu
		*/
		//--------------------------------------------------------------------------------------
		WallSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vector2& StartScale, const Vector2& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~WallSprite();
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
	};



	//--------------------------------------------------------------------------------------
	///	�X�N���[������X�v���C�g
	//--------------------------------------------------------------------------------------
	class ScrollSprite : public GameObject {
		bool m_Trace;
		Vector2 m_StartScale;
		Vector2 m_StartPos;
		wstring m_TextureKey;
		float m_TotalTime;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	TextureKey	�e�N�X�`���L�[
		@param[in]	Trace	�����������邩�ǂ���
		@param[in]	StartScale	�����X�P�[��
		@param[in]	StartPos	�����ʒu
		*/
		//--------------------------------------------------------------------------------------
		ScrollSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vector2& StartScale,const Vector2& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~ScrollSprite();
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
	};


	//--------------------------------------------------------------------------------------
	///	����ŉ�]���闧����
	//--------------------------------------------------------------------------------------
	class RollingCube : public GameObject {
		bool m_Trace;
		Vector3 m_StartScale;
		Quaternion m_StartQt;
		Vector3 m_StartPos;
		float m_TotalTime;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionColor> m_BackupVertices;
		//���̃I�u�W�F�N�g��`�悷��J����
		shared_ptr<Camera> m_Camera;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	Trace	�����������邩�ǂ���
		@param[in]	StartScale	�����X�P�[��
		@param[in]	StartQt	������]
		@param[in]	StartPos	�����ʒu
		*/
		//--------------------------------------------------------------------------------------
		RollingCube(const shared_ptr<Stage>& StagePtr,bool Trace,
			const Vector3& StartScale, const Quaternion& StartQt,const Vector3& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~RollingCube();
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���̃I�u�W�F�N�g��`�悷�邽�߂̃J�����𓾂�i�f�t�H���g�̓X�e�[�W�̃r���[����擾�j
		@return	�J������shared_ptr
		*/
		//--------------------------------------------------------------------------------------
		virtual const shared_ptr<Camera>& OnGetDrawCamera() const override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
	};


	//--------------------------------------------------------------------------------------
	///	�`�󂪕ς�鋅��
	//--------------------------------------------------------------------------------------
	class TransSphere : public GameObject {
		wstring m_TextureKey;
		bool m_Trace;
		Vector3 m_StartScale;
		Quaternion m_StartQt;
		Vector3 m_StartPos;
		float m_TotalTime;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionColorTexture> m_BackupVertices;
		//�����^�C���p���_�f�[�^�i�ω�������j
		vector<VertexPositionColorTexture> m_RuntimeVertices;
		//���̃I�u�W�F�N�g��`�悷��J����
		shared_ptr<Camera> m_Camera;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	TextureKey	�e�N�X�`���L�[
		@param[in]	Trace	�����������邩�ǂ���
		@param[in]	StartScale	�����X�P�[��
		@param[in]	StartQt	������]
		@param[in]	StartPos	�����ʒu
		*/
		//--------------------------------------------------------------------------------------
		TransSphere(const shared_ptr<Stage>& StagePtr,const wstring& TextureKey,bool Trace,
			const Vector3& StartScale, const Quaternion& StartQt, const Vector3& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~TransSphere();
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
	};




	//--------------------------------------------------------------------------------------
	//	class SeekObject : public GameObject;
	//	�p�r: �ǂ�������z�u�I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class SeekObject : public GameObject {
		shared_ptr< StateMachine<SeekObject> >  m_StateMachine;	//�X�e�[�g�}�V�[��
		Vector3 m_StartPos;
		float m_BaseY;
		float m_StateChangeSize;
		//���[�e�B���e�B�֐��Q
		//�v���C���[�̈ʒu��Ԃ�
		Vector3 GetPlayerPosition() const;
		//�v���C���[�܂ł̋�����Ԃ�
		float GetPlayerLength() const;
	public:
		//�\�z�Ɣj��
		SeekObject(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos);
		virtual ~SeekObject();
		//������
		virtual void OnCreate() override;
		//�A�N�Z�T
		shared_ptr< StateMachine<SeekObject> > GetStateMachine() const {
			return m_StateMachine;
		}
		//���[�V��������������֐��Q
		void  SeekStartMoton();
		bool  SeekUpdateMoton();
		void  SeekEndMoton();

		void  ArriveStartMoton();
		bool  ArriveUpdateMoton();
		void  ArriveEndMoton();

		//����
		virtual void OnUpdate() override;
		virtual void OnLastUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//	class FarState : public ObjState<SeekObject>;
	//	�p�r: �v���C���[���牓���Ƃ��̈ړ�
	//--------------------------------------------------------------------------------------
	class FarState : public ObjState<SeekObject>
	{
		FarState() {}
	public:
		static shared_ptr<FarState> Instance();
		virtual void Enter(const shared_ptr<SeekObject>& Obj)override;
		virtual void Execute(const shared_ptr<SeekObject>& Obj)override;
		virtual void Exit(const shared_ptr<SeekObject>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class NearState : public ObjState<SeekObject>;
	//	�p�r: �v���C���[����߂��Ƃ��̈ړ�
	//--------------------------------------------------------------------------------------
	class NearState : public ObjState<SeekObject>
	{
		NearState() {}
	public:
		static shared_ptr<NearState> Instance();
		virtual void Enter(const shared_ptr<SeekObject>& Obj)override;
		virtual void Execute(const shared_ptr<SeekObject>& Obj)override;
		virtual void Exit(const shared_ptr<SeekObject>& Obj)override;
	};


	//--------------------------------------------------------------------------------------
	//	�����̃X�N�G�A
	//--------------------------------------------------------------------------------------
	class NumberSquare : public GameObject {
		weak_ptr<SeekObject> m_SeekObject;
		//���̃I�u�W�F�N�g�݂̂Ŏg�p����X�N�G�A���b�V��
		shared_ptr<MeshResource> m_SquareMeshResource;
		//�w�ԍ�
		size_t m_Number;
	public:
		//�\�z�Ɣj��
		NumberSquare(const shared_ptr<Stage>& StagePtr, 
			const shared_ptr<SeekObject>& SeekObjectPtr, size_t Number);
		virtual ~NumberSquare();
		//������
		virtual void OnCreate() override;
		//�ω�
		virtual void OnUpdate() override;
	};





	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//	�p�r: �Œ�̃{�b�N�X
	//--------------------------------------------------------------------------------------
	class FixedBox : public GameObject {
		Vector3 m_Scale;
		Vector3 m_Rotation;
		Vector3 m_Position;
	public:
		//�\�z�Ɣj��
		FixedBox(const shared_ptr<Stage>& StagePtr,
			const Vector3& Scale,
			const Vector3& Rotation,
			const Vector3& Position
		);
		virtual ~FixedBox();
		//������
		virtual void OnCreate() override;
		//����
	};

	//--------------------------------------------------------------------------------------
	//	class MoveBox : public GameObject;
	//	�p�r: �㉺�ړ�����{�b�N�X
	//--------------------------------------------------------------------------------------
	class MoveBox : public GameObject {
		Vector3 m_Scale;
		Vector3 m_Rotation;
		Vector3 m_Position;
	public:
		//�\�z�Ɣj��
		MoveBox(const shared_ptr<Stage>& StagePtr,
			const Vector3& Scale,
			const Vector3& Rotation,
			const Vector3& Position
		);
		virtual ~MoveBox();
		//������
		virtual void OnCreate() override;
		//����
	};

	//--------------------------------------------------------------------------------------
	//	class SphereObject : public GameObject;
	//	�p�r: ��Q����
	//--------------------------------------------------------------------------------------
	class SphereObject : public GameObject {
		Vector3 m_StartPos;
	public:
		//�\�z�Ɣj��
		SphereObject(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos);
		virtual ~SphereObject();
		//������
		virtual void OnCreate() override;
		//����
	};



}
//end basecross
