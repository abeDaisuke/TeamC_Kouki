/*!
@file Components.cpp
@brief �R���|�[�l���g����
*/
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	struct Component::Impl;
	//	�p�r: �R���|�[�l���gImpl�N���X
	//--------------------------------------------------------------------------------------
	struct Component::Impl {
		weak_ptr<GameObject> m_GameObject;
		bool m_UpdateActive{ true };	//update���邩�ǂ���
		bool m_DrawActive{ true };		//Draw���邩�ǂ���
		explicit Impl(const shared_ptr<GameObject>& GameObjectPtr) :
			m_GameObject(GameObjectPtr)
		{}
		~Impl() {}
	};

	//--------------------------------------------------------------------------------------
	//	class Component :public Object;
	//	�p�r: �R���|�[�l���g���N���X
	//--------------------------------------------------------------------------------------
	Component::Component(const shared_ptr<GameObject>& GameObjectPtr) :
		ObjectInterface(),
		ShapeInterface(),
		pImpl(new Impl(GameObjectPtr))
	{}
	Component::~Component() {}
	//�A�N�Z�T
	shared_ptr<GameObject> Component::GetGameObject() const {
		auto shptr = pImpl->m_GameObject.lock();
		if (!shptr) {
			throw BaseException(
				L"GameObject�͗L���ł͂���܂���",
				L"if (!shptr)",
				L"Component::GetGameObject()"
			);
		}
		else {
			return shptr;
		}
	}

	void Component::AttachGameObject(const shared_ptr<GameObject>& GameObjectPtr) {
		pImpl->m_GameObject = GameObjectPtr;
	}
	shared_ptr<Stage> Component::GetStage() const {
		return GetGameObject()->GetStage();
	}


	bool Component::IsUpdateActive() const {
		return pImpl->m_UpdateActive;
	}
	bool Component::GetUpdateActive() const {
		return pImpl->m_UpdateActive;
	}
	void Component::SetUpdateActive(bool b) {
		pImpl->m_UpdateActive = b;
	}

	bool Component::IsDrawActive() const {
		return pImpl->m_DrawActive;
	}
	bool Component::GetDrawActive() const {
		return pImpl->m_DrawActive;
	}
	void Component::SetDrawActive(bool b) {
		pImpl->m_DrawActive = b;
	}


	//--------------------------------------------------------------------------------------
	//	struct Transform::Impl;
	//	�p�r: �R���|�[�l���gImpl�N���X
	//--------------------------------------------------------------------------------------
	struct Transform::Impl {
		bool m_Init{ false };	//�������ς݂��ǂ����i1��ڂ�Update�ŁABefore�ɒl������j
		//1�O�̕ϐ�
		Vector3 m_BeforeScale;
		Vector3 m_BeforePivot;
		Quaternion m_BeforeQuaternion;
		Vector3 m_BeforePosition;
		//���݂̕ϐ�
		Vector3 m_Scale;
		Vector3 m_Pivot;
		Quaternion m_Quaternion;
		Vector3 m_Position;
		Impl()
		{}
		~Impl() {}
	};


	//--------------------------------------------------------------------------------------
	//	class Transform : public Component ;
	//	�p�r: �ω�
	//--------------------------------------------------------------------------------------
	Transform::Transform(const shared_ptr<GameObject>& GameObjectPtr) :
		Component(GameObjectPtr), pImpl(new Impl())
	{}
	Transform::~Transform() {}

	//�A�N�Z�T
	//BeforeGetter
	Vector3 Transform::GetBeforeScale() const {
		return pImpl->m_BeforeScale;
	}

	Vector3 Transform::GetBeforePivot() const{
		return pImpl->m_BeforePivot;
	}

	Quaternion Transform::GetBeforeQuaternion() const {
		return pImpl->m_BeforeQuaternion;
	}

	Vector3 Transform::GetBeforeRotation() const {
		return pImpl->m_BeforeQuaternion.GetRotation();
	}

	Vector3 Transform::GetBeforePosition() const {
		return pImpl->m_BeforePosition;
	}

	Matrix4X4 Transform::GetBeforeWorldMatrix() const{
		Matrix4X4 mat;
		mat.AffineTransformation(pImpl->m_BeforeScale,
			pImpl->m_BeforePivot, 
			pImpl->m_BeforeQuaternion, 
			pImpl->m_BeforePosition
		);
		return mat;
	}


	//Getter&Setter

	Vector3 Transform::GetScale() const {
		return pImpl->m_Scale;
	}

	void Transform::SetScale(const Vector3& Scale) {
		pImpl->m_Scale = Scale;
	}
	void Transform::SetScale(float x, float y, float z) {
		SetScale(Vector3(x, y, z));
	}

	Vector3 Transform::GetPivot() const {
		return pImpl->m_Pivot;
	}
	void Transform::SetPivot(const Vector3& Pivot) {
		pImpl->m_Pivot = Pivot;
	}
	void Transform::SetPivot(float x, float y, float z) {
		SetPivot(Vector3(x, y, z));
	}

	Quaternion Transform::GetQuaternion() const {
		return pImpl->m_Quaternion;
	}
	void Transform::SetQuaternion(const Quaternion& quaternion) {
		pImpl->m_Quaternion = quaternion;
		pImpl->m_Quaternion.Normalize();
	}
	Vector3 Transform::GetRotation() const {
		return pImpl->m_Quaternion.GetRotation();
	}

	void Transform::SetRotation(const Vector3& Rot) {
		Quaternion Qt;
		Qt.RotationRollPitchYawFromVector(Rot);
		SetQuaternion(Qt);
	}
	void Transform::SetRotation(float x, float y, float z) {
		SetRotation(Vector3(x, y, z));
	}

	Vector3 Transform::GetPosition() const {
		return pImpl->m_Position;
	}

	void Transform::SetPosition(const Vector3& Position) {
		pImpl->m_Position = Position;
	}
	void Transform::SetPosition(float x, float y, float z) {
		SetPosition(Vector3(x, y, z));
	}
	Matrix4X4 Transform::GetWorldMatrix() const{
		Matrix4X4 mat;
		mat.AffineTransformation(
			pImpl->m_Scale,
			pImpl->m_Pivot,
			pImpl->m_Quaternion,
			pImpl->m_Position
		);
		return mat;
	}

	Vector3 Transform::GetVelocity() const {
		//�O��̃^�[������̎���
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		Vector3 Velocity = pImpl->m_Position - pImpl->m_BeforePosition;
		Velocity /= ElapsedTime;
		return Velocity;
	}


	void Transform::SetToBefore() {
		pImpl->m_BeforeScale = pImpl->m_Scale;
		pImpl->m_BeforePivot = pImpl->m_Pivot;
		pImpl->m_BeforeQuaternion = pImpl->m_Quaternion;
		pImpl->m_BeforePosition = pImpl->m_Position;
	}

	//����
	void Transform::OnUpdate() {
		if (!pImpl->m_Init) {
			SetToBefore();
			pImpl->m_Init = true;
		}
	}



}
//end basecross
