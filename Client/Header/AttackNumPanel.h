
#include "StatUI.h"
_BEGIN(Client)
class CNumIcon;
class CAttackNumPanel :
	public CStatUI
{
private:
	vector<CNumIcon*>	m_vNumIcon;

	virtual HRESULT Initialize() override;
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	Add_UI_Object(void * pArg);

	explicit CAttackNumPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CAttackNumPanel(const CAttackNumPanel & rhs);
	virtual ~CAttackNumPanel() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CAttackNumPanel* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);

};
_END