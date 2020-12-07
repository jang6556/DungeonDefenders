#pragma once
#include "Item.h"

_BEGIN(Client)
class CManaToken :
	public CItem
{
public:
	enum ROTATE_DIR {RIGHT,UP,LOOK,END};
	enum MANA { MANA_BLUE = 1, MANA_RED = 5, MANA_GREEN = 10, MANA_PURPLE = 50, MANA_SKY = 500, MANA_YELLOW = 2000, MANA_END };
private:
	CTexture*		m_pTexture = nullptr;
	D3DXVECTOR3		m_vSpeed;
	D3DXVECTOR3		m_vAngle;
	bool			m_bFinish = false;
	ROTATE_DIR		m_eRotateDir = END;

	float			m_fTimeDrop = 0.f;
	bool			m_bFlag = false;

		
	D3DXVECTOR3		m_vScale;
	D3DXVECTOR3		m_vColor;
	MANA			m_eMana = MANA_END;


	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	bool			CalculateAngle();
	void			ReSetTransform(ROTATE_DIR eType);
	HRESULT			SetManaInfo();

	explicit CManaToken(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CManaToken(const CManaToken & rhs);
	virtual ~CManaToken() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;


	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CManaToken* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END

