#include "stdafx.h"
#include "PFirework.h"
			
//===================================================================
// - written by ������
// - �Ҳɳ���
//===================================================================

PFirework::PFirework(D3DXVECTOR3 * origin, int numParticles)
{
	_origin = *origin;
	_size = 0.9f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;

	for (int i = 0; i < numParticles; i++)
	{
		AddParticle();
	}
}

void PFirework::ResetParticle(ST_Attribute * attribute)
{
	attribute->_isAlive = true;
	attribute->_position = _origin;

	D3DXVECTOR3 min = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	D3DXVECTOR3 max = D3DXVECTOR3( 1.0f,  1.0f,  1.0f);

	PSystem::GetRandomVector(&attribute->_velocity, &min, &max);

	// ��ü�� ����� ���� ����ȭ
	D3DXVec3Normalize(&attribute->_velocity, &attribute->_velocity);

	attribute->_velocity *= 1.0f;

	attribute->_color = D3DXCOLOR(PSystem::GetRandomFloat(0.0f, 1.0f),
								PSystem::GetRandomFloat(0.0f, 1.0f), 
								PSystem::GetRandomFloat(0.0f, 1.0f),
								1.0f);

	attribute->_age		 = 0.0f;
	attribute->_lifeTime = 2.0f;	// 2�� ������ ������ ����
}

// ��ƼŬ ��ġ ����, �����ʰ��� ��ƼŬ ����ó��(��Ȱ�� ���� ���� ��ƼŬ ���� ����)
void PFirework::Update(float timeDelta)
{
	std::list<ST_Attribute>::iterator i;

	for (i = _particles.begin(); i != _particles.end(); i++)
	{
		// ������ ��ƼŬ�� ����
		if (i->_isAlive)
		{
			//i->_position += i->_velocity * timeDelta;
			i->_position += i->_velocity * timeDelta;
			i->_age += timeDelta;

			if (i->_age > i->_lifeTime)	// ���δ�
				i->_isAlive = false;
		}
	}
}

void PFirework::PreRender()
{
	PSystem::PreRender();

	_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// z ���� �б�� ���������� ����� ������� ����
	_device->SetRenderState(D3DRS_ZWRITEENABLE, false);
}

void PFirework::PostRender()
{
	PSystem::PostRender();

	_device->SetRenderState(D3DRS_ZWRITEENABLE, true);
}