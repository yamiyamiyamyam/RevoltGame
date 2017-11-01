#include "stdafx.h"
#include "RacingScene.h"
#include "cTrack.h"
#include "cLight.h"
#include "PFirework.h"
#include "Firework.h"

RacingScene::RacingScene(){}

RacingScene::~RacingScene(){}

void RacingScene::Setup()
{
	g_pCamManager->SetLookAt(&D3DXVECTOR3(0, 0, 0));
	m_pTrack = new cTrack;
	if (m_pTrack)
	{
		m_pTrack->Setup();
		m_pTrack->LoadTrack("Market2");
	}
	m_nLightIDCount = 0;

	D3DLIGHT9 light;
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient = D3DXCOLOR(0.8,0.8,0.8,1);
	light.Diffuse = D3DXCOLOR(0.8, 0.8, 0.8, 1);
	light.Specular = D3DXCOLOR(0.8, 0.8, 0.8, 1);
	D3DXVECTOR3 dir = { 0,-1,0 };
	D3DXVec3Normalize(&dir, &dir);
	light.Direction = dir;
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, true);

	pCar1 = new cCar;
	pCar1->LoadMesh("tc1");
//	m_vecObject.push_back(pCar1);


	//자동차 추가
	pVeh = MgrPhysX->createCarWithDesc(NxVec3(0, 2, 0), true, true, false, false, false, MgrPhysXSDK);

	g_pCamManager->SetCamPos(camPos);
	g_pCamManager->SetLookAt(camLookTarget);

	srand((unsigned int)time(0));

	m_pPFirework = new PFirework(&D3DXVECTOR3(15.0f, 4.0f, 0.0f), 100);
	m_pPFirework->Init(g_pD3DDevice, "Maps/Front/Image/particle_flare2.bmp");

	m_pFirework = new Firework;
	m_pFirework->Setup();

}

void RacingScene::Destroy()
{
	SAFE_DESTROY(m_pTrack);
	SAFE_DELETE(m_pTrack);
	SAFE_DELETE(m_pLightSun);
	SAFE_DELETE(m_pPFirework);
}

void RacingScene::Update()
{
	GameNode::Update();
	SAFE_UPDATE(m_pTrack);

	//TEST
	if (pVeh)
	{
		NxVec3 pos = pVeh->getGlobalPose().t;

		*camPos = D3DXVECTOR3(pos.x - 5, pos.y + 5, pos.z);
		*camLookTarget = D3DXVECTOR3(pos.x, pos.y + 3, pos.z);
		g_pCamManager->SetCamPos(camPos);
		g_pCamManager->SetLookAt(camLookTarget);

		static float angle = 0;
		if (g_pKeyManager->isOnceKeyDown('A'))
		{
			angle += 0.1;
		}
		if (g_pKeyManager->isOnceKeyDown('D'))
		{
			angle -= 0.1;
		}
		NxWheel* wheel = pVeh->getWheel(0);
		wheel->setAngle(angle);

		wheel = pVeh->getWheel(1);
		wheel->setAngle(angle);

		pVeh->getActor()->addForce(NxVec3(0, 1, 0));

		if (g_pKeyManager->isOnceKeyDown('S'))
		{
			NxWheel* wheel = pVeh->getWheel(0);
			wheel->tick(false, (NxReal)-1000, (NxReal)0, (NxReal)1.f / 60.f);
			wheel->setAngle(angle);

			wheel = pVeh->getWheel(1);
			wheel->tick(false, (NxReal)-1000, (NxReal)0, (NxReal)1.f / 60.f);
			wheel->setAngle(angle);

			wheel = pVeh->getWheel(2);
			wheel->tick(false, (NxReal)-1000, (NxReal)0, (NxReal)1.f / 60.f);

			wheel = pVeh->getWheel(3);
			wheel->tick(false, (NxReal)-1000, (NxReal)0, (NxReal)1.f / 60.f);
		}

		if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
		{
			NxWheel* wheel = pVeh->getWheel(0);
			wheel->tick(false, (NxReal)0, (NxReal)1000, (NxReal)1.f / 60.f);

			wheel = pVeh->getWheel(1);
			wheel->tick(false, (NxReal)0, (NxReal)1000, (NxReal)1.f / 60.f);

			wheel = pVeh->getWheel(2);
			wheel->tick(false, (NxReal)0, (NxReal)1000, (NxReal)1.f / 60.f);

			wheel = pVeh->getWheel(3);
			wheel->tick(false, (NxReal)0, (NxReal)1000, (NxReal)1.f / 60.f);
		}

		if (g_pKeyManager->isOnceKeyDown('W'))
		{
			NxWheel* wheel = pVeh->getWheel(0);
			wheel->tick(false, (NxReal)1000, (NxReal)0, (NxReal)1.f / 60.f);

			wheel = pVeh->getWheel(1);
			wheel->tick(false, (NxReal)1000, (NxReal)0, (NxReal)1.f / 60.f);

			wheel = pVeh->getWheel(2);
			wheel->tick(false, (NxReal)1000, (NxReal)0, (NxReal)1.f / 60.f);

			wheel = pVeh->getWheel(3);
			wheel->tick(false, (NxReal)1000, (NxReal)0, (NxReal)1.f / 60.f);
		}
	}

	m_pPFirework->Update(0.01f);

	if (m_pPFirework->isDead())		// 반복
		m_pPFirework->Reset();
}

void RacingScene::Render()
{
	//앰비언트
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(230,230,230));

	if (m_pTrack)
	{
		m_pTrack->Render();
	}

	m_pPFirework->Render();
	m_pFirework->Render();
}
