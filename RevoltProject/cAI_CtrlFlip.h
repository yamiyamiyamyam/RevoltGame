#pragma once
#include "cAI.h"
class cAI_CtrlFlip :
	public cAI
{
public:
	cAI_CtrlFlip();
	~cAI_CtrlFlip();
	
	float flipTime;
	float flipTrueTime;

	void Update();
	void Render();
};

