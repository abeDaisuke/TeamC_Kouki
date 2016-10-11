/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------


	//���\�[�X�̍쐬
	void GameStage::CreateResourses() {
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		strTexture = DataDir + L"sky.jpg";
		App::GetApp()->RegisterTexture(L"SKY_TX", strTexture);
		strTexture = DataDir + L"wall.jpg";
		App::GetApp()->RegisterTexture(L"WALL_TX", strTexture);
		strTexture = DataDir + L"spark.png";
		App::GetApp()->RegisterTexture(L"SPARK_TX", strTexture);
		strTexture = DataDir + L"number.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);
	}



	//�r���[�ƃ��C�g�̍쐬
	void GameStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrLookAtCamera = ObjectFactory::Create<LookAtCamera>();
		PtrView->SetCamera(PtrLookAtCamera);
		PtrLookAtCamera->SetEye(Vector3(0.0f, 5.0f, -5.0f));
		PtrLookAtCamera->SetAt(Vector3(0.0f, 0.0f, 0.0f));
		//�V���O�����C�g�̍쐬
		auto PtrSingleLight = CreateLight<SingleLight>();
		//���C�g�̐ݒ�
		PtrSingleLight->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);
	}


	//�v���[�g�̍쐬
	void GameStage::CreatePlate() {
		//�X�e�[�W�ւ̃Q�[���I�u�W�F�N�g�̒ǉ�
		auto Ptr = AddGameObject<GameObject>();
		auto PtrTrans = Ptr->GetComponent<Transform>();
		Quaternion Qt;
		Qt.RotationRollPitchYawFromVector(Vector3(XM_PIDIV2, 0, 0));
		Matrix4X4 WorldMat;
		WorldMat.DefTransformation(
			Vector3(200.0f, 200.0f, 1.0f),
			Qt,
			Vector3(0.0f, 0.0f, 0.0f)
		);
		PtrTrans->SetScale(200.0f, 200.0f, 1.0f);
		PtrTrans->SetQuaternion(Qt);
		PtrTrans->SetPosition(0.0f, 0.0f, 0.0f);

		//�`��R���|�[�l���g�̒ǉ�
		auto DrawComp = Ptr->AddComponent<PNTStaticDraw>();
		//�`��R���|�[�l���g�Ɍ`��i���b�V���j��ݒ�
		DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
		//�����ɉe���f�肱�ނ悤�ɂ���
		DrawComp->SetOwnShadowActive(true);

		//�`��R���|�[�l���g�e�N�X�`���̐ݒ�
		DrawComp->SetTextureResource(L"SKY_TX");
	}

	//�ǂ�������I�u�W�F�N�g�̍쐬
	void GameStage::CreateSeekObject() {
		//�I�u�W�F�N�g�̃O���[�v���쐬����
		auto Group = CreateSharedObjectGroup(L"ObjectGroup");
		//�z��̏�����
		vector<Vector3> Vec = {
			{ 0, 0.125f, 10.0f },
			{ 10.0f, 0.125f, 0.0f },
			{ -10.0f, 0.125f, 0.0f },
			{ 0, 0.125f, -10.0f },
		};

		//�z�u�I�u�W�F�N�g�̍쐬
		//�i���o�[�X�N�G�A�̍쐬
		for (size_t count = 0; count < Vec.size(); count++) {
			auto Ptr = AddGameObject<SeekObject>(Vec[count]);
			//�i���o�[�X�N�G�A���쐬���Ċ֘A������
			AddGameObject<NumberSquare>(Ptr, count);
		}

	}



	//�Œ�̃{�b�N�X�̍쐬
	void GameStage::CreateFixedBox() {
		//�z��̏�����
		vector< vector<Vector3> > Vec = {
			{
				Vector3(5.0f, 0.5f, 5.0f),
				Vector3(0.0f, 0.0f, 0.0f),
				Vector3(10.0f, 0.25f, 10.0f)
			},
			{
				Vector3(5.0f, 0.5f, 5.0f),
				Vector3(0.0f, 0.0f, 0.0f),
				Vector3(14.0f, 0.25f, 10.0f)
			},

			{
				Vector3(2.0f, 1.0f, 2.0f),
				Vector3(0, 0, 0),
				Vector3(10.0f, 0.5f, 10.0f)
			},
			{
				Vector3(4.0f, 1.0f, 4.0f),
				Vector3(0, 0, 0),
				Vector3(-10.0f, 0.5f, 10.0f)
			},
			{
				Vector3(10.0f, 0.5f, 10.0f),
				Vector3(-0.5f, 0.0f, -0.5f),
				Vector3(-10.0f, 0.25f, 10.0f)
			},
		};
		//�I�u�W�F�N�g�̍쐬
		for (auto v : Vec) {
			AddGameObject<FixedBox>(v[0], v[1], v[2]);
		}
	}

	//�v���C���[�̍쐬
	void GameStage::CreatePlayer() {
		//�v���[���[�̍쐬
		auto PlayerPtr = AddGameObject<Player>();
		//�V�F�A�z��Ƀv���C���[��ǉ�
		SetSharedGameObject(L"Player", PlayerPtr);
	}

	//�㉺�ړ����Ă���{�b�N�X�̍쐬
	void GameStage::CreateMoveBox() {
		CreateSharedObjectGroup(L"MoveBox");
		AddGameObject<MoveBox>(
			Vector3(5.0f, 0.5f, 5.0f),
			Vector3(0.0f, 0.0f, 0.0f),
			Vector3(0.0f, -0.5f, 20.0f)
			);
	}

	//�q�b�g���鋅�̂̍쐬
	void GameStage::CreateSphere() {
		//�z��̏�����
		vector<Vector3> Vec = {
			{ 20.0f, 0, 25.0f },
			{ 20.0f, 0, 0.0f },
		};
		//�z�u�I�u�W�F�N�g�̍쐬
		for (auto v : Vec) {
			AddGameObject<SphereObject>(v);
		}
	}

	//�������̃X�v���C�g�쐬
	void GameStage::CreateTraceSprite() {
		AddGameObject<TraceSprite>( true,
			Vector2(200.0f, 200.0f), Vector2(-500.0f, -280.0f));
	}


	//�ǖ͗l�̃X�v���C�g�쐬
	void GameStage::CreateWallSprite() {
		AddGameObject<WallSprite>(L"WALL_TX", false,
			Vector2(200.0f, 200.0f), Vector2(500.0f, -280.0f));
	}


	//�X�N���[������X�v���C�g�쐬
	void GameStage::CreateScrollSprite() {
		AddGameObject<ScrollSprite>(L"TRACE_TX",true,
			Vector2(160.0f, 40.0f),Vector2(500.0f,-280.0f));
	}

	//����ŉ�]���闧����
	void GameStage::CreateRollingCube() {
		Quaternion Qt(Vector3(0.0f, 0.0, 1.0), XM_PIDIV4);
		AddGameObject<RollingCube>(true,
			Vector3(64.0f,64.0f,64.0f), 
			Qt,
			Vector3(-440,320,100.0f)
			);

	}

	//�`�󂪕ς�鋅��
	void GameStage::CreateTransSphere() {
		AddGameObject<TransSphere>(
			L"WALL_TX",
			false,
			Vector3(1.0f, 1.0f, 1.0f),
			Quaternion(),
			Vector3(10.0f, 2.0f, 10.0f)
			);
	}




	//�X�p�[�N�̍쐬
	void GameStage::CreateSpark() {
		auto MultiSparkPtr = AddGameObject<MultiSpark>();
		//�V�F�A�z��ɃX�p�[�N��ǉ�
		SetSharedGameObject(L"MultiSpark", MultiSparkPtr);
		//�G�t�F�N�g��Z�o�b�t�@���g�p����
		GetParticleManager()->SetZBufferUse(true);
	}




	void GameStage::OnCreate() {
		try {
			//���\�[�X�̍쐬
			CreateResourses();
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�v���[�g�̍쐬
			CreatePlate();
			//�Œ�̃{�b�N�X�̍쐬
			CreateFixedBox();
			//�㉺�ړ����Ă���{�b�N�X�̍쐬
			CreateMoveBox();
			//���̍쐬
			CreateSphere();
			//�ǂ�������I�u�W�F�N�g�̍쐬
			CreateSeekObject();
			//�������̃X�v���C�g�쐬
			CreateTraceSprite();
			//�ǖ͗l�̃X�v���C�g�쐬
			CreateWallSprite();
			//�X�N���[������X�v���C�g�쐬
			CreateScrollSprite();
			//����ŉ�]���闧����
			CreateRollingCube();
			//����Ō`�󂪕ς�鋅��
			CreateTransSphere();
			//�X�p�[�N�̍쐬
			CreateSpark();
			//�v���[���[�̍쐬
			CreatePlayer();
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
