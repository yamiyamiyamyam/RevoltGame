#include "stdafx.h"
#include "InGameUI.h"
#include "UITextImageView.h"
#include "UIImageView.h"
#include "cCar.h"
#include "cTrack.h"
#include "Object.h"
#include "cCheckBox.h"
#include "c321GO.h"
#include "RacingScene.h"

#define TIMEMAX 60

InGameUI::InGameUI()
	: m_pLobby(NULL)
	, m_WorldDotOneth(0)
	, m_LastDotOneTh(FONT2_NUM0)
	, m_LastDotTenth(FONT2_NUM0)
	, m_LastDotMilth(FONT2_NUM0)
	, m_LastSecOneth(FONT2_NUM0)
	, m_LastSecTenth(FONT2_NUM0)
	, m_LastMinOneth(FONT2_NUM0)
	, m_LastMinTenth(FONT2_NUM0)
	, m_BestDotOneTh(FONT2_NUM0)
	, m_BestDotTenth(FONT2_NUM0)
	, m_BestDotMilth(FONT2_NUM0)
	, m_BestSecOneth(FONT2_NUM0)
	, m_BestSecTenth(FONT2_NUM0)
	, m_BestMinOneth(FONT2_NUM5)
	, m_BestMinTenth(FONT2_NUM0)
	, m_ElapseTime(0.0f)
	, m_DotTenth(FONT2_NUM0)
	, m_DotMilth(FONT2_NUM0)
	, m_SecOneth(FONT2_NUM0)
	, m_SecTenth(FONT2_NUM0)
	, m_MinOneth(FONT2_NUM0)
	, m_MinTenth(FONT2_NUM0)
	, m_LabElapseTime(0.0f)
	, m_LabDotTenth(FONT2_NUM0)
	, m_LabDotMilth(FONT2_NUM0)
	, m_LabSecOneth(FONT2_NUM0)
	, m_LabSecTenth(FONT2_NUM0)
	, m_LabMinOneth(FONT2_NUM0)
	, m_LabMinTenth(FONT2_NUM0)
	, m_select(99)
	, m_LabCnt(-1)
	, m_arrowIndex(0)
{
}

InGameUI::~InGameUI()
{

}

void InGameUI::Setup()
{
	m_pRootUI = new UIObject;
	UITextImageView::m_Select = &m_select;


	//Lab
	UITextImageView* pLabCntFont = new UITextImageView;
	pLabCntFont->SetTexture("UIImage/font2.png");
	pLabCntFont->SetText("Lab");
	pLabCntFont->SetXSize(1.0f);
	pLabCntFont->SetYSize(1.0f);
	pLabCntFont->SetPosition(30, 20);
	pLabCntFont->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	m_pCurrentLab = new UITextImageView;
	m_pCurrentLab->SetTexture("UIImage/font2.png");
	m_pCurrentLab->SetPosition(0, 20);


	m_pMaxLab = new UITextImageView;
	m_pMaxLab->SetTexture("UIImage/font2.png");
	m_pMaxLab->SetPosition(10, 0);
	m_pMaxLab->SetText("/3");

	// Last Lab Timer
	UITextImageView* pLastLabFont = new UITextImageView;
	pLastLabFont->SetTexture("UIImage/font2.png");
	pLastLabFont->SetText("Last Lap");
	pLastLabFont->SetXSize(1.0f);
	pLastLabFont->SetYSize(1.0f);
	pLastLabFont->SetPosition(900, 20);
	pLastLabFont->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	m_pLastDotOneTh = new UITextImageView;
	m_pLastDotOneTh->SetTexture("UIImage/font2.png");
	m_pLastDotOneTh->SetPosition(60, 20);
	m_pLastDotOneTh->SetText("0");

	m_pLastDotTenth = new UITextImageView;
	m_pLastDotTenth->SetTexture("UIImage/font2.png");
	m_pLastDotTenth->SetPosition(-10, 0);
	m_pLastDotTenth->SetText("0");

	m_pLastDotMilth = new UITextImageView;
	m_pLastDotMilth->SetTexture("UIImage/font2.png");
	m_pLastDotMilth->SetPosition(-10, 0);
	m_pLastDotMilth->SetText("0");

	UITextImageView* pLastSecColon = new UITextImageView;
	pLastSecColon->SetTexture("UIImage/font2.png");
	pLastSecColon->SetPosition(-10, 0);
	pLastSecColon->SetText(":");

	m_pLastSecOneth = new UITextImageView;
	m_pLastSecOneth->SetTexture("UIImage/font2.png");
	m_pLastSecOneth->SetPosition(-10, 0);
	m_pLastSecOneth->SetText("0");

	m_pLastSecTenth = new UITextImageView;
	m_pLastSecTenth->SetTexture("UIImage/font2.png");
	m_pLastSecTenth->SetPosition(-10, 0);
	m_pLastSecTenth->SetText("0");

	UITextImageView* pLastMinColon = new UITextImageView;
	pLastMinColon->SetTexture("UIImage/font2.png");
	pLastMinColon->SetPosition(-10, 0);
	pLastMinColon->SetText(":");


	m_pLastMinOneth = new UITextImageView;
	m_pLastMinOneth->SetTexture("UIImage/font2.png");
	m_pLastMinOneth->SetPosition(-10, 0);
	m_pLastMinOneth->SetText("0");

	m_pLastMinTenth = new UITextImageView;
	m_pLastMinTenth->SetTexture("UIImage/font2.png");
	m_pLastMinTenth->SetPosition(-10, 0);
	m_pLastMinTenth->SetText("0");
	// << :

	// Best Lab Timer
	UITextImageView* pBestLabFont = new UITextImageView;
	pBestLabFont->SetTexture("UIImage/font2.png");
	pBestLabFont->SetText("Best Lab");
	pBestLabFont->SetXSize(1.0f);
	pBestLabFont->SetYSize(1.0f);
	pBestLabFont->SetPosition(0, 50);
	pBestLabFont->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	m_pBestDotOneTh = new UITextImageView;
	m_pBestDotOneTh->SetTexture("UIImage/font2.png");
	m_pBestDotOneTh->SetPosition(60, 20);
	m_pBestDotOneTh->SetText("0");

	m_pBestDotTenth = new UITextImageView;
	m_pBestDotTenth->SetTexture("UIImage/font2.png");
	m_pBestDotTenth->SetPosition(-10, 0);
	m_pBestDotTenth->SetText("0");

	m_pBestDotMilth = new UITextImageView;
	m_pBestDotMilth->SetTexture("UIImage/font2.png");
	m_pBestDotMilth->SetPosition(-10, 0);
	m_pBestDotMilth->SetText("0");


	UITextImageView* pBestSecColon = new UITextImageView;
	pBestSecColon->SetTexture("UIImage/font2.png");
	pBestSecColon->SetPosition(-10, 0);
	pBestSecColon->SetText(":");

	m_pBestSecOneth = new UITextImageView;
	m_pBestSecOneth->SetTexture("UIImage/font2.png");
	m_pBestSecOneth->SetPosition(-10, 0);
	m_pBestSecOneth->SetText("0");

	m_pBestSecTenth = new UITextImageView;
	m_pBestSecTenth->SetTexture("UIImage/font2.png");
	m_pBestSecTenth->SetPosition(-10, 0);
	m_pBestSecTenth->SetText("0");

	UITextImageView* pBestMinColon = new UITextImageView;
	pBestMinColon->SetTexture("UIImage/font2.png");
	pBestMinColon->SetPosition(-10, 0);
	pBestMinColon->SetText(":");

	m_pBestMinOneth = new UITextImageView;
	m_pBestMinOneth->SetTexture("UIImage/font2.png");
	m_pBestMinOneth->SetPosition(-10, 0);
	m_pBestMinOneth->SetText("5");

	m_pBestMinTenth = new UITextImageView;
	m_pBestMinTenth->SetTexture("UIImage/font2.png");
	m_pBestMinTenth->SetPosition(-10, 0);
	m_pBestMinTenth->SetText("0");
	// << :

	// Lab Timer
	UITextImageView* pLabFont = new UITextImageView;
	pLabFont->SetTexture("UIImage/font2.png");
	pLabFont->SetText("Lab");
	pLabFont->SetXSize(1.0f);
	pLabFont->SetYSize(1.0f);
	pLabFont->SetPosition(39, 100);
	pLabFont->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	m_pLabElapseTime = new UITextImageView;
	m_pLabElapseTime->SetTexture("UIImage/font2.png");
	m_pLabElapseTime->SetPosition(20, 20);
	m_pLabElapseTime->SetText("0");

	m_pLabDotTenth = new UITextImageView;
	m_pLabDotTenth->SetTexture("UIImage/font2.png");
	m_pLabDotTenth->SetPosition(-10, 0);
	m_pLabDotTenth->SetText("0");

	m_pLabDotMilth = new UITextImageView;
	m_pLabDotMilth->SetTexture("UIImage/font2.png");
	m_pLabDotMilth->SetPosition(-10, 0);
	m_pLabDotMilth->SetText("0");

	UITextImageView* pLabSecColon = new UITextImageView;
	pLabSecColon->SetTexture("UIImage/font2.png");
	pLabSecColon->SetPosition(-10, 0);
	pLabSecColon->SetText(":");

	m_pLabSecOneth = new UITextImageView;
	m_pLabSecOneth->SetTexture("UIImage/font2.png");
	m_pLabSecOneth->SetPosition(-10, 0);
	m_pLabSecOneth->SetText("0");

	m_pLabSecTenth = new UITextImageView;
	m_pLabSecTenth->SetTexture("UIImage/font2.png");
	m_pLabSecTenth->SetPosition(-10, 0);
	m_pLabSecTenth->SetText("0");

	UITextImageView* pLabMinColon = new UITextImageView;
	pLabMinColon->SetTexture("UIImage/font2.png");
	pLabMinColon->SetPosition(-10, 0);
	pLabMinColon->SetText(":");

	m_pLabMinOneth = new UITextImageView;
	m_pLabMinOneth->SetTexture("UIImage/font2.png");
	m_pLabMinOneth->SetPosition(-10, 0);
	m_pLabMinOneth->SetText("0");

	m_pLabMinTenth = new UITextImageView;
	m_pLabMinTenth->SetTexture("UIImage/font2.png");
	m_pLabMinTenth->SetPosition(-10, 0);
	m_pLabMinTenth->SetText("0");
	// << :

	// Race Timer
	UITextImageView* pRaceFont = new UITextImageView;
	pRaceFont->SetTexture("UIImage/font2.png");
	pRaceFont->SetText("Race");
	pRaceFont->SetXSize(1.0f);
	pRaceFont->SetYSize(1.0f);
	pRaceFont->SetPosition(32, 150);
	pRaceFont->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	m_pElapseTime = new UITextImageView;
	m_pElapseTime->SetTexture("UIImage/font2.png");
	m_pElapseTime->SetPosition(25, 20);
	m_pElapseTime->SetText("0");

	m_pDotTenth = new UITextImageView;
	m_pDotTenth->SetTexture("UIImage/font2.png");
	m_pDotTenth->SetPosition(-10, 0);
	m_pDotTenth->SetText("0");

	m_pDotMilth = new UITextImageView;
	m_pDotMilth->SetTexture("UIImage/font2.png");
	m_pDotMilth->SetPosition(-10, 0);
	m_pDotMilth->SetText("0");

	UITextImageView* pSecColon = new UITextImageView;
	pSecColon->SetTexture("UIImage/font2.png");
	pSecColon->SetPosition(-10, 0);
	pSecColon->SetText(":");

	m_pSecOneth = new UITextImageView;
	m_pSecOneth->SetTexture("UIImage/font2.png");
	m_pSecOneth->SetPosition(-10, 0);
	m_pSecOneth->SetText("0");

	m_pSecTenth = new UITextImageView;
	m_pSecTenth->SetTexture("UIImage/font2.png");
	m_pSecTenth->SetPosition(-10, 0);
	m_pSecTenth->SetText("0");

	UITextImageView* pMinColon = new UITextImageView;
	pMinColon->SetTexture("UIImage/font2.png");
	pMinColon->SetPosition(-10, 0);
	pMinColon->SetText(":");

	m_pMinOneth = new UITextImageView;
	m_pMinOneth->SetTexture("UIImage/font2.png");
	m_pMinOneth->SetPosition(-10, 0);
	m_pMinOneth->SetText("0");

	m_pMinTenth = new UITextImageView;
	m_pMinTenth->SetTexture("UIImage/font2.png");
	m_pMinTenth->SetPosition(-10, 0);
	m_pMinTenth->SetText("0");
	// << :

	UIImageView* pImageView6 = new UIImageView;
	pImageView6->SetXSize(1.2f);
	pImageView6->SetYSize(1.2f);
	pImageView6->SetPosition(-5, 50);
	pImageView6->SetTexture("UIImage/itemframe.png");

	UIImageView* pImageView7 = new UIImageView;
	pImageView7->SetIsBoard(true);
	pImageView7->SetXSize(15.0f);
	pImageView7->SetYSize(2.5f);
	pImageView7->SetPosition(20, 600);
	pImageView7->SetTexture("UIImage/ring.png");


	//방향 화살표
	pIV_arrowDir = new UIImageView;
	pIV_arrowDir->SetIsArrowDir(true);
	pIV_arrowDir->SetXSize(1.2f);
	pIV_arrowDir->SetYSize(1.2f);
	pIV_arrowDir->SetPosition(150, 550);
	pIV_arrowDir->SetTexture("UIImage/arrowDirection.png");

	//등수
	pITV_Rank = new UITextImageView;
	pITV_Rank->SetXSize(3.0f);
	pITV_Rank->SetYSize(3.0f);
	pITV_Rank->SetPosition(25, -50);
	pITV_Rank->SetText("8");
	pITV_Rank->SetTexture("UIImage/font2.png");

	pITV_Rank2 = new UITextImageView;
	pITV_Rank2->SetXSize(1.0f);
	pITV_Rank2->SetYSize(1.0f);
	pITV_Rank2->SetPosition(55, -45);
	pITV_Rank2->SetText("th");
	pITV_Rank2->SetTexture("UIImage/font2.png");
	pITV_Rank2->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	m_pItemImage = new UIImageView;
	m_pItemImage->SetXSize(1.2f);
	m_pItemImage->SetYSize(1.2f);
	m_pItemImage->SetPosition(22, 22);
	m_pItemImage->SetIsItem(true);
	m_pItemImage->SetTexture("UIImage/itemlist.png");
	m_pItemImage->LinkCarPt(m_pCar);

	//속도계 추가

	UIImageView* pSpeedFrame = new UIImageView;
	pSpeedFrame->SetIsSpeedFrame(true);
	pSpeedFrame->SetXSize(1.2f);
	pSpeedFrame->SetYSize(1.2f);
	pSpeedFrame->SetPosition(750, 650);
	pSpeedFrame->SetTexture("UIImage/speedFrame.png");

	m_pSpeedometerImage = new UIImageView;
	m_pSpeedometerImage->SetIsSpeed(true);
	m_pSpeedometerImage->SetXSize(1.2f);
	m_pSpeedometerImage->SetYSize(1.2f);
	m_pSpeedometerImage->SetPosition(0, 0);
	m_pSpeedometerImage->SetTexture("UIImage/speed.png");

	m_pSpeedOne = new UITextImageView;			// 1의 자리
	m_pSpeedOne->SetTexture("UIImage/font2.png");
	m_pSpeedOne->SetText("0");
	m_pSpeedOne->SetXSize(1.2f);
	m_pSpeedOne->SetYSize(1.2f);
	m_pSpeedOne->SetPosition(150, 0);

	m_pSpeedTen = new UITextImageView;			// 10의 자리
	m_pSpeedTen->SetTexture("UIImage/font2.png");
	m_pSpeedTen->SetText("");
	m_pSpeedTen->SetXSize(1.2f);
	m_pSpeedTen->SetYSize(1.2f);
	m_pSpeedTen->SetPosition(-10, 0);

	m_pSpeedHun = new UITextImageView;			// 100의 자리
	m_pSpeedHun->SetTexture("UIImage/font2.png");
	m_pSpeedHun->SetText("");
	m_pSpeedHun->SetXSize(1.2f);
	m_pSpeedHun->SetYSize(1.2f);
	m_pSpeedHun->SetPosition(-10, 0);

	UITextImageView* pSpeed_mph = new UITextImageView;
	pSpeed_mph->SetTexture("UIImage/font2.png");
	pSpeed_mph->SetText("mph");
	pSpeed_mph->SetXSize(1.2f);
	pSpeed_mph->SetYSize(1.2f);
	pSpeed_mph->SetPosition(170, 8);
	pSpeed_mph->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));


	//Result
	m_pResultRing = new UIImageView;
	m_pResultRing->SetIsBoard(true);
	m_pResultRing->SetXSize(15.0f);
	m_pResultRing->SetYSize(12.5f);
	m_pResultRing->SetPosition(400, 200);

	m_pRaceResult = new UITextImageView;
	m_pRaceResult->SetTexture("UIImage/font2.png");
	m_pRaceResult->SetXSize(1.0f);
	m_pRaceResult->SetYSize(1.0f);
	m_pRaceResult->SetPosition(10, 10);
	m_pRaceResult->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	// First
	m_pFirst = new UITextImageView;
	m_pFirst->SetTexture("UIImage/font2.png");
	m_pFirst->SetXSize(1.0f);
	m_pFirst->SetYSize(1.0f);
	m_pFirst->SetPosition(0, 30);
	m_pFirstPlayerName = new UITextImageView;
	m_pFirstPlayerName->SetTexture("UIImage/font2.png");
	m_pFirstPlayerName->SetPosition(30, 0);
	m_pFirstPlayerName->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));
	m_pFirstResultMinTenth = new UITextImageView;
	m_pFirstResultMinTenth->SetTexture("UIImage/font2.png");
	m_pFirstResultMinTenth->SetPosition(160, 0);
	m_pFirstResultMinOneth = new UITextImageView;
	m_pFirstResultMinOneth->SetTexture("UIImage/font2.png");
	m_pFirstResultMinOneth->SetPosition(10, 0);
	m_pFirstResultMinColon = new UITextImageView;
	m_pFirstResultMinColon->SetTexture("UIImage/font2.png");
	m_pFirstResultMinColon->SetPosition(10, 0);
	m_pFirstResultSecTenth = new UITextImageView;
	m_pFirstResultSecTenth->SetTexture("UIImage/font2.png");
	m_pFirstResultSecTenth->SetPosition(10, 0);
	m_pFirstResultSecOneth = new UITextImageView;
	m_pFirstResultSecOneth->SetTexture("UIImage/font2.png");
	m_pFirstResultSecOneth->SetPosition(10, 0);
	m_pFirstResultSecColon = new UITextImageView;
	m_pFirstResultSecColon->SetTexture("UIImage/font2.png");
	m_pFirstResultSecColon->SetPosition(10, 0);
	m_pFirstResultDotMilth = new UITextImageView;
	m_pFirstResultDotMilth->SetTexture("UIImage/font2.png");
	m_pFirstResultDotMilth->SetPosition(10, 0);
	m_pFirstResultDotTenth = new UITextImageView;
	m_pFirstResultDotTenth->SetTexture("UIImage/font2.png");
	m_pFirstResultDotTenth->SetPosition(10, 0);
	m_pFirstResultDotOneth = new UITextImageView;
	m_pFirstResultDotOneth->SetTexture("UIImage/font2.png");
	m_pFirstResultDotOneth->SetPosition(10, 0);


	/*          Set Child          */

	//Basic
	m_pRootUI->AddChild(pLabCntFont);
	m_pRootUI->AddChild(pLastLabFont);
	m_pRootUI->AddChild(pImageView7);
	m_pRootUI->AddChild(pSpeedFrame);
	m_pRootUI->AddChild(pIV_arrowDir);

	pLabCntFont->AddChild(pImageView6);
	pLabCntFont->AddChild(m_pCurrentLab);
	m_pCurrentLab->AddChild(m_pMaxLab);
	pLastLabFont->AddChild(pBestLabFont);
	pLastLabFont->AddChild(pLabFont);
	pLastLabFont->AddChild(pRaceFont);
	pImageView6->AddChild(m_pItemImage);

	pImageView7->AddChild(pITV_Rank);
	pImageView7->AddChild(pITV_Rank2);

	pSpeedFrame->AddChild(m_pSpeedometerImage);
	pSpeedFrame->AddChild(m_pSpeedOne);
	pSpeedFrame->AddChild(pSpeed_mph);
	m_pSpeedOne->AddChild(m_pSpeedTen);
	m_pSpeedTen->AddChild(m_pSpeedHun);


	//Last Font
	pLastLabFont->AddChild(m_pLastDotOneTh);
	m_pLastDotOneTh->AddChild(m_pLastDotTenth);
	m_pLastDotTenth->AddChild(m_pLastDotMilth);
	m_pLastDotMilth->AddChild(pLastSecColon);
	pLastSecColon->AddChild(m_pLastSecOneth);
	m_pLastSecOneth->AddChild(m_pLastSecTenth);
	m_pLastSecTenth->AddChild(pLastMinColon);
	pLastMinColon->AddChild(m_pLastMinOneth);
	m_pLastMinOneth->AddChild(m_pLastMinTenth);

	// Best Font
	pBestLabFont->AddChild(m_pBestDotOneTh);
	m_pBestDotOneTh->AddChild(m_pBestDotTenth);
	m_pBestDotTenth->AddChild(m_pBestDotMilth);
	m_pBestDotMilth->AddChild(pBestSecColon);
	pBestSecColon->AddChild(m_pBestSecOneth);
	m_pBestSecOneth->AddChild(m_pBestSecTenth);
	m_pBestSecTenth->AddChild(pBestMinColon);
	pBestMinColon->AddChild(m_pBestMinOneth);
	m_pBestMinOneth->AddChild(m_pBestMinTenth);

	// LabFont
	pLabFont->AddChild(m_pLabElapseTime);
	m_pLabElapseTime->AddChild(m_pLabDotTenth);
	m_pLabDotTenth->AddChild(m_pLabDotMilth);
	m_pLabDotMilth->AddChild(pLabSecColon);
	pLabSecColon->AddChild(m_pLabSecOneth);
	m_pLabSecOneth->AddChild(m_pLabSecTenth);
	m_pLabSecTenth->AddChild(pLabMinColon);
	pLabMinColon->AddChild(m_pLabMinOneth);
	m_pLabMinOneth->AddChild(m_pLabMinTenth);

	// RaceFont
	pRaceFont->AddChild(m_pElapseTime);
	m_pElapseTime->AddChild(m_pDotTenth);
	m_pDotTenth->AddChild(m_pDotMilth);
	m_pDotMilth->AddChild(pSecColon);
	pSecColon->AddChild(m_pSecOneth);
	m_pSecOneth->AddChild(m_pSecTenth);
	m_pSecTenth->AddChild(pMinColon);
	pMinColon->AddChild(m_pMinOneth);
	m_pMinOneth->AddChild(m_pMinTenth);

	// Result
	m_pRootUI->AddChild(m_pResultRing);
	m_pResultRing->AddChild(m_pRaceResult);
	m_pRaceResult->AddChild(m_pFirst);

	/*          First          */
	m_pFirst->AddChild(m_pFirstResultMinTenth);
	m_pFirst->AddChild(m_pFirstPlayerName);
	m_pFirstResultMinTenth->AddChild(m_pFirstResultMinOneth);
	m_pFirstResultMinOneth->AddChild(m_pFirstResultMinColon);
	m_pFirstResultMinColon->AddChild(m_pFirstResultSecTenth);
	m_pFirstResultSecTenth->AddChild(m_pFirstResultSecOneth);
	m_pFirstResultSecOneth->AddChild(m_pFirstResultSecColon);
	m_pFirstResultSecColon->AddChild(m_pFirstResultDotMilth);
	m_pFirstResultDotMilth->AddChild(m_pFirstResultDotTenth);
	m_pFirstResultDotTenth->AddChild(m_pFirstResultDotOneth);


	//========================================
	// 시작시 321GO 
	// by. 태섭
	//========================================
	m_p321go = new c321GO;
	m_p321go->LinkRacingScene(m_pRacingScene);
	m_p321go->Setup();
}

void InGameUI::Update()
{
	iLobby::Update();
	
	if (m_p321go)
	{
		m_p321go->Update();
//		return;
	}

	UpdateSpeed();
	UpdateLabCount();

	UpdateArrowDir();

	

	int nTrackCount = m_pRacingScene->GettrackEndCount();
	if (m_LabCnt > -1 && m_LabCnt < nTrackCount)	UpdateLabTime();

	if (m_LabCnt >= nTrackCount)
	{
		RaceResults();
		if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
		{
			g_SceneManager->ChangeScene("Lobby");
			*iLobby::m_gLobbyState = START_LOBBY;
		}
	}
}

void InGameUI::Render(LPD3DXSPRITE pSprite)
{
	iLobby::Render(pSprite);

	if (m_p321go)
	{
		m_p321go->Render();
	}
}

void InGameUI::Destroy()
{
	iLobby::Destroy();

	return;
	SAFE_DELETE(m_pItemImage);
	SAFE_DELETE(m_pLobby);
	//SAFE_DELETE(m_pLab);
	SAFE_DELETE(m_pCurrentLab);
	SAFE_DELETE(m_pMaxLab);
	SAFE_DELETE(m_pLastDotOneTh);
	SAFE_DELETE(m_pLastDotTenth);
	SAFE_DELETE(m_pLastDotMilth);
	SAFE_DELETE(m_pLastSecOneth);
	SAFE_DELETE(m_pLastSecTenth);
	SAFE_DELETE(m_pLastMinOneth);
	SAFE_DELETE(m_pLastMinTenth);
	SAFE_DELETE(m_pBestDotOneTh);
	SAFE_DELETE(m_pBestDotTenth);
	SAFE_DELETE(m_pBestDotMilth);
	SAFE_DELETE(m_pBestSecOneth);
	SAFE_DELETE(m_pBestSecTenth);
	SAFE_DELETE(m_pBestMinOneth);
	SAFE_DELETE(m_pBestMinTenth);
	SAFE_DELETE(m_pLabElapseTime);
	SAFE_DELETE(m_pLabDotTenth);
	SAFE_DELETE(m_pLabDotMilth);
	SAFE_DELETE(m_pLabSecOneth);
	SAFE_DELETE(m_pLabSecTenth);
	SAFE_DELETE(m_pLabMinOneth);
	SAFE_DELETE(m_pLabMinTenth);
	SAFE_DELETE(m_pElapseTime);
	SAFE_DELETE(m_pDotTenth);
	SAFE_DELETE(m_pDotMilth);
	SAFE_DELETE(m_pSecOneth);
	SAFE_DELETE(m_pSecTenth);
	SAFE_DELETE(m_pMinOneth);
	SAFE_DELETE(m_pMinTenth);
	SAFE_DELETE(m_pSpeedOne);
	SAFE_DELETE(m_pSpeedTen);
	SAFE_DELETE(m_pSpeedHun);
	SAFE_DELETE(m_pSpeedometerImage);
	SAFE_DELETE(pITV_Rank);
	SAFE_DELETE(pITV_Rank2);
	SAFE_DELETE(pIV_arrowDir);
	SAFE_DELETE(m_p321go);
	m_pTrack = NULL;
	m_pCar = NULL;
	m_pRacingScene = NULL;

	iLobby::Destroy();
}

void InGameUI::UpdateSpeed()
{
	int fTemp;
	fTemp = m_pCar->GetCurrentSpeed();
	if (fTemp >= 999)
		fTemp = 999;

	int nOne;
	int nTen;
	int nHun;

	nOne = (int)(fTemp % 10) + FONT2_NUM0;
	nTen = (int)((fTemp / 10)%10) + FONT2_NUM0;
	nHun = (int)(fTemp / 100) + FONT2_NUM0;

	if (nOne <= FONT2_NUM0) nOne = FONT2_NUM0;
	if (nTen <= FONT2_NUM0) nTen = FONT2_NUM0;
	if (nHun <= FONT2_NUM0) nHun = FONT2_NUM0;

	std::string strHun;
	std::string strTen;
	std::string strOne;

	strHun = nHun;
	strTen = nTen;
	strOne = nOne;

	m_pSpeedHun->SetText(strHun);
	m_pSpeedTen->SetText(strTen);
	m_pSpeedOne->SetText(strOne);
	m_pSpeedometerImage->SetRpmGauge(m_pCar->GetNxVehicle()->getWheel(1)->getRpm());
}

void InGameUI::UpdateLabCount()
{
	if (m_LabCnt < 1)	m_pCurrentLab->SetText("1");
	if (m_LabCnt == 1) m_pCurrentLab->SetText("2");
	if (m_LabCnt == 2) m_pCurrentLab->SetText("3");
	if (m_LabCnt > 2)
	{
		m_pCurrentLab->SetText("Finished");
		m_pMaxLab->SetText("");
	}
}

void InGameUI::UpdateLastTime()
{
	// Add String For UITextImage Text
	std::string LastDotOneth;								//		 x.xx0
	std::string LastDotTenth;								//		 x.x0x
	std::string LastDotMilth;								//		 x.0xx

	std::string LastSecOneth;								//		 0.xxx
	std::string LastSecTenth;								//		0x.xxx

	std::string LastMinOneth;								//	  0.xx.xxx
	std::string LastMinTenth;								//	 0x.xx.xxx

	if (m_LabCnt != -1)
	{
		m_LastDotOneTh = m_WorldDotOneth;
		m_LastDotTenth = m_LabDotTenth;
		m_LastDotMilth = m_LabDotMilth;
		m_LastSecOneth = m_LabSecOneth;
		m_LastSecTenth = m_LabSecTenth;
		m_LastMinOneth = m_LabMinOneth;
		m_LastMinTenth = m_LabMinTenth;

		LastDotOneth = m_LastDotOneTh;
		LastDotTenth = m_LastDotTenth;
		LastDotMilth = m_LastDotMilth;
		LastSecOneth = m_LastSecOneth;
		LastSecTenth = m_LastSecTenth;
		LastMinOneth = m_LastMinOneth;
		LastMinTenth = m_LastMinTenth;
	}

	m_pLastDotOneTh->SetText(LastDotOneth);
	m_pLastDotTenth->SetText(LastDotTenth);
	m_pLastDotMilth->SetText(LastDotMilth);
	m_pLastSecOneth->SetText(LastSecOneth);
	m_pLastSecTenth->SetText(LastSecTenth);
	m_pLastMinOneth->SetText(LastMinOneth);
	m_pLastMinTenth->SetText(LastMinTenth);
}

void InGameUI::CompareBestTime()
{
	std::string BestDotOneth;
	std::string BestDotTenth;
	std::string BestDotMilth;
	std::string BestSecOneth;
	std::string BestSecTenth;
	std::string BestMinOneth;
	std::string BestMinTenth;

	int CurrentDotOneTh = 0;
	int CurrentDotTenth = 0;
	int CurrentDotMilth = 0;
	int CurrentSecOneth = 0;
	int CurrentSecTenth = 0;
	int CurrentMinOneth = 0;
	int CurrentMinTenth = 0;

	CurrentDotOneTh = m_WorldDotOneth;
	CurrentDotTenth = m_LabDotTenth;
	CurrentDotMilth = m_LabDotMilth;
	CurrentSecOneth = m_LabSecOneth;
	CurrentSecTenth = m_LabSecTenth;
	CurrentMinOneth = m_LabMinOneth;
	CurrentMinTenth = m_LabMinTenth;

	if (m_LabCnt == 1)
	{
		m_BestDotOneTh = CurrentDotOneTh;
		m_BestDotTenth = CurrentDotTenth;
		m_BestDotMilth = CurrentDotMilth;
		m_BestSecOneth = CurrentSecOneth;
		m_BestSecTenth = CurrentSecTenth;
		m_BestMinOneth = CurrentMinOneth;
		m_BestMinTenth = CurrentMinTenth;

		int Check = 1;
	}
	else if (m_LabCnt > 1)
	{
		if (m_BestMinTenth > CurrentMinTenth)
		{
			m_BestDotOneTh = CurrentDotOneTh;
			m_BestDotTenth = CurrentDotTenth;
			m_BestDotMilth = CurrentDotMilth;
			m_BestSecOneth = CurrentSecOneth;
			m_BestSecTenth = CurrentSecTenth;
			m_BestMinOneth = CurrentMinOneth;
			m_BestMinTenth = CurrentMinTenth;
		}
		else if (m_BestMinTenth == CurrentMinTenth)
		{
			if (m_BestMinOneth > CurrentMinOneth)
			{
				m_BestDotOneTh = CurrentDotOneTh;
				m_BestDotTenth = CurrentDotTenth;
				m_BestDotMilth = CurrentDotMilth;
				m_BestSecOneth = CurrentSecOneth;
				m_BestSecTenth = CurrentSecTenth;
				m_BestMinOneth = CurrentMinOneth;
				m_BestMinTenth = CurrentMinTenth;
			}
			else if (m_BestMinOneth == CurrentMinOneth)
			{
				if (m_BestSecTenth > CurrentSecTenth)
				{
					m_BestDotOneTh = CurrentDotOneTh;
					m_BestDotTenth = CurrentDotTenth;
					m_BestDotMilth = CurrentDotMilth;
					m_BestSecOneth = CurrentSecOneth;
					m_BestSecTenth = CurrentSecTenth;
					m_BestMinOneth = CurrentMinOneth;
					m_BestMinTenth = CurrentMinTenth;
				}
				else if (m_BestSecTenth == CurrentSecTenth)
				{
					if (m_BestSecOneth > CurrentSecOneth)
					{
						m_BestDotOneTh = CurrentDotOneTh;
						m_BestDotTenth = CurrentDotTenth;
						m_BestDotMilth = CurrentDotMilth;
						m_BestSecOneth = CurrentSecOneth;
						m_BestSecTenth = CurrentSecTenth;
						m_BestMinOneth = CurrentMinOneth;
						m_BestMinTenth = CurrentMinTenth;
					}
					else if (m_BestSecOneth == CurrentSecOneth)
					{
						if (m_BestDotMilth > CurrentDotMilth)
						{
							m_BestDotOneTh = CurrentDotOneTh;
							m_BestDotTenth = CurrentDotTenth;
							m_BestDotMilth = CurrentDotMilth;
							m_BestSecOneth = CurrentSecOneth;
							m_BestSecTenth = CurrentSecTenth;
							m_BestMinOneth = CurrentMinOneth;
							m_BestMinTenth = CurrentMinTenth;
						}
						else if (m_BestDotMilth == CurrentDotMilth)
						{
							if (m_BestDotTenth > CurrentDotTenth)
							{
								m_BestDotOneTh = CurrentDotOneTh;
								m_BestDotTenth = CurrentDotTenth;
								m_BestDotMilth = CurrentDotMilth;
								m_BestSecOneth = CurrentSecOneth;
								m_BestSecTenth = CurrentSecTenth;
								m_BestMinOneth = CurrentMinOneth;
								m_BestMinTenth = CurrentMinTenth;
							}
							else if (m_BestDotTenth == CurrentDotTenth)
							{
								if (m_BestDotOneTh > CurrentDotOneTh)
								{
									m_BestDotOneTh = CurrentDotOneTh;
									m_BestDotTenth = CurrentDotTenth;
									m_BestDotMilth = CurrentDotMilth;
									m_BestSecOneth = CurrentSecOneth;
									m_BestSecTenth = CurrentSecTenth;
									m_BestMinOneth = CurrentMinOneth;
									m_BestMinTenth = CurrentMinTenth;
								}
							}
						}
					}
				}
			}
		}
	}

	BestDotOneth = m_BestDotOneTh;
	BestDotTenth = m_BestDotTenth;
	BestDotMilth = m_BestDotMilth;
	BestSecOneth = m_BestSecOneth;
	BestSecTenth = m_BestSecTenth;
	BestMinOneth = m_BestMinOneth;
	BestMinTenth = m_BestMinTenth;

	m_pBestDotOneTh->SetText(BestDotOneth);
	m_pBestDotTenth->SetText(BestDotTenth);
	m_pBestDotMilth->SetText(BestDotMilth);
	m_pBestSecOneth->SetText(BestSecOneth);
	m_pBestSecTenth->SetText(BestSecTenth);
	m_pBestMinOneth->SetText(BestMinOneth);
	m_pBestMinTenth->SetText(BestMinTenth);
}

void InGameUI::UpdateLabTime()
{
	// Add String For UITextImage Text
	std::string LabElapseTime;										// Elase(x.xx0)
	std::string LabDotTenth;										//		 x.x0x
	std::string LabDotMilth;										//		 x.0xx

	std::string LabSecOneth;										//		 0.xxx
	std::string LabSecTenth;										//		0x.xxx

	std::string LabMinOneth;										//	  0.xx.xxx
	std::string LabMinTenth;										//	 0x.xx.xxx

																	//if (m_LabCnt == -1)	m_LabElapseTime = 0;
																	//else if (m_LabCnt == 0)	m_LabElapseTime += g_pTimeManager->GetElapsedTime();			// Uptate ElapsedTime
	m_LabElapseTime += g_pTimeManager->GetElapsedTime();

	//if (g_pKeyManager->isOnceKeyDown('B'))
	//{
	//	//if (m_LabCnt == -1) m_LabCnt += 1;
	//	//else m_LabCnt -= 1;
	//
	//	m_LabElapseTime = 0;
	//}

	if (m_LabElapseTime > TIMEMAX)									// After 60 Second
	{
		m_LabElapseTime = 0;										// ElapsedTime = 0
		m_LabMinOneth += 1;											// Add 1 Minute
	}
	if (m_LabMinOneth > FONT2_NUM9)									// After 10 Minute
	{
		m_LabMinOneth = FONT2_NUM0;									// MinuteOneth = 0; 
		m_LabMinTenth += 1;											// Add MinuteTenth ( 09:59 -> 10:00 )
	}
	if (m_LabMinTenth > FONT2_NUM9)
	{
		m_LabMinTenth = FONT2_NUM0;
	}
	m_LabSecTenth = (m_LabElapseTime / 10) + FONT2_NUM0;			// Ex : m_ElapseTime = 59
	m_LabSecOneth = ((int)m_LabElapseTime % 10) + FONT2_NUM0;		//      m_ElapseTime / 10 = 5;	
																	//      m_ElapseTime % 10 = 9;
																	//      Therefore Current Second : 59


																	//		EX : m_ElapseTime = 9.876
	float CalcDP = (m_LabElapseTime - (int)m_LabElapseTime) * 10.0f;	//		CalcDP = (9.876 - 9) * 10 = 8.76
	m_LabDotTenth = (int)(CalcDP)+FONT2_NUM0;								//		x.?xx = x.8xx
	CalcDP -= (int)CalcDP;												//		CalcDP = 8.76 - 8 = 0.76
	CalcDP *= 10.0f;													//		CalcDP = 0.76 * 10 = 7.6
	m_LabDotMilth = (int)CalcDP + FONT2_NUM0;								//		x.8?x = x.87x
	CalcDP -= (int)CalcDP;												//		CalcDP = 7.6 - 7 = 0.6
	CalcDP *= 10.0f;													//		CalcDP = 0.6 * 10 = 6
	LabElapseTime = (int)CalcDP + FONT2_NUM0;							//		x.87? = x.876
																		//		Therefore Calculation Decimal Point = 0.876

																		/*          Add String          */
	LabDotTenth = m_LabDotTenth;
	LabDotMilth = m_LabDotMilth;

	LabSecOneth = m_LabSecOneth;
	LabSecTenth = m_LabSecTenth;

	LabMinOneth = m_LabMinOneth;
	LabMinTenth = m_LabMinTenth;



	/*          Set Text          */
	m_pLabElapseTime->SetText(LabElapseTime);
	m_pLabDotTenth->SetText(LabDotTenth);
	m_pLabDotMilth->SetText(LabDotMilth);
	m_pLabSecOneth->SetText(LabSecOneth);
	m_pLabSecTenth->SetText(LabSecTenth);
	m_pLabMinOneth->SetText(LabMinOneth);
	m_pLabMinTenth->SetText(LabMinTenth);
}
void InGameUI::UpdateRaceTime()
{
	// Add String For UITextImage Text
	std::string ElapseTime;								// Elase(x.xx0)
	std::string DotTenth;								//		 x.x0x
	std::string DotMilth;								//		 x.0xx

	std::string SecOneth;								//		 0.xxx
	std::string SecTenth;								//		0x.xxx

	std::string MinOneth;								//	  0.xx.xxx
	std::string MinTenth;								//	 0x.xx.xxx

	m_ElapseTime = m_pCar->GetTotlaTimeCount();
	//m_ElapseTime += g_pTimeManager->GetElapsedTime();	// Uptate ElapsedTime
	int CalcMin = (int)(m_ElapseTime / 60.f);
	m_MinOneth = CalcMin % 10 + FONT2_NUM0;
	m_MinTenth = CalcMin / 10 + FONT2_NUM0;
	//if (m_ElapseTime > TIMEMAX)							// After 60 Second
	//{
	//	m_ElapseTime = 0;								// ElapsedTime = 0
	//	m_MinOneth += 1;								// Add 1 Minute
	//}
	//f (m_MinOneth > FONT2_NUM9)						// After 10 Minute
	//
	//	m_MinOneth = FONT2_NUM0;						// MinuteOneth = 0; 
	//	m_MinTenth += 1;								// Add MinuteTenth ( 09:59 -> 10:00 )
	//
	//if (m_MinTenth > FONT2_NUM9)
	//{
	//	m_MinTenth = FONT2_NUM0;
	//}
	m_SecTenth = (int(m_ElapseTime / 10) % 6) + FONT2_NUM0;		// Ex : m_ElapseTime = 59
	m_SecOneth = ((int)m_ElapseTime % 10) + FONT2_NUM0; //      m_ElapseTime / 10 = 5;	
														//      m_ElapseTime % 10 = 9;
														//      Therefore Current Second : 59


																//		EX : m_ElapseTime = 9.876
	float CalcDP = (m_ElapseTime - (int)m_ElapseTime) * 10.0f;	//		CalcDP = (9.876 - 9) * 10 = 8.76
	DotMilth = m_DotMilth = (int)(CalcDP) + FONT2_NUM0;	//		x.?xx = x.8xx
	CalcDP -= (int)CalcDP;										//		CalcDP = 8.76 - 8 = 0.76
	CalcDP *= 10.0f;											//		CalcDP = 0.76 * 10 = 7.6
	DotTenth = m_DotTenth = (int)CalcDP + FONT2_NUM0;						//		x.8?x = x.87x
	CalcDP -= (int)CalcDP;										//		CalcDP = 7.6 - 7 = 0.6
	CalcDP *= 10.0f;											//		CalcDP = 0.6 * 10 = 6
	ElapseTime = (int)CalcDP + FONT2_NUM0;						//		x.87? = x.876
	m_WorldDotOneth = (int)CalcDP + FONT2_NUM0;;				//		Therefore Calculation Decimal Point = 0.876

																				/*          Add String          */
	SecOneth = m_SecOneth;
	SecTenth = m_SecTenth;

	MinOneth = m_MinOneth;
	MinTenth = m_MinTenth;



	/*          Set Text          */
	m_pElapseTime->SetText(ElapseTime);
	m_pDotTenth->SetText(DotTenth);
	m_pDotMilth->SetText(DotMilth);
	m_pSecOneth->SetText(SecOneth);
	m_pSecTenth->SetText(SecTenth);
	m_pMinOneth->SetText(MinOneth);
	m_pMinTenth->SetText(MinTenth);
}

void InGameUI::UpdateArrowDir()
{
	int curboxID = m_pCar->GetNextCheckBoxID();
	cCheckBox* checkboxPt = (cCheckBox*)m_pTrack->GetCheckBoxs()[curboxID];
	D3DXVECTOR3 posCheckbox = checkboxPt->GetPosition();
	D3DXVECTOR3 tar = posCheckbox;
	tar.y = 0.0f;

	D3DXVECTOR3 pos = D3DXVECTOR3(m_pCar->GetPosition().x, 0.0f, m_pCar->GetPosition().z);	// 자동차 위치
	D3DXVECTOR3 carDir = D3DXVECTOR3(m_pCar->GetDirection().x, 0.0f, m_pCar->GetDirection().z);	// 차 방향
	D3DXVECTOR3 arrowDir = tar - checkboxPt->GetNextCheckBox()->GetPosition();				// 화살표 방향

	D3DXVec3Normalize(&carDir, &carDir);
	D3DXVec3Normalize(&arrowDir, &arrowDir);

	// 내적
	float dot = D3DXVec3Dot(&carDir, &arrowDir);
	float angle = acos(dot);

	// 오른쪽 왼쪽 방향 구분위해
	D3DXVECTOR3 rightDir;
	D3DXVec3Normalize(&rightDir, &rightDir);

	D3DXVec3Cross(&rightDir, &carDir, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	if (D3DXVec3Dot(&rightDir, &arrowDir) < 0)
	{
		angle = -angle;
	}

	pIV_arrowDir->SetArrowAngle(-angle);
}

void InGameUI::RaceResults()
{
	// String

	/*          First          */
	std::string FstResultElapseTime;								
	std::string FstResultDotTenth;								
	std::string FstResultDotMilth;								
	std::string FstResultSecOneth;								
	std::string FstResultSecTenth;								
	std::string FstResultMinOneth;								
	std::string FstResultMinTenth;	

	/*          Sec          */
	std::string SndResultElapseTime;
	std::string SndResultDotTenth;
	std::string SndResultDotMilth;
	std::string SndResultSecOneth;
	std::string SndResultSecTenth;
	std::string SndResultMinOneth;
	std::string SndResultMinTenth;

	/*         Third          */
	std::string TrdResultElapseTime;
	std::string TrdResultDotTenth;
	std::string TrdResultDotMilth;
	std::string TrdResultSecOneth;
	std::string TrdResultSecTenth;
	std::string TrdResultMinOneth;
	std::string TrdResultMinTenth;

	/*         Fourth          */
	std::string FourthResultElapseTime;
	std::string FourthResultDotTenth;
	std::string FourthResultDotMilth;
	std::string FourthResultSecOneth;
	std::string FourthResultSecTenth;
	std::string FourthResultMinOneth;
	std::string FourthResultMinTenth;

	/*         Fifth          */
	std::string FifthResultElapseTime;
	std::string FifthResultDotTenth;
	std::string FifthResultDotMilth;
	std::string FifthResultSecOneth;
	std::string FifthResultSecTenth;
	std::string FifthResultMinOneth;
	std::string FifthResultMinTenth;

	/*         Sixth          */
	std::string SixthResultElapseTime;
	std::string SixthResultDotTenth;
	std::string SixthResultDotMilth;
	std::string SixthResultSecOneth;
	std::string SixthResultSecTenth;
	std::string SixthResultMinOneth;
	std::string SixthResultMinTenth;

	/*         Seventh          */
	std::string SeventhResultElapseTime;
	std::string SeventhResultDotTenth;
	std::string SeventhResultDotMilth;
	std::string SeventhResultSecOneth;
	std::string SeventhResultSecTenth;
	std::string SeventhResultMinOneth;
	std::string SeventhResultMinTenth;

	/*         Eighth          */
	std::string EighthResultElapseTime;
	std::string EighthResultDotTenth;
	std::string EighthResultDotMilth;
	std::string EighthResultSecOneth;
	std::string EighthResultSecTenth;
	std::string EighthResultMinOneth;
	std::string EighthResultMinTenth;


	FstResultElapseTime		= m_WorldDotOneth;
	FstResultDotTenth		= m_DotTenth;
	FstResultDotMilth		= m_DotMilth;
	FstResultSecOneth		= m_SecOneth;
	FstResultSecTenth		= m_SecTenth;
	FstResultMinOneth		= m_MinOneth;
	FstResultMinTenth		= m_MinTenth;





	m_pResultRing->SetTexture("UIImage/ring.png");
	m_pRaceResult->SetText("Race Results");
	m_pFirstResultMinTenth->SetText(FstResultMinTenth);
	m_pFirstResultMinOneth->SetText(FstResultMinOneth);
	m_pFirstResultMinColon->SetText(":");
	m_pFirstResultSecTenth->SetText(FstResultSecTenth);
	m_pFirstResultSecOneth->SetText(FstResultSecOneth);
	m_pFirstResultSecColon->SetText(":");
	m_pFirstResultDotMilth->SetText(FstResultDotMilth);
	m_pFirstResultDotTenth->SetText(FstResultDotTenth);
	m_pFirstResultDotOneth->SetText(FstResultElapseTime);
	m_pFirstPlayerName->SetText(g_pDataManager->vecPlayerData[0]->ID);
	m_pFirst->SetText("01");
}

void InGameUI::LinkCarPt(cCar * car)
{
	m_pCar = car;
}
