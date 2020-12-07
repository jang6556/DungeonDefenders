#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CMonsterController;
class CArcanePad :
	public CGameObject
{
public:
	enum MONSTER {MONSTER_GOBLIN,MONSTER_ARCHER,MONSTER_KOBOLD,MONSTER_END};
private:
	CTransform*		m_pTransform = nullptr;
	CShader*		m_pShader = nullptr;
	CRenderer*		m_pRenderer = nullptr;
	CMeshStatic*	m_pMeshStatic = nullptr;
	CNaviMesh*		m_pNaviMesh = nullptr;

	CMonsterController*	m_pMonsterController = nullptr;

	vector<MONSTER>	m_MonsterList;


	list<int>		m_vecRoot;

	float			m_fTimeDelta = 0.f;
	int				m_iCurrIndex = 0.f;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT Initialize(void* pArg);
	HRESULT	AddComponent();

	void	MakeRoot(D3DXVECTOR3 _vPosition);

	explicit CArcanePad(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CArcanePad(const CArcanePad & rhs);
	virtual ~CArcanePad() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CArcanePad* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);

};
_END

