#include "..\Header\AnimaitionCtrl.h"
#include <iostream>



HRESULT CAnimaitionCtrl::Initialize()
{
	return NOERROR;
}

HRESULT CAnimaitionCtrl::SetAnimation(int iIndex)
{
	if (m_pAniCtrl == nullptr)
		return E_FAIL;

	if (m_iOldIndex == iIndex)
		return NOERROR;

	LPD3DXANIMATIONSET pAnimationSet = nullptr;

	if (FAILED(m_pAniCtrl->GetAnimationSet(iIndex, &pAnimationSet)))
		return E_FAIL;

	m_iNewTrack = (m_iCurrTrack == 0) ? 1 : 0;

	if (FAILED(m_pAniCtrl->SetTrackAnimationSet(m_iNewTrack, pAnimationSet)))
		return E_FAIL;
	
	Safe_Release(pAnimationSet);
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	m_pAniCtrl->UnkeyAllTrackEvents(m_iCurrTrack);
	m_pAniCtrl->UnkeyAllTrackEvents(m_iNewTrack);

	m_pAniCtrl->KeyTrackEnable(m_iCurrTrack, FALSE, m_TimeAcc+0.2f);
	m_pAniCtrl->KeyTrackSpeed(m_iCurrTrack, 1.f, m_TimeAcc, 0.2f, D3DXTRANSITION_LINEAR);
	m_pAniCtrl->KeyTrackWeight(m_iCurrTrack, 0.1f, m_TimeAcc, 0.2f, D3DXTRANSITION_LINEAR);

	m_pAniCtrl->SetTrackEnable(m_iNewTrack, TRUE);
	m_pAniCtrl->KeyTrackSpeed(m_iNewTrack, 1.f, m_TimeAcc, 0.2f, D3DXTRANSITION_LINEAR);
	m_pAniCtrl->KeyTrackWeight(m_iNewTrack, 0.9f, m_TimeAcc, 0.2f, D3DXTRANSITION_LINEAR);

	m_pAniCtrl->SetTrackPosition(m_iNewTrack, 0.0f);
	m_TimeAcc = 0.0;
	m_pAniCtrl->ResetTime();

	m_iOldIndex = iIndex;

	m_iCurrTrack = m_iNewTrack;
	/////////////////////////////////////////////////////////////////////////////////////////////////
	////다시 해야함/////////
	return NOERROR;
}

HRESULT CAnimaitionCtrl::PlayAnimation(const float & fTimeDelta)
{
	m_pAniCtrl->AdvanceTime(fTimeDelta, nullptr);
	m_TimeAcc += fTimeDelta;

	return NOERROR;
}

bool CAnimaitionCtrl::AnimationEnd(float fOffset)
{
	LPD3DXANIMATIONSET		pAnimationSet;
	m_pAniCtrl->GetAnimationSet(m_iOldIndex, &pAnimationSet);
	double dPeriod = pAnimationSet->GetPeriod();
	
	D3DXTRACK_DESC	TrackDesc;
	ZeroMemory(&TrackDesc, sizeof(D3DXTRACK_DESC));

	m_pAniCtrl->GetTrackDesc(m_iCurrTrack, &TrackDesc);

	
	if (dPeriod <= TrackDesc.Position+ fOffset)
		return true;

	return false;
}

double CAnimaitionCtrl::GetTimeTrack()
{
	LPD3DXANIMATIONSET		pAnimationSet;
	m_pAniCtrl->GetAnimationSet(m_iOldIndex, &pAnimationSet);
	double dPeriod = pAnimationSet->GetPeriod();

	D3DXTRACK_DESC	TrackDesc;
	ZeroMemory(&TrackDesc, sizeof(D3DXTRACK_DESC));

	m_pAniCtrl->GetTrackDesc(m_iCurrTrack, &TrackDesc);

	return TrackDesc.Position/ dPeriod;
}

CAnimaitionCtrl::CAnimaitionCtrl(LPD3DXANIMATIONCONTROLLER pAniCtrl)
	:m_pAniCtrl(pAniCtrl)
{
	m_pAniCtrl->AddRef();
}

CAnimaitionCtrl::CAnimaitionCtrl(const CAnimaitionCtrl & rhs)	
{
	rhs.m_pAniCtrl->CloneAnimationController(rhs.m_pAniCtrl->GetMaxNumAnimationOutputs(), rhs.m_pAniCtrl->GetMaxNumAnimationSets(), rhs.m_pAniCtrl->GetMaxNumTracks(), rhs.m_pAniCtrl->GetMaxNumEvents(), &m_pAniCtrl);
}

CAnimaitionCtrl * CAnimaitionCtrl::Create(LPD3DXANIMATIONCONTROLLER pAniCtrl)
{
	CAnimaitionCtrl* pInstance = new CAnimaitionCtrl(pAniCtrl);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CAnimaitionCtrl Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CAnimaitionCtrl * CAnimaitionCtrl::Create(const CAnimaitionCtrl & rhs)
{
	CAnimaitionCtrl* pInstance = new CAnimaitionCtrl(rhs);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CAnimaitionCtrl Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CAnimaitionCtrl::Free()
{
	Safe_Release(m_pAniCtrl);
}
