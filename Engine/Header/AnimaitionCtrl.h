#pragma once

#include "Base.h"

_BEGIN(Engine)
class CAnimaitionCtrl : public CBase
{
private:
	LPD3DXANIMATIONCONTROLLER m_pAniCtrl = nullptr;
	int		 m_iCurrTrack = 0;
	int		 m_iNewTrack  = 1;
	int		 m_iOldIndex  = 0;
	double	 m_TimeAcc = 0.0f;

	HRESULT Initialize();
	

	explicit CAnimaitionCtrl(LPD3DXANIMATIONCONTROLLER pAniCtrl);
	explicit CAnimaitionCtrl(const CAnimaitionCtrl& rhs);
	virtual ~CAnimaitionCtrl() =default;
public:	
	HRESULT SetAnimation(int iIndex);
	HRESULT PlayAnimation(const float& fTimeDelta);
	
	bool	AnimationEnd(float fOffset=0.f);
	double  GetTimeTrack();
	
	
	static CAnimaitionCtrl* Create(LPD3DXANIMATIONCONTROLLER pAniCtrl);
	static CAnimaitionCtrl* Create(const CAnimaitionCtrl& rhs);
	virtual void Free();
	
};
_END
