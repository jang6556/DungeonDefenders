#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CSkillPanel :
	public CGameObject
{
private:	
	CTransform*				m_pTransform	= nullptr;
	CTexture*				m_Texture		= nullptr;
	CShader*				m_pShader		= nullptr;	
	CRectUI*				m_pBuffer		= nullptr;

	float					m_fTimeDelta	= 0.f;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CSkillPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CSkillPanel(const CSkillPanel & rhs);
	virtual ~CSkillPanel() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CSkillPanel* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);

};
_END