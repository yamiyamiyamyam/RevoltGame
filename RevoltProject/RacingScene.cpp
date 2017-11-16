#include "stdafx.h"
#include "RacingScene.h"
#include "cTrack.h"
#include "cLight.h"
#include "cCar.h"
#include "InGameUI.h"
#include "UITextImageView.h"
#include "cSkyBox.h"
#include "c321GO.h"
#include "cAI_Master.h"

RacingScene::RacingScene()
	: m_select(99)
	, m_pSkyBox(NULL)
{}

RacingScene::~RacingScene() {}

void RacingScene::Setup()
{
	playerIndex = 0;
	m_eRaceProg = RACE_PROG_READY;

	//TrackEndCount 돌아야 되는 바퀴 수	
	m_trackEndCount = 3;

	//카메라 초기값
	m_camPos = new D3DXVECTOR3(70, 5, 0);
	m_camLookTarget = new D3DXVECTOR3(0, 0, 0);

	UITextImageView::m_Select = &m_select;

	D3DXCreateSprite(g_pD3DDevice, &m_Sprite);
	g_pCamManager->SetLookAt(&D3DXVECTOR3(0, 0, 0));

	m_pTrack = new cTrack;
	if (m_pTrack)
	{
		m_pTrack->Setup();
		m_pTrack->LoadTrack(g_pDataManager->mapName);
	}
	m_nLightIDCount = 0;

	m_pLightSun = new cLight;
	m_pLightSun->SetupDirectional(0, D3DCOLOR_XRGB(192,192,192), { 0,-1,0 });
	m_pLightSun->Switch(true);

	g_pCamManager->SetCamPos(m_camPos);
	g_pCamManager->SetLookAt(m_camLookTarget);

	//앰비언트
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));

	m_pSkyBox = new cSkyBox;
	m_pSkyBox->Setup("Maps/SkyBox", "SkyBox.obj");

	int i = 0;
	for each(cPlayerData* p in g_pDataManager->vecPlayerData)
	{
		if (i  == m_pTrack->GetStartPositions().size()) break;
		CreateCar(m_pTrack->GetStartPositions()[i], i, p->CAR_NAME, p->IsAI, p->isUser);
		i++;
	}

	m_pInGameUI = new InGameUI;
	LinkUI(0); // 인게임 InGameUI::Setup(); 전에 위치해야함, new InGameUI 가 선언되어 있어야 함.
	m_pInGameUI->Setup();
	
	g_pNetworkManager->SetResetKeyEvent();

//	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

void RacingScene::Destroy()
{
	SAFE_DESTROY(m_pTrack);
	SAFE_DELETE(m_pTrack);

	m_pLightSun->Destroy();
	SAFE_DELETE(m_pLightSun);

	m_pInGameUI->Destroy();
	SAFE_DELETE(m_pInGameUI);
	SAFE_DESTROY(m_pSkyBox);
	SAFE_DELETE(m_pSkyBox);
	SAFE_DELETE(m_camPos);
	SAFE_DELETE(m_camLookTarget);

	for each(cCar* p in vecCars)
	{
		p->Destroy();
		SAFE_DELETE(p);
	}
	vecCars.clear();
}

void RacingScene::Update()
{
	GameNode::Update();
	SAFE_UPDATE(m_pTrack);

	if (g_pNetworkManager->GetIsInGameNetwork())
		NetworkLoop();		// 네트워크 데이터 받는 메서드

	switch (m_eRaceProg)
	{
	case RACE_PROG_READY:
	case RACE_PROG_SET:
	case RACE_PROG_GO:
	{
		if (m_eRaceProg == RACE_PROG_GO)
		{
			m_pInGameUI->UpdateRaceTime();

			for (int i = 0; i < vecCars.size(); i++)
			{
				vecCars[i]->m_isCtl = true;;
			}
		}
		if (g_pNetworkManager->GetIsInGameNetwork())
		{
			SetNetworkCarData();
			//m_pInGameUI->UpdateRaceTime();
		}
		else
		{
			for (int i = 0; i < vecCars.size(); i++)
			{
				if (IsCarRunTrue(vecCars[i])) vecCars[i]->Update();

				if (!IsCarRunTrue(vecCars[0])) m_eRaceProg = RACE_PROG_FINISH;
			}
		}
	}
	break;
	case RACE_PROG_FINISH:
	{
		for (int i = 0; i < vecCars.size(); i++)
		{
			vecCars[i]->RunEnd();
		}
	}
	break;
	default: break;
	}

	if (m_pInGameUI)
	{
		m_pInGameUI->Update();
	}

	
}

