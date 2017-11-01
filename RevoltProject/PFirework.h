#pragma once

#include "PSystem.h"

//===================================================================
// - written by 정종훈
// - 불꽃놀이
//===================================================================


class PFirework : public PSystem
{
public:
	// 시스템 원천(폭팔할 장소)으로의 포인터, 시스템이 가진 파티클의 수
	PFirework(D3DXVECTOR3* origin, int numParticles);
	virtual void ResetParticle(ST_Attribute* attribute);
	virtual void Update(float timeDelta);
	virtual void PreRender();
	virtual void PostRender();
};

