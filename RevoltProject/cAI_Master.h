#pragma once
#include "cAI.h"

#include "cAI_Ray.h"
#include "cAI_CtrlSpeed.h"
#include "cAI_CtrlHandel.h"
#include "cAI_CtrlFlip.h"
#include "cAI_Ctrl.h"


class cAI_Master
{
public:
	std::vector<cAI*> familyAI;
	bool isUpdate;
	cAI_Master();
	~cAI_Master();

	void Setup(AI_DATA pData);
	void Destory();
	void Update();
	void Render();
};