void RacingScene::Render()
{
	//D3DXVECTOR3 forward = *g_pCamManager->GetLookAt() - *g_pCamManager->GetCamPos();
	//D3DXVec3Normalize(&forward, &forward);


	//LPD3DXMESH mesh;
	//D3DXCreateTeapot(g_pD3DDevice, &mesh, 0);

	//D3DMATERIAL9 mtl;
	//mtl.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	//mtl.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	//mtl.Emissive = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	//mtl.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	//g_pD3DDevice->SetMaterial(&mtl);

	//D3DXMATRIXA16 mat, matR, matT, matS;

	//D3DXMatrixScaling(&matS, 1, 1, 1);

	//D3DXMatrixTranslation(&matT,
	//	vecCars[0]->GetPosition().x,
	//	vecCars[0]->GetPosition().y,
	//	vecCars[0]->GetPosition().z);

	////D3DXMatrixIdentity(&matR);
	//D3DXMatrixRotationZ(&matR, (D3DX_PI / 2.0f));
	////D3DXVec3TransformNormal(&forward, &forward, &matR);

	//mat = matS * vecCars[0]->GetMatrix(0,1,0) * matT;
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);

	//mesh->DrawSubset(0);



	if (m_pSkyBox)
	{
		m_pSkyBox->Render();
	}

	if (m_pTrack)
	{
		m_pTrack->Render();
	}

	for each(cCar* p in vecCars)
	{
		p->Render();
	}

	m_pInGameUI->Render(m_Sprite);
}

void RacingScene::LastUpdate()
{
	m_pTrack->LastUpdate();

	for each(cCar* p in vecCars)
	{
		p->LastUpdate();
	}

	UpdateCamera();
	UpdateSound();
}

void RacingScene::UpdateCamera()
{

#define CAM_X (*m_camPos).x
#define CAM_Y (*m_camPos).y
#define CAM_Z (*m_camPos).z
#define CAM_POS (*m_camPos)

	//회전 매트릭스 받아옴
	//D3DXMATRIXA16 matR = vecCars[0]->GetCarRotMatrix();
	D3DXMATRIXA16 matR;
	matR = vecCars[0]->GetMatrix(false, true, false); //이걸 사용하면 약간 부정확함

	float distToCar = 5; //차와의 거리
	float Height = 1; //카메라 높이
	float LerpSpd = 0.02f;

	D3DXVECTOR3 carDir = { 1,0,0 };
	D3DXVec3TransformNormal(&carDir, &carDir, &matR);

	//자동차 포지션
	D3DXVECTOR3 carPos = {
		vecCars[0]->GetPosition().x,
		vecCars[0]->GetPosition().y + 0.5f ,
		vecCars[0]->GetPosition().z };

	//D3DXVECTOR3 carPos = {
	//	vecCars[0]->GetPhysXData()->m_pActor->getGlobalPosition().x,
	//	vecCars[0]->GetPhysXData()->m_pActor->getGlobalPosition().y + 0.5f ,
	//	vecCars[0]->GetPhysXData()->m_pActor->getGlobalPosition().z };

	*m_camLookTarget = carPos;//D3DXVECTOR3(pos.x, pos.y + 2.f, pos.z);

	D3DXVECTOR3 camDir = (*m_camLookTarget) - CAM_POS;
	D3DXVec3Normalize(&camDir, &camDir);

	//레이초기화
	NxRay RayCam;
	RayCam.orig = NxVec3(carPos);
	RayCam.dir = NxVec3(-carDir);

	NxRaycastHit RayCamHit;
	RayCamHit.shape = NULL;
	g_pPhysXScene->raycastClosestShape(RayCam, NxShapesType::NX_ALL_SHAPES, RayCamHit, 0xffffffff, distToCar);

	//레이초기화
	NxRay RayCamVertical;
	RayCamVertical.orig = NxVec3(carPos);
	RayCamVertical.dir = NxVec3(0, 1, 0);

	NxRaycastHit RayCamVerticalHit;
	RayCamVerticalHit.shape = NULL;

	g_pPhysXScene->raycastClosestShape(RayCamVertical, NxShapesType::NX_ALL_SHAPES, RayCamVerticalHit, 0xffffffff, Height);

	float x = carPos.x - (carDir.x * distToCar);
	float y = carPos.y - (carDir.y * distToCar) + Height;
	float z = carPos.z - (carDir.z * distToCar);

	float fCamHeight = Height;

	if (RayCamHit.shape)
	{
		if (RayCamHit.shape->getActor().getName())
		{
			std::string str = RayCamHit.shape->getActor().getName();

			if (str == "map")
			{
				x = RayCamHit.worldImpact.x;
				//y = carPos.y + Height;//RayCamHit.worldImpact.y;
				y = carPos.y + fCamHeight;
				z = RayCamHit.worldImpact.z;
			}
		}
	}

	if (RayCamVerticalHit.shape)
	{
		if (RayCamVerticalHit.shape->getActor().getName())
		{
			std::string str = RayCamVerticalHit.shape->getActor().getName();
			if (str == "map")
			{
				fCamHeight = RayCamVerticalHit.distance;
				y = carPos.y + fCamHeight;
			}
		}
	}

	// 카메라 목적지
	D3DXVECTOR3 vDest = { x,y,z };

	// 카메라 무빙

	if(m_eRaceProg == RACE_PROG_READY)
	{
		LerpSpd = 0.02f;
		D3DXVECTOR3 dist = *m_camPos - vDest;
		float fDist = D3DXVec3Length(&dist);
		if (fDist < 0.1)
		{
			m_pInGameUI->Get321goPt()->StartCount();
			m_eRaceProg = RACE_PROG_SET;
		}
	}
	else if (m_eRaceProg == RACE_PROG_SET)
	{
		LerpSpd = 0.05f;
	}
	else
	{
		LerpSpd = 0.2f;
	}

	D3DXVec3Lerp(m_camPos, m_camPos, &vDest, LerpSpd);
	//CAM_POS = vDest;
	g_pCamManager->SetCamPos(m_camPos);
	g_pCamManager->SetLookAt(m_camLookTarget);
}

void RacingScene::UpdateSound()
{
	D3DXVECTOR3 forward = *g_pCamManager->GetCamPos() - *g_pCamManager->GetLookAt();
	D3DXVec3Normalize(&forward, &forward);

	//D3DXMATRIXA16 matR;

	//D3DXMatrixRotationX(&matR, (D3DX_PI/2.0f));
	//D3DXVec3TransformNormal(&forward, &forward, &matR);
	//g_pSoundManager->Setup3DCamera(*g_pCamManager->GetCamPos(), forward);
	g_pSoundManager->Setup3DCamera(vecCars[0]->GetPosition(), forward);
	//g_pSoundManager->Setup3DCamera(*g_pCamManager->GetCamPos(), vecCars[0]->GetDirection());
}

bool RacingScene::IsCarRunTrue(cCar* pCar)
{
	return m_trackEndCount > pCar->GetCountRapNum();
}

void RacingScene::CreateCar(D3DXVECTOR3 setPos, int playerID, std::string carName, bool isAI, bool isUser)
{
	cCar* pCar = new cCar;
	AI_DATA aiData(pCar, m_pTrack, &vecCars);
	pCar->SetPlayerID(playerID);
	pCar->LoadCar(carName);
	pCar->SetAI(isAI, aiData);
	pCar->SetIsUser(isUser);
	vecCars.push_back(pCar);

	pCar->GetPhysXData()->SetPosition(m_pTrack->GetStartPositions()[playerID]);
}

void RacingScene::LinkUI(int playerID)
{
	m_pInGameUI->LinkCarPt(vecCars[playerID]);
	vecCars[playerID]->LinkUI(m_pInGameUI);
	m_pInGameUI->LinkTrack(m_pTrack);
	m_pInGameUI->LinkRacingScene(this);
	for (int i = 0; i < vecCars.size(); i++)
	{
		vecCars[i]->LinkTrackPt(m_pTrack);
	}
}

void RacingScene::NetworkLoop()
{
	std::string str = "";

	char* pchIP = NULL;
	char* pchKEY = NULL;
	char* pchPOS = NULL;
	char* pchX = NULL;
	char* pchY = NULL;
	char* pchZ = NULL;

	str = "$" + g_pNetworkManager->GetClientIP() + "$" + g_pNetworkManager->GetKeYString();
	g_pNetworkManager->SendMsg(str.c_str());

	if (g_pNetworkManager->RecvMsg())
	{
		str = g_pNetworkManager->GetMsg();
	}

	pchIP = strtok((char*)str.c_str(), "$");
	pchKEY = strtok(NULL, "$");

	////pchPOS = strtok(NULL, "@");
	//
	if (pchIP != NULL && g_pNetworkManager->GetClientIP().find(pchIP) == -1)
	{
		//	//pchX = strtok(pchPOS, "/");
		//	//pchY = strtok(NULL, "/");
		//	//pchZ = strtok(NULL, "/");
		//
		printf("%s\n", pchKEY);
	}
}

void RacingScene::SetNetworkCarData()
{
	g_pNetworkManager->SetResetKeyEvent();
	if (IsCarRunTrue(vecCars[0]))
	{
		vecCars[0]->Update();
	}

	if (IsCarRunTrue(vecCars[0])) vecCars[0]->Update();
	if (!IsCarRunTrue(vecCars[0])) m_eRaceProg = RACE_PROG_FINISH;

	
}
