#pragma once
#include "../Header/Effect.h"

_BEGIN(Client)  
class CBloodEffect :
	public CEffect
{
private:	
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CBloodEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CBloodEffect(const CBloodEffect & rhs);
	virtual ~CBloodEffect() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CBloodEffect* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);

};
_END
