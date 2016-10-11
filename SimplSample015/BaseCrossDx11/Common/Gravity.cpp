/*!
@file Gravity.cpp
@brief �d�̓R���|�[�l���g����
*/
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	struct Gravity::Impl;
	//	�p�r: �R���|�[�l���gImpl�N���X
	//--------------------------------------------------------------------------------------
	struct Gravity::Impl {
		Vector3 m_DefaultGravity;		//���R���������x
		Vector3 m_Gravity;				//���݂̏d�͉����x
		Vector3 m_GravityVelocity;		//�d�͉����x�ɂ�錻�݂̑��x
		float m_BaseY;	//�ŉ������n�_

	public:
		Impl() :
			m_DefaultGravity(0, -9.8f, 0),
			m_Gravity(0, 0, 0),
			m_GravityVelocity(0, 0, 0),
			m_BaseY(0)
		{}
		~Impl() {}
	};

	//--------------------------------------------------------------------------------------
	//	class Gravity : public Component ;
	//	�p�r: �d��
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	Gravity::Gravity(const shared_ptr<GameObject>& GameObjectPtr) :
		Component(GameObjectPtr), pImpl(new Impl())
	{}
	Gravity::~Gravity() {}

	//�A�N�Z�T

	const Vector3& Gravity::GetDefaultGravity() const {
		return pImpl->m_DefaultGravity;
	}
	void Gravity::SetDefaultGravity(const Vector3& gravity) {
		pImpl->m_DefaultGravity = gravity;
	}
	void Gravity::SetDefaultGravity(float x, float y, float z) {
		pImpl->m_DefaultGravity = Vector3(x, y, z);

	}


	const Vector3& Gravity::GetGravity() const {
		return pImpl->m_Gravity;
	}
	void Gravity::SetGravity(const Vector3& gravity) {
		pImpl->m_Gravity = gravity;
	}
	void Gravity::SetGravity(float x, float y, float z) {
		pImpl->m_Gravity = Vector3(x, y, z);
	}
	void Gravity::SetGravityZero() {
		pImpl->m_Gravity.Zero();
	}

	void Gravity::SetGravityDefault() {
		pImpl->m_Gravity = pImpl->m_DefaultGravity;
	}



	const Vector3& Gravity::GetGravityVelocity() const {
		return pImpl->m_GravityVelocity;
	}

	void Gravity::SetGravityVelocity(const Vector3& GravityVelocity) {
		pImpl->m_GravityVelocity = GravityVelocity;
	}
	void Gravity::SetGravityVelocity(float x, float y, float z) {
		pImpl->m_GravityVelocity = Vector3(x, y, z);
	}

	bool Gravity::IsGravityVelocityZero() {
		return (pImpl->m_GravityVelocity == Vector3(0, 0, 0));
	}
	void Gravity::SetGravityVelocityZero() {
		pImpl->m_GravityVelocity.Zero();
	}
	float Gravity::GetBaseY() const {
		return pImpl->m_BaseY;
	}
	void Gravity::SetBaseY(float y) {
		pImpl->m_BaseY = y;
	}

	void Gravity::StartJump(const Vector3& StartVec, float EscapeSpan) {
		auto PtrTransform = GetGameObject()->GetComponent<Transform>();
		Vector3 Pos = PtrTransform->GetPosition();
		SetGravityVelocity(StartVec);
		SetGravityDefault();
		//�W�����v���Đe�I�u�W�F�N�g�{�����[������E�o�ł��Ȃ��Ƃ��Ή�
		Vector3 EscapeVec = StartVec;
		EscapeVec *= EscapeSpan;
		Pos += EscapeVec;
		PtrTransform->SetPosition(Pos);
	}
	void Gravity::StartJump(float x, float y, float z, float EscapeSpan) {
		StartJump(Vector3(x, y, z), EscapeSpan);
	}

	void Gravity::UpdateFromTime(float CalcTime) {
		auto PtrTransform = GetGameObject()->GetComponent<Transform>();
		Vector3 Pos = PtrTransform->GetPosition();
		//���R���������x���v�Z
		pImpl->m_GravityVelocity += pImpl->m_Gravity * CalcTime;
		Pos += pImpl->m_GravityVelocity * CalcTime;

		if (pImpl->m_Gravity.y <= 0) {
			if (Pos.y <= pImpl->m_BaseY) {
				Pos.y = pImpl->m_BaseY;
				SetGravityVelocityZero();
				SetGravityZero();
			}
		}
		else {
			if (Pos.y >= pImpl->m_BaseY) {
				Pos.y = pImpl->m_BaseY;
				SetGravityVelocityZero();
				SetGravityZero();
			}
		}
		//�ʒu��ݒ�
		PtrTransform->SetPosition(Pos);
	}



	//����
	void Gravity::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		UpdateFromTime(ElapsedTime);
	}



}
//end basecross

