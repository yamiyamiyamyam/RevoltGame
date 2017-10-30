#include "stdafx.h"
#include "InGameUI.h"
#include "UITextImageView.h"
#include "UIImageView.h"

#define TIMEMAX 60

InGameUI::InGameUI()
	: m_pLobby(NULL)
	, m_ElapseTime(0.0f)
	, m_DotTenth(48)
	, m_DotMilth(48)
	, m_SecOneth(48)
	, m_SecTenth(48)
	, m_MinOneth(48)
	, m_MinTenth(48)
{
}

InGameUI::~InGameUI()
{
	SAFE_DELETE(m_pRootUI);
	SAFE_DELETE(m_pItemImage);
	SAFE_DELETE(m_pLobby);
}

void InGameUI::Setup()
{
	m_pRootUI = new UIObject;

	UITextImageView* pImageView1 = new UITextImageView;
	pImageView1->SetTexture("Maps/Front/Image/font2.png");
	pImageView1->SetText("Lab");
	pImageView1->SetXSize(1.0f);
	pImageView1->SetYSize(1.0f);
	pImageView1->SetPosition(30, 20);
	pImageView1->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	UITextImageView* pImageView2 = new UITextImageView;
	pImageView2->SetTexture("Maps/Front/Image/font2.png");
	pImageView2->SetText("Last Lap");
	pImageView2->SetXSize(1.0f);
	pImageView2->SetYSize(1.0f);
	pImageView2->SetPosition(900, 20);
	pImageView2->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	UITextImageView* pImageView3 = new UITextImageView;
	pImageView3->SetTexture("Maps/Front/Image/font2.png");
	pImageView3->SetText("Best Lab");
	pImageView3->SetXSize(1.0f);
	pImageView3->SetYSize(1.0f);
	pImageView3->SetPosition(0, 50);
	pImageView3->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	UITextImageView* pImageView4 = new UITextImageView;
	pImageView4->SetTexture("Maps/Front/Image/font2.png");
	pImageView4->SetText("Lab");
	pImageView4->SetXSize(1.0f);
	pImageView4->SetYSize(1.0f);
	pImageView4->SetPosition(39, 100);
	pImageView4->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));
	
	// << :
	m_pElapseTime = new UITextImageView;
	m_pElapseTime->SetTexture("Maps/Front/Image/font2.png");
	m_pElapseTime->SetPosition(10, 30);

	m_pDotTenth = new UITextImageView;
	m_pDotTenth->SetTexture("Maps/Front/Image/font2.png");
	m_pDotTenth->SetPosition(-10, 0);

	m_pDotMilth = new UITextImageView;
	m_pDotMilth->SetTexture("Maps/Front/Image/font2.png");
	m_pDotMilth->SetPosition(-10, 0);

	UITextImageView* pSecColon = new UITextImageView;
	pSecColon->SetTexture("Maps/Front/Image/font2.png");
	pSecColon->SetPosition(-10, 0);
	pSecColon->SetText(":");

	m_pSecOneth = new UITextImageView;
	m_pSecOneth->SetTexture("Maps/Front/Image/font2.png");
	m_pSecOneth->SetPosition(-10, 0);

	m_pSecTenth = new UITextImageView;
	m_pSecTenth->SetTexture("Maps/Front/Image/font2.png");
	m_pSecTenth->SetPosition(-10, 0);

	UITextImageView* pMinColon = new UITextImageView;
	pMinColon->SetTexture("Maps/Front/Image/font2.png");
	pMinColon->SetPosition(-10, 0);
	pMinColon->SetText(":");

	m_pMinOneth = new UITextImageView;
	m_pMinOneth->SetTexture("Maps/Front/Image/font2.png");
	m_pMinOneth->SetPosition(-10, 0);

	m_pMinTenth = new UITextImageView;
	m_pMinTenth->SetTexture("Maps/Front/Image/font2.png");
	m_pMinTenth->SetPosition(-10, 0);
	// << :

	UITextImageView* pImageView5 = new UITextImageView;
	pImageView5->SetTexture("Maps/Front/Image/font2.png");
	pImageView5->SetText("Race");
	pImageView5->SetXSize(1.0f);
	pImageView5->SetYSize(1.0f);
	pImageView5->SetPosition(32, 150);
	pImageView5->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	UIImageView* pImageView6 = new UIImageView;
	pImageView6->SetXSize(1.2f);
	pImageView6->SetYSize(1.2f);
	pImageView6->SetPosition(-5, 50);
	pImageView6->SetTexture("Maps/Front/Image/itemframe.png");

	UIImageView* pImageView7 = new UIImageView;
	pImageView7->SetIsBoard(true);
	pImageView7->SetXSize(12.0f);
	pImageView7->SetYSize(2.5f);
	pImageView7->SetPosition(20, 600);
	pImageView7->SetTexture("Maps/Front/Image/ring.png");

	UIImageView* pImageView8 = new UIImageView;
	pImageView8->SetIsBoard(true);
	pImageView8->SetXSize(12.0f);
	pImageView8->SetYSize(2.5f);
	pImageView8->SetPosition(20, 600);
	pImageView8->SetTexture("Maps/Front/Image/ring.png");

	m_pItemImage = new UIImageView;
	m_pItemImage->SetXSize(1.2f);
	m_pItemImage->SetYSize(1.2f);
	m_pItemImage->SetPosition(22, 22);
	m_pItemImage->SetIsItem(true);
	m_pItemImage->SetTexture("Maps/Front/Image/itemlist.png");

	m_pRootUI->AddChild(pImageView1);
	m_pRootUI->AddChild(pImageView2);
	m_pRootUI->AddChild(pImageView7);
	pImageView1->AddChild(pImageView6);
	pImageView2->AddChild(pImageView3);
	pImageView2->AddChild(pImageView4);
	pImageView2->AddChild(pImageView5);
	pImageView6->AddChild(m_pItemImage);
	pImageView4->AddChild(m_pElapseTime);

	m_pElapseTime->AddChild(m_pDotTenth);
	m_pDotTenth->AddChild(m_pDotMilth);
	m_pDotMilth->AddChild(pSecColon);
	pSecColon->AddChild(m_pSecOneth);
	m_pSecOneth->AddChild(m_pSecTenth);
	m_pSecTenth->AddChild(pMinColon);
	pMinColon->AddChild(m_pMinOneth);
	m_pMinOneth->AddChild(m_pMinTenth);
}

