/*!
@file ProjectShader.cpp
@brief �v���W�F�N�g�Ŏg�p����V�F�[�_�[����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	IMPLEMENT_DX12SHADER(VSPNTStatic, App::GetApp()->m_wstrRelativeShadersPath + L"VSPNTStatic.cso")
	IMPLEMENT_DX12SHADER(PSPNTStatic, App::GetApp()->m_wstrRelativeShadersPath + L"PSPNTStatic.cso")

}
//end basecross


