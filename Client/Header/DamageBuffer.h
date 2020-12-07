#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CDamageBuffer :
	public CGameObject
{
public:

	enum NUM_TYPE {TYPE_EVEN,TYPE_ODD,TYPE_END};
	enum NUM_POS { POS_ONE, POS_TEN, POS_HUN, POS_THOU, POS_MILL, POS_END};
	
private:
	CTransform*				m_pTransform = nullptr;
	CTexture*				m_pTexture = nullptr;
	CShader*				m_pShader = nullptr;
	CRectUI*				m_pBuffer = nullptr;

	float					m_fTimeDelta = 0.f;
	D3DXVECTOR4				m_vPosition;
	NUM_TYPE				m_eType;
	NUM_POS					m_ePos;
	float					m_fScale = 0.f;

	void					ComputePosition();
	void					SetPosition(D3DXVECTOR3* pOut);

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();

	explicit CDamageBuffer(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CDamageBuffer(const CDamageBuffer & rhs);
	virtual ~CDamageBuffer() = default;

public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;	

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	void Set_Type_Pos(NUM_TYPE eType, NUM_POS ePos) { m_eType = eType; m_ePos = ePos; }

	static CDamageBuffer* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
