#pragma once

typedef struct tagSkilInfo
{
	float	fTimeDelta;
	bool	IsCoolTime;
	float	fCoolTime;
	float	fConsumeMp;
	float	fBuildTime;
	float	fCurrBuildTime;

	tagSkilInfo()
	{
		fTimeDelta = 0.f;
		IsCoolTime = false;
		fCoolTime = 0.f;
		fConsumeMp = 0.f;
		fBuildTime = 0.f;
		fCurrBuildTime = 0.f;

	}
}SKILLINFO;

typedef struct tagPosTarget
{
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vTarget;
	tagPosTarget() {}

	tagPosTarget(D3DXVECTOR3 _vPosition, D3DXVECTOR3 _vTarget)
		:vPosition(_vPosition), vTarget(_vTarget)
	{

	}

}POS_TARGET;