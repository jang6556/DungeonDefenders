#pragma once
#include "Bullet.h"

_BEGIN(Client)
class CCrossBowArrow :
	public CBullet
{
private:
		

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CCrossBowArrow(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CCrossBowArrow(const CCrossBowArrow & rhs);
	virtual ~CCrossBowArrow() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CCrossBowArrow* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
