#pragma once
#include "GameObject.h"
#include "../Header/Player.h"

_BEGIN(Client)
class CSkillIcon :
	public CGameObject
{
protected:
	CTransform*				m_pTransform = nullptr;
	CTexture*				m_Texture = nullptr;
	CShader*				m_pShader = nullptr;	
	CRectUI*				m_pBuffer = nullptr;

	const SKILLINFO*		m_pSkillInfo = nullptr;

	float					m_fTimeDelta = 0.f;
	_uint					m_iIconNum = 0.f;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();

	explicit CSkillIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CSkillIcon(const CSkillIcon & rhs);
	virtual ~CSkillIcon() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;
};
_END