void InGameUI::Update()
{

	if (m_pRootUI)
		m_pRootUI->Update();
}

void InGameUI::Render(LPD3DXSPRITE pSprite)
{
	if (m_pRootUI)
		m_pRootUI->Render(pSprite);

}

void InGameUI::UpdateTimeLab()
{
	// 59 = :
	std::string ElaseTime;
	std::string DotTenth;
	std::string DotMilth;

	std::string SecOneth;
	std::string SecTenth;

	std::string MinOneth;
	std::string MinTenth;

	m_ElapseTime += g_pTimeManager->GetElapsedTime();

	if (m_ElapseTime > TIMEMAX)
	{
		m_ElapseTime -= TIMEMAX;
		m_MinOneth += 1;
	}
	if (m_MinOneth > FONT2_NUM9)
	{
		m_MinOneth = FONT2_NUM0;
		m_MinTenth += 1;
	}
	m_SecTenth = (m_ElapseTime / 10) + FONT2_NUM0;
	m_SecOneth = ((int)m_ElapseTime % 10) + FONT2_NUM0;


	
	float fTime = (m_ElapseTime - (int)m_ElapseTime) * 10.0f;
	DotMilth = (int)(fTime) +FONT2_NUM0;
	fTime -= (int)fTime;
	fTime *= 10.0f;
	DotTenth = (int)fTime + FONT2_NUM0;
	fTime -= (int)fTime;
	fTime *= 10.0f;
	ElaseTime = (int)fTime  + FONT2_NUM0;

	SecOneth = m_SecOneth;
	SecTenth = m_SecTenth;

	MinOneth = m_MinOneth;
	MinTenth = m_MinTenth;

	m_pElapseTime->SetText(ElaseTime);
	m_pDotTenth->SetText(DotTenth);
	m_pDotMilth->SetText(DotMilth);
	m_pSecOneth->SetText(SecOneth);
	m_pSecTenth->SetText(SecTenth);
	m_pMinOneth->SetText(MinOneth);
	m_pMinTenth->SetText(MinTenth);
}
