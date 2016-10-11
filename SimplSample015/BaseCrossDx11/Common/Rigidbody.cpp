/*!
@file Rigidbody.h
@brief �����v�Z�R���|�[�l���g����
*/
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	struct SteeringComponent::Impl;
	//	�p�r: �R���|�[�l���gImpl�N���X
	//--------------------------------------------------------------------------------------
	struct SteeringComponent::Impl {
		float m_Weight;
		Impl() :
			m_Weight(1.0f)
		{}
		~Impl() {}
	};



	//--------------------------------------------------------------------------------------
	//	class SteeringComponent : public Component ;
	//	�p�r: ���ǃR���|�[�l���g�̐e�N���X
	//--------------------------------------------------------------------------------------
	SteeringComponent::SteeringComponent(const shared_ptr<GameObject>& GameObjectPtr) :
		Component(GameObjectPtr),
		pImpl(new Impl())
	{}
	SteeringComponent::~SteeringComponent() {}

	float SteeringComponent::GetWeight() const { return pImpl->m_Weight; }
	void SteeringComponent::SetWeight(float f) { pImpl->m_Weight = f; }




	//--------------------------------------------------------------------------------------
	//	struct SeekSteering::Impl;
	//	�p�r: �R���|�[�l���gImpl�N���X
	//--------------------------------------------------------------------------------------
	struct SeekSteering::Impl {
		Vector3 m_TargetPosition;
		Impl() :
			m_TargetPosition(0, 0, 0)
		{}
		~Impl() {}
	};

	//--------------------------------------------------------------------------------------
	//	class SeekSteering : public SteeringComponent;
	//	�p�r: Seek����
	//--------------------------------------------------------------------------------------
	SeekSteering::SeekSteering(const shared_ptr<GameObject>& GameObjectPtr) :
		SteeringComponent(GameObjectPtr),
		pImpl(new Impl())
	{
		auto PtrT = GetGameObject()->GetComponent<Transform>();
		if (PtrT) {
			//�����I�u�W�F�N�g������΂��̈ʒu�ɏ�����
			pImpl->m_TargetPosition = PtrT->GetPosition();
		}
	}
	SeekSteering::~SeekSteering() {}

	//�A�N�Z�T

	const Vector3& SeekSteering::GetTargetPosition() const {
		return pImpl->m_TargetPosition;
	}
	void SeekSteering::SetTargetPosition(const Vector3& Vec) {
		pImpl->m_TargetPosition = Vec;
	}
	void SeekSteering::SetTargetPosition(float x, float y, float z) {
		pImpl->m_TargetPosition = Vector3(x, y, z);
	}
	//����
	void SeekSteering::OnUpdate() {
		auto RigidPtr = GetGameObject()->GetComponent<Rigidbody>();
		auto TransPtr = GetGameObject()->GetComponent<Transform>();
		if (RigidPtr && TransPtr) {
			Vector3 Force = RigidPtr->GetForce();
			Vector3 WorkForce;
			WorkForce = Steering::Seek(RigidPtr->GetVelocity(), pImpl->m_TargetPosition,
				TransPtr->GetPosition(), RigidPtr->GetMaxSpeed()) * GetWeight();
			Steering::AccumulateForce(Force, WorkForce, RigidPtr->GetMaxForce());
			RigidPtr->SetForce(Force);
		}
	}

	//--------------------------------------------------------------------------------------
	//	struct ArriveSteering::Impl;
	//	�p�r: �R���|�[�l���gImpl�N���X
	//--------------------------------------------------------------------------------------
	struct ArriveSteering::Impl {
		Vector3 m_TargetPosition;
		float m_Decl;
		Impl() :
			m_TargetPosition(0, 0, 0),
			m_Decl(3.0f)
		{}
		~Impl() {}
	};

	//--------------------------------------------------------------------------------------
	//	class ArriveSteering : public SteeringComponent;
	//	�p�r: Arrive����
	//--------------------------------------------------------------------------------------
	ArriveSteering::ArriveSteering(const shared_ptr<GameObject>& GameObjectPtr) :
		SteeringComponent(GameObjectPtr),
		pImpl(new Impl())
	{}
	ArriveSteering::~ArriveSteering() {}

	//�A�N�Z�T
	const Vector3& ArriveSteering::GetTargetPosition() const {
		return pImpl->m_TargetPosition;
	}
	void ArriveSteering::SetTargetPosition(const Vector3& Vec) {
		pImpl->m_TargetPosition = Vec;
	}
	void ArriveSteering::SetTargetPosition(float x, float y, float z) {
		pImpl->m_TargetPosition = Vector3(x, y, z);
	}

	float ArriveSteering::GetDecl() const { return pImpl->m_Decl; }
	void ArriveSteering::SetDecl(float f) { pImpl->m_Decl = f; }


	//����
	void ArriveSteering::OnUpdate() {
		auto RigidPtr = GetGameObject()->GetComponent<Rigidbody>();
		auto TransPtr = GetGameObject()->GetComponent<Transform>();
		if (RigidPtr && TransPtr) {
			Vector3 Force = RigidPtr->GetForce();
			Vector3 WorkForce;
			WorkForce = Steering::Arrive(RigidPtr->GetVelocity(), pImpl->m_TargetPosition,
				TransPtr->GetPosition(), RigidPtr->GetMaxSpeed(), pImpl->m_Decl) *  GetWeight();
			Steering::AccumulateForce(Force, WorkForce, RigidPtr->GetMaxForce());
			RigidPtr->SetForce(Force);
		}
	}


	//--------------------------------------------------------------------------------------
	//	struct PursuitSteering::Impl;
	//	�p�r: �R���|�[�l���gImpl�N���X
	//--------------------------------------------------------------------------------------
	struct PursuitSteering::Impl {
		Vector3 m_TargetPosition;	//�ڕW�̈ʒu
		Quaternion m_TargetQuaternion;		//�ڕW�̌���
		Vector3 m_TargetVelocity;	//�ڕW�̑��x
		Impl() :
			m_TargetPosition(0, 0, 0),
			m_TargetQuaternion(),
			m_TargetVelocity(0, 0, 0)
		{}
		~Impl() {}
	};


	//--------------------------------------------------------------------------------------
	//	class PursuitSteering : public SteeringComponent;
	//	�p�r: Pursuit����
	//--------------------------------------------------------------------------------------
	PursuitSteering::PursuitSteering(const shared_ptr<GameObject>& GameObjectPtr) :
		SteeringComponent(GameObjectPtr),
		pImpl(new Impl())
	{}
	PursuitSteering::~PursuitSteering() {}

	//�A�N�Z�T
	const Vector3& PursuitSteering::GetTargetPosition() const {
		return pImpl->m_TargetPosition;
	}
	void PursuitSteering::SetTargetPosition(const Vector3& Vec) {
		pImpl->m_TargetPosition = Vec;
	}
	void PursuitSteering::SetTargetPosition(float x, float y, float z) {
		pImpl->m_TargetPosition = Vector3(x, y, z);
	}

	const Quaternion& PursuitSteering::GetTargetQuaternion() const {
		return pImpl->m_TargetQuaternion;
	}
	void PursuitSteering::SetTargetQuaternion(const Quaternion& Qt) {
		pImpl->m_TargetQuaternion = Qt;
	}
	void PursuitSteering::SetTargetRotation(const Vector3& rotation) {
		pImpl->m_TargetQuaternion.RotationRollPitchYawFromVector(rotation);
	}
	void PursuitSteering::SetTargetRotation(float x, float y, float z) {
		SetTargetRotation(Vector3(x, y, z));
	}
	const Vector3& PursuitSteering::GetTargetVelocity() const {
		return pImpl->m_TargetVelocity;
	}
	void PursuitSteering::SetTargetVelocity(const Vector3& velocity) {
		pImpl->m_TargetVelocity = velocity;
	}
	void PursuitSteering::SetTargetVelocity(float x, float y, float z) {
		SetTargetVelocity(Vector3(x, y, z));
	}

	//����
	void PursuitSteering::OnUpdate() {
		auto RigidPtr = GetGameObject()->GetComponent<Rigidbody>();
		auto TransPtr = GetGameObject()->GetComponent<Transform>();
		if (RigidPtr && TransPtr) {
			Vector3 Force = RigidPtr->GetForce();
			Vector3 WorkForce;
			WorkForce = Steering::Pursuit(RigidPtr->GetVelocity(), TransPtr->GetPosition(), TransPtr->GetRotation(), RigidPtr->GetMaxSpeed(),
				pImpl->m_TargetVelocity, pImpl->m_TargetPosition, pImpl->m_TargetQuaternion.GetRotation()) *  GetWeight();
			Steering::AccumulateForce(Force, WorkForce, RigidPtr->GetMaxForce());
			RigidPtr->SetForce(Force);
		}
	}

	//--------------------------------------------------------------------------------------
	//	struct WanderSteering::Impl;
	//	�p�r: �R���|�[�l���gImpl�N���X
	//--------------------------------------------------------------------------------------
	struct WanderSteering::Impl {
		Vector3 m_WanderTarget;	//�p�j�ڕW�̉�]�W���i���ǂɂ���ď�����������j
		float m_WanderRadius;	//�p�j���a
		float m_WanderDistance;	//�p�j�~�܂ł̋���
		float m_WanderJitter;	//�����_���ψق̍ő�l
		Impl() :
			m_WanderTarget(0, 0, 0),
			m_WanderRadius(1.5f),
			m_WanderDistance(1.0f),
			m_WanderJitter(0.5f)
		{}
		~Impl() {}
	};

	//--------------------------------------------------------------------------------------
	//	class WanderSteering : public SteeringComponent;
	//	�p�r: Wander����
	//--------------------------------------------------------------------------------------
	WanderSteering::WanderSteering(const shared_ptr<GameObject>& GameObjectPtr) :
		SteeringComponent(GameObjectPtr),
		pImpl(new Impl())
	{}
	WanderSteering::~WanderSteering() {}
	//�A�N�Z�T
	const Vector3& WanderSteering::GetWanderTarget() const {
		return pImpl->m_WanderTarget;
	}
	void WanderSteering::SetWanderTarget(const Vector3& target) {
		pImpl->m_WanderTarget = target;
	}
	float WanderSteering::GetWanderRadius() const {
		return pImpl->m_WanderRadius;
	}
	void WanderSteering::SetWanderRadius(float f) {
		pImpl->m_WanderRadius = f;
	}
	float WanderSteering::GetWanderDistance() const {
		return pImpl->m_WanderDistance;
	}
	void WanderSteering::SetWanderDistance(float f) {
		pImpl->m_WanderDistance = f;
	}
	float WanderSteering::GetWanderJitter() const {
		return pImpl->m_WanderJitter;
	}
	void WanderSteering::SetWanderJitter(float f) {
		pImpl->m_WanderJitter = f;
	}

	void WanderSteering::OnUpdate() {
		auto RigidPtr = GetGameObject()->GetComponent<Rigidbody>();
		auto TransPtr = GetGameObject()->GetComponent<Transform>();
		if (RigidPtr && TransPtr) {
			Vector3 Force = RigidPtr->GetForce();
			Vector3 WorkForce;
			WorkForce = Steering::Wander(TransPtr->GetWorldMatrix(),
				pImpl->m_WanderRadius, pImpl->m_WanderDistance, pImpl->m_WanderJitter, pImpl->m_WanderTarget) * GetWeight();
			Steering::AccumulateForce(Force, WorkForce, RigidPtr->GetMaxForce());
			RigidPtr->SetForce(Force);
		}
	}

	//--------------------------------------------------------------------------------------
	//	struct WallAvoidanceSteering::Impl;
	//	�p�r: �R���|�[�l���gImpl�N���X
	//--------------------------------------------------------------------------------------
	struct WallAvoidanceSteering::Impl {
		vector<PLANE> m_PlaneVec;//������ׂ��ʂ̔z��
		bool m_WallArrived;	//�ǂƏՓ˂�����
		Impl() :
			m_WallArrived(false)
		{}
		~Impl() {}
	};

	//--------------------------------------------------------------------------------------
	//	class WallAvoidanceSteering : public SteeringComponent;
	//	�p�r: WallAvoidance����(�ǉ��)
	//--------------------------------------------------------------------------------------
	WallAvoidanceSteering::WallAvoidanceSteering(const shared_ptr<GameObject>& GameObjectPtr) :
		SteeringComponent(GameObjectPtr),
		pImpl(new Impl())
	{}
	WallAvoidanceSteering::~WallAvoidanceSteering() {}

	//�A�N�Z�T
	vector<PLANE>& WallAvoidanceSteering::GetPlaneVec() const {
		return pImpl->m_PlaneVec;
	}
	void WallAvoidanceSteering::SetPlaneVec(const vector<PLANE>& planevec) {
		//�K���N���A����
		pImpl->m_PlaneVec.clear();
		for (auto v : planevec) {
			pImpl->m_PlaneVec.push_back(v);
		}
	}
	void WallAvoidanceSteering::SetPlaneVec(const vector<Plane>& planevec) {
		//�K���N���A����
		pImpl->m_PlaneVec.clear();
		for (auto v : planevec) {
			PLANE p(v);
			pImpl->m_PlaneVec.push_back(p);
		}
	}


	//�ǂƏՓ˂��Ă��邩
	bool WallAvoidanceSteering::IsWallArribed() const {
		return pImpl->m_WallArrived;
	}


	//����
	void WallAvoidanceSteering::OnUpdate() {
		auto RigidPtr = GetGameObject()->GetComponent<Rigidbody>();
		auto TransPtr = GetGameObject()->GetComponent<Transform>();
		pImpl->m_WallArrived = false;
		if (RigidPtr && TransPtr) {
			Vector3 Force = RigidPtr->GetForce();
			Vector3 WorkForce(0, 0, 0);
			WorkForce = Steering::WallAvoidance(TransPtr->GetWorldMatrix(),
				RigidPtr->GetVelocity(), RigidPtr->GetMaxSpeed(), pImpl->m_PlaneVec) * GetWeight();
			Steering::AccumulateForce(Force, WorkForce, RigidPtr->GetMaxForce());
			RigidPtr->SetForce(Force);
			if (WorkForce.Length() > 0.0f) {
				//�ǂɏՓ˂��Ă���
				pImpl->m_WallArrived = true;
			}
		}
	}

	//--------------------------------------------------------------------------------------
	//	struct ObstacleAvoidanceSteering::Impl;
	//	�p�r: �R���|�[�l���gImpl�N���X
	//--------------------------------------------------------------------------------------
	struct ObstacleAvoidanceSteering::Impl {
		vector<SPHERE> m_ObstacleSphereVec;		//������ׂ���Q����SPHERE�z��
		float m_RoadWidth;
		float m_RoadHeight;
		Impl() :
			m_RoadWidth(0.5f),
			m_RoadHeight(0.5f)
		{}
		~Impl() {}
	};


	//--------------------------------------------------------------------------------------
	//	class ObstacleAvoidanceSteering : public SteeringComponent;
	//	�p�r: ObstacleAvoidance����(��Q�����)
	//--------------------------------------------------------------------------------------
	ObstacleAvoidanceSteering::ObstacleAvoidanceSteering(const shared_ptr<GameObject>& GameObjectPtr) :
		SteeringComponent(GameObjectPtr),
		pImpl(new Impl())
	{}
	ObstacleAvoidanceSteering::~ObstacleAvoidanceSteering() {}
	//�A�N�Z�T
	//��Q���̔z��
	const vector<SPHERE>& ObstacleAvoidanceSteering::GetObstacleSphereVec() const {
		return pImpl->m_ObstacleSphereVec;
	}
	void ObstacleAvoidanceSteering::SetObstacleSphereVec(const vector<SPHERE>& spherevec) {
		pImpl->m_ObstacleSphereVec.clear();
		for (auto sp : spherevec) {
			pImpl->m_ObstacleSphereVec.push_back(sp);
		}
	}

	//���̍���
	float ObstacleAvoidanceSteering::GetRoadWidth() const {
		return pImpl->m_RoadWidth;
	}
	void ObstacleAvoidanceSteering::SetRoadWidth(float f) {
		pImpl->m_RoadWidth = f;
	}
	//����
	float ObstacleAvoidanceSteering::GetRoadHeight() const {
		return pImpl->m_RoadHeight;
	}
	void ObstacleAvoidanceSteering::SetRoadHeight(float f) {
		pImpl->m_RoadHeight = f;
	}


	void ObstacleAvoidanceSteering::OnUpdate() {
		auto RigidPtr = GetGameObject()->GetComponent<Rigidbody>();
		auto TransPtr = GetGameObject()->GetComponent<Transform>();
		if (RigidPtr && TransPtr) {
			Vector3 Force = RigidPtr->GetForce();
			Vector3 WorkForce(0, 0, 0);
			WorkForce = Steering::ObstacleAvoidance(TransPtr->GetWorldMatrix(),
				RigidPtr->GetVelocity(), RigidPtr->GetMaxSpeed(), pImpl->m_RoadWidth, pImpl->m_RoadHeight,
				pImpl->m_ObstacleSphereVec) * GetWeight();
			Steering::AccumulateForce(Force, WorkForce, RigidPtr->GetMaxForce());
			RigidPtr->SetForce(Force);
		}
	}

	//--------------------------------------------------------------------------------------
	//	struct FollowPathSteering::Impl;
	//	�p�r: �R���|�[�l���gImpl�N���X
	//--------------------------------------------------------------------------------------
	struct FollowPathSteering::Impl {
		Path m_Path;	//�o�H������킷�p�X
		float m_Decl;	//�����l
		float m_WaypointSpan;	//�o�H�̒��S����̋���
		Impl() :
			m_Decl(3.0f),
			m_WaypointSpan(2.0f)
		{}
		~Impl() {}
	};

	//--------------------------------------------------------------------------------------
	//	class FollowPathSteering : public SteeringComponent;
	//	�p�r: FollowPath����(�o�H�Ǐ])
	//--------------------------------------------------------------------------------------
	FollowPathSteering::FollowPathSteering(const shared_ptr<GameObject>& GameObjectPtr) :
		SteeringComponent(GameObjectPtr),
		pImpl(new Impl())
	{}
	FollowPathSteering::~FollowPathSteering() {}

	//�A�N�Z�T
	void FollowPathSteering::SetPathList(const list<Vector3>& pathlist) {
		pImpl->m_Path.SetList(pathlist);
	}

	float FollowPathSteering::GetDecl() const {
		return pImpl->m_Decl;
	}
	void FollowPathSteering::SetDecl(float f) {
		pImpl->m_Decl = f;
	}

	float FollowPathSteering::GetWaypointSpan() const {
		return pImpl->m_WaypointSpan;
	}
	void FollowPathSteering::SetWaypointSpan(float f) {
		pImpl->m_WaypointSpan = f;
	}

	bool FollowPathSteering::GetLooped() const {
		return pImpl->m_Path.GetLooped();
	}
	bool FollowPathSteering::IsLooped() const {
		return pImpl->m_Path.GetLooped();
	}
	void FollowPathSteering::SetLooped(bool b) {
		pImpl->m_Path.SetLooped(b);
	}

	bool FollowPathSteering::IsFinished() const {
		return pImpl->m_Path.IsFinished();
	}

	//����
	void FollowPathSteering::OnUpdate() {
		auto RigidPtr = GetGameObject()->GetComponent<Rigidbody>();
		auto TransPtr = GetGameObject()->GetComponent<Transform>();
		if (RigidPtr && TransPtr) {
			Vector3 Force = RigidPtr->GetForce();
			Vector3 WorkForce(0, 0, 0);
			WorkForce = Steering::FollowPath(pImpl->m_Path,
				pImpl->m_WaypointSpan,
				TransPtr->GetPosition(),
				RigidPtr->GetVelocity(),
				RigidPtr->GetMaxSpeed(),
				pImpl->m_Decl)
				* GetWeight();
			Steering::AccumulateForce(Force, WorkForce, RigidPtr->GetMaxForce());
			RigidPtr->SetForce(Force);
		}
	}

	//--------------------------------------------------------------------------------------
	//	struct AlignmentSteering::Impl;
	//	�p�r: �R���|�[�l���gImpl�N���X
	//--------------------------------------------------------------------------------------
	struct AlignmentSteering::Impl {
		weak_ptr<GameObjectGroup> m_Group;
		Impl(const shared_ptr<GameObjectGroup>& Group) :
			m_Group(Group)
		{}
		~Impl() {}
	};

	//--------------------------------------------------------------------------------------
	//	class AlignmentSteering : public SteeringComponent;
	//	�p�r: Alignment����(����)
	//--------------------------------------------------------------------------------------
	AlignmentSteering::AlignmentSteering(const shared_ptr<GameObject>& GameObjectPtr,
		const shared_ptr<GameObjectGroup>& Group) :
		SteeringComponent(GameObjectPtr),
		pImpl(new Impl(Group))
	{}
	AlignmentSteering::~AlignmentSteering() {}

	//�A�N�Z�T
	shared_ptr<GameObjectGroup> AlignmentSteering::GetGameObjectGroup() const {
		if (pImpl->m_Group.expired()) {
			throw BaseException(
				L"�O���[�v�͖����ł�",
				L"�O���[�v�̑��݂��m�F���ĉ�����",
				L"AlignmentSteering::GetGameObjectGroup()"
			);
		}
		return pImpl->m_Group.lock();
	}
	void AlignmentSteering::SetGameObjectGroup(const shared_ptr<GameObjectGroup>& Group) {
		pImpl->m_Group = Group;
	}
	//����
	void AlignmentSteering::OnUpdate() {
		auto RigidPtr = GetGameObject()->GetComponent<Rigidbody>();
		auto TransPtr = GetGameObject()->GetComponent<Transform>();
		if (TransPtr && RigidPtr) {
			Vector3 Force = RigidPtr->GetForce();
			Vector3 WorkForce;
			WorkForce = Steering::Alignment(GetGameObjectGroup(), GetGameObject()) * GetWeight();
			Steering::AccumulateForce(Force, WorkForce, RigidPtr->GetMaxForce());
			RigidPtr->SetForce(Force);
		}
	}


	//--------------------------------------------------------------------------------------
	//	struct CohesionSteering::Impl;
	//	�p�r: �R���|�[�l���gImpl�N���X
	//--------------------------------------------------------------------------------------
	struct CohesionSteering::Impl {
		weak_ptr<GameObjectGroup> m_Group;
		Impl(const shared_ptr<GameObjectGroup>& Group) :
			m_Group(Group)
		{}
		~Impl() {}
	};

	//--------------------------------------------------------------------------------------
	//	class CohesionSteering : public SteeringComponent;
	//	�p�r: Cohesion����(����)
	//--------------------------------------------------------------------------------------
	CohesionSteering::CohesionSteering(const shared_ptr<GameObject>& GameObjectPtr,
		const shared_ptr<GameObjectGroup>& Group) :
		SteeringComponent(GameObjectPtr),
		pImpl(new Impl(Group))
	{}
	CohesionSteering::~CohesionSteering() {}

	//�A�N�Z�T
	shared_ptr<GameObjectGroup> CohesionSteering::GetGameObjectGroup() const {
		if (pImpl->m_Group.expired()) {
			throw BaseException(
				L"�O���[�v�͖����ł�",
				L"�O���[�v�̑��݂��m�F���ĉ�����",
				L"CohesionSteering::GetGameObjectGroup()"
			);
		}
		return pImpl->m_Group.lock();
	}
	void CohesionSteering::SetGameObjectGroup(const shared_ptr<GameObjectGroup>& Group) {
		pImpl->m_Group = Group;
	}

	//����
	void CohesionSteering::OnUpdate() {
		auto RigidPtr = GetGameObject()->GetComponent<Rigidbody>();
		auto TransPtr = GetGameObject()->GetComponent<Transform>();
		if (TransPtr && RigidPtr) {
			Vector3 Force = RigidPtr->GetForce();
			Vector3 WorkForce;
			WorkForce = Steering::Cohesion(GetGameObjectGroup(), GetGameObject(),
				RigidPtr->GetVelocity(), RigidPtr->GetMaxSpeed()) * GetWeight();
			Steering::AccumulateForce(Force, WorkForce, RigidPtr->GetMaxForce());
			RigidPtr->SetForce(Force);
		}
	}


	//--------------------------------------------------------------------------------------
	//	struct SeparationSteering::Impl;
	//	�p�r: �R���|�[�l���gImpl�N���X
	//--------------------------------------------------------------------------------------
	struct SeparationSteering::Impl {
		weak_ptr<GameObjectGroup> m_Group;
		Impl(const shared_ptr<GameObjectGroup>& Group) :
			m_Group(Group)
		{}
		~Impl() {}
	};

	//--------------------------------------------------------------------------------------
	//	class SeparationSteering : public SteeringComponent;
	//	�p�r: Separation����
	//--------------------------------------------------------------------------------------
	SeparationSteering::SeparationSteering(const shared_ptr<GameObject>& GameObjectPtr,
		const shared_ptr<GameObjectGroup>& Group) :
		SteeringComponent(GameObjectPtr),
		pImpl(new Impl(Group))
	{}
	SeparationSteering::~SeparationSteering() {}
	//�A�N�Z�T
	shared_ptr<GameObjectGroup> SeparationSteering::GetGameObjectGroup() const {
		if (pImpl->m_Group.expired()) {
			throw BaseException(
				L"�O���[�v�͖����ł�",
				L"�O���[�v�̑��݂��m�F���ĉ�����",
				L"SeparationSteering::GetGameObjectGroup()"
			);
		}
		return pImpl->m_Group.lock();
	}
	void SeparationSteering::SetGameObjectGroup(const shared_ptr<GameObjectGroup>& Group) {
		pImpl->m_Group = Group;
	}

	void SeparationSteering::OnUpdate() {
		auto RigidPtr = GetGameObject()->GetComponent<Rigidbody>();
		auto TransPtr = GetGameObject()->GetComponent<Transform>();
		if (TransPtr && RigidPtr) {
			Vector3 Force = RigidPtr->GetForce();
			Vector3 WorkForce;
			WorkForce = Steering::Separation(GetGameObjectGroup(), GetGameObject()) * GetWeight();
			Steering::AccumulateForce(Force, WorkForce, RigidPtr->GetMaxForce());
			RigidPtr->SetForce(Force);
		}
	}


	//--------------------------------------------------------------------------------------
	//	struct Rigidbody::Impl;
	//	�p�r: �R���|�[�l���gImpl�N���X
	//--------------------------------------------------------------------------------------
	struct Rigidbody::Impl {
		Vector3 m_Velocity;				//���x
		float m_MaxSpeed;				//�ō����x
		Vector3 m_MinVelocity;			//�Œᑬ�x�iXYZ���w��ł���j
		Vector3 m_AngularVelocity;		//��]���x

		float m_Mass;					//���ʁi�L���O�����j
		float m_Reflection;				//�����W��
		Vector3 m_Force;				//���݂̃t�H�[�X�i�X�e�A�����O�n�R���|�[�l���g�ŕύX�����j
		float m_Friction;				//���C�W���iForce�̋t�����ɓ����K��0����-1.0�̊ԁj
		float m_MaxForce;				//�ō��t�H�[�X
		Impl() :
			m_Velocity(0, 0, 0),
			m_MaxSpeed(10.0f),
			m_MinVelocity(0.01f, 0.01f, 0.01f),
			m_AngularVelocity(0, 0, 0),
			m_Mass(1.0f),
			m_Reflection(1.0f),
			m_Force(0, 0, 0),
			m_Friction(0),
			m_MaxForce(30.0f)
		{}
		~Impl() {}

	};

	//--------------------------------------------------------------------------------------
	//	class Rigidbody : public Component ;
	//	�p�r: �����ʒu�R���g���[��
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	Rigidbody::Rigidbody(const shared_ptr<GameObject>& GameObjectPtr) :
		Component(GameObjectPtr),
		pImpl(new Impl())
	{}
	Rigidbody::~Rigidbody() {}

	const Vector3& Rigidbody::GetVelocity() const { return pImpl->m_Velocity; }
	void Rigidbody::SetVelocity(const Vector3& Velocity) {
		pImpl->m_Velocity = Velocity;
		pImpl->m_Velocity.ClampLength(0, pImpl->m_MaxSpeed);
		if (pImpl->m_Velocity.Length() < pImpl->m_MinVelocity.Length()) {
			pImpl->m_Velocity.Zero();
		}
	}
	void Rigidbody::SetVelocity(float x, float y, float z) {
		SetVelocity(Vector3(x, y, z));
	}

	float Rigidbody::GetMaxSpeed() const { return pImpl->m_MaxSpeed; }
	void Rigidbody::SetMaxSpeed(float f) { pImpl->m_MaxSpeed = f; }

	const Vector3& Rigidbody::GetMinVelocity() const {
		return pImpl->m_MinVelocity;
	}
	void Rigidbody::SetMinVelocity(const Vector3& Velocity) {
		pImpl->m_MinVelocity = Velocity;
	}
	void Rigidbody::SetMinVelocity(float x, float y, float z) {
		SetMinVelocity(Vector3(x, y, z));
	}


	const Vector3& Rigidbody::GetAngularVelocity() const { return pImpl->m_AngularVelocity; }
	void Rigidbody::SetAngularVelocity(const Vector3& AngularVelocity) { pImpl->m_AngularVelocity = AngularVelocity; }
	void Rigidbody::SetAngularVelocity(float x, float y, float z) { pImpl->m_AngularVelocity = Vector3(x, y, z); }


	float Rigidbody::GetMass() const { return pImpl->m_Mass; }
	void Rigidbody::SetMass(float f) { pImpl->m_Mass = f; }

	float Rigidbody::GetReflection() const {
		return pImpl->m_Reflection;
	}
	void Rigidbody::SetReflection(float f) {
		pImpl->m_Reflection = f;
	}

	const Vector3& Rigidbody::GetForce() const { return pImpl->m_Force; }
	void Rigidbody::SetForce(const Vector3& Force) { pImpl->m_Force = Force; }
	void Rigidbody::SetForce(float x, float y, float z) { pImpl->m_Force = Vector3(x, y, z); }

	float Rigidbody::GetFriction() const {
		return pImpl->m_Friction;
	}
	void Rigidbody::SetFriction(float f) {
		if (f >= 0) {
			pImpl->m_Friction = 0.0f;
		}
		else if (f <= -1.0f) {
			pImpl->m_Friction = -1.0f;
		}
		else {
			pImpl->m_Friction = f;
		}
	}


	float Rigidbody::GetMaxForce() const { return pImpl->m_MaxForce; }
	void Rigidbody::SetMaxForce(float f) { pImpl->m_MaxForce = f; }


	void Rigidbody::IsHitChangeVelocity(const shared_ptr<CollisionSphere>& SrcColl, const shared_ptr<CollisionSphere>& DestColl) {
		switch (SrcColl->GetIsHitAction()) {
		case IsHitAction::Stop:
			SetVelocity(0, 0, 0);
			break;
		case IsHitAction::AutoOnObjectRepel:
		{
			SPHERE sp = SrcColl->GetSphere();
			SPHERE destsp = DestColl->GetSphere();
			Vector3 Normal = destsp.m_Center - sp.m_Center;
			Normal.Normalize();
			auto Ref = Vector3EX::Reflect(GetVelocity(), Normal);
			//�����W��
			Ref *= GetReflection();
			SetVelocity(Ref);
		}
		break;
		}
	}
	void Rigidbody::IsHitChangeVelocity(const shared_ptr<CollisionSphere>& SrcColl, const shared_ptr<CollisionObb>& DestColl) {
		switch (SrcColl->GetIsHitAction()) {
		case IsHitAction::Stop:
			SetVelocity(0,0,0);
			break;
		case IsHitAction::AutoOnObjectRepel:
			{
				SPHERE sp = SrcColl->GetSphere();
				OBB obb = DestColl->GetObb();
				Vector3 Ret;
				HitTest::SPHERE_OBB(sp, obb, Ret);
				Vector3 Normal = Ret - sp.m_Center;
				Normal.Normalize();
				auto Ref = Vector3EX::Reflect(GetVelocity(), Normal);
				//�����W��
				Ref *= GetReflection();
				SetVelocity(Ref);
			}
			break;
		}

	}


	void Rigidbody::IsHitChangeVelocity(const shared_ptr<CollisionObb>& SrcColl, const shared_ptr<CollisionSphere>& DestColl) {
		switch (SrcColl->GetIsHitAction()) {
			case IsHitAction::Stop:
				SetVelocity(0, 0, 0);
				break;
			case IsHitAction::AutoOnObjectRepel:
			{
				OBB obb = SrcColl->GetObb();
				SPHERE sp = DestColl->GetSphere();
				Vector3 Ret;
				HitTest::SPHERE_OBB(sp, obb, Ret);
				Vector3 Normal = sp.m_Center - Ret;
				Normal.Normalize();
				auto Ref = Vector3EX::Reflect(GetVelocity(), Normal);
				//�����W��
				Ref *= GetReflection();
				SetVelocity(Ref);
			}
			break;
		}
	}

	void Rigidbody::IsHitChangeVelocity(const shared_ptr<CollisionObb>& SrcColl, const shared_ptr<CollisionObb>& DestColl) {
		switch (SrcColl->GetIsHitAction()) {
		case IsHitAction::Stop:
			SetVelocity(0, 0, 0);
			break;
		case IsHitAction::AutoOnObjectRepel:
		{
			OBB SrcObb = SrcColl->GetObb();
			OBB DestObb = DestColl->GetObb();
			Vector3 Ret;
			//Src��OBB��Dest�̍ŋߐړ_�𓾂�
			HitTest::ClosestPtPointOBB(SrcObb.m_Center, DestObb, Ret);
			Vector3 Normal = SrcObb.m_Center - Ret;
			Normal.Normalize();
			auto Ref = Vector3EX::Reflect(GetVelocity(), Normal);
			//�����W��
			Ref *= GetReflection();
			SetVelocity(Ref);
		}
		break;
		}

	}



	void Rigidbody::UpdateFromTime(float CalcTime) {
		auto PtrTransform = GetGameObject()->GetComponent<Transform>();
		Vector3 Pos = PtrTransform->GetPosition();
		Quaternion Qt = PtrTransform->GetQuaternion();
		//�t�H�[�X���ύX����Ă�����
		if (pImpl->m_Force.Length() > 0) {
			//�t�H�[�X��0�ȏ�Ȃ�
			//���ʂ��v�Z���ĉ��������߂�
			Vector3 Accel = pImpl->m_Force / pImpl->m_Mass;
			pImpl->m_Velocity += Accel * CalcTime;
		}
		if (pImpl->m_Velocity.Length() >= pImpl->m_MaxSpeed) {
			pImpl->m_Velocity.ClampLength(0, pImpl->m_MaxSpeed);
		}
		//�����l�����߂�
		auto  Friction = pImpl->m_Mass * pImpl->m_Friction;
		if (Friction <= -1.0f) {
			Friction = -1.0f;
		}
		else if (Friction >= 0.0f) {
			Friction = 0.0f;
		}
		Vector3 VFriction = pImpl->m_Velocity * Friction;
		pImpl->m_Velocity += VFriction;
		if (abs(pImpl->m_Velocity.x) < pImpl->m_MinVelocity.x) {
			pImpl->m_Velocity.x = 0;
		}
		if (abs(pImpl->m_Velocity.y) < pImpl->m_MinVelocity.y) {
			pImpl->m_Velocity.y = 0;
		}
		if (abs(pImpl->m_Velocity.z) < pImpl->m_MinVelocity.z) {
			pImpl->m_Velocity.z = 0;
		}
		Quaternion QtSpan;
		QtSpan.RotationRollPitchYawFromVector(pImpl->m_AngularVelocity * CalcTime);
		Qt *= QtSpan;
		Qt.Normalize();
		Pos += pImpl->m_Velocity * CalcTime;
		PtrTransform->SetQuaternion(Qt);
		PtrTransform->SetPosition(Pos);
	}





	void Rigidbody::OnUpdate() {
		//�O��̃^�[������̎���
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		UpdateFromTime(ElapsedTime);
	}

}
//end basecross
