#include "stdafx.h"
#include "cAI_CtrlFlip.h"
#include "cCar.h"

cAI_CtrlFlip::cAI_CtrlFlip()
{
	flipTime = 0.0f;
	flipTrueTime = 1.5f;
	isFlip = false;
}


cAI_CtrlFlip::~cAI_CtrlFlip()
{
}

void cAI_CtrlFlip::Update()
{
	NxQuat quat = AI_Data->pCar->GetPhysXData()->m_pActor->getGlobalOrientationQuat();
	NxVec3 carUp = quat.transform(NxVec3(0, 1, 0), NxVec3(0, 0, 0));
	if (carUp.y < -0.5f)
	{
		flipTime += g_pTimeManager->GetElapsedTime();
	}
	else
	{
		flipTime = 0.0f;
	}

	if (flipTime > flipTrueTime)
	{
		isFlip = true;
		flipTime = 0.f;
	}
	else
	{
		isFlip = false;
	}
}

void cAI_CtrlFlip::Render()
{
}
