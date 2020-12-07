#pragma once
#include "GameObject.h"
#include "Wall.h"
#include "Transform.h"
#include "Texture.h"
#include "Renderer.h"
_BEGIN(Client)

class CIntro final : public CGameObject
{
private:
	CWall* m_Triangle = nullptr;
	CTransform* m_Transform = nullptr;
	CTexture*	m_Texture = nullptr;
	CRenderer*  m_Renderer = nullptr;

	explicit CIntro(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CIntro(const CIntro& rhs);
	virtual ~CIntro() = default;	
	
public:
	virtual HRESULT Initialize() override;
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	HRESULT InitializePrototype();
	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CIntro* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
