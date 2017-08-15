#include "stdafx.h"
#include "TitleScene.h"

#include "ZeroSceneManager.h"
#include "ZeroInputManager.h"

#include "GameScene.h"

TitleScene::TitleScene()
{
	title = new ZeroSprite("Resource/Text/titleText.png");

	background1 = new ZeroSprite("Resource/Background/space.png");
	background2 = new ZeroSprite("Resource/Background/space.png");

	enterText = new ZeroFont(40, "Press Enter To Start");

	PushScene(background1);
	PushScene(background2);

	background2->SetPos(background1->Pos().x, background1->Pos().y + background1->Height());

	title->SetPos(350 - (title->Width() * 0.5), 100);
	enterText->SetPos(220, 700);
}

void TitleScene::Update(float eTime)
{
	MovingBackground(eTime);

	if (ZeroInputMgr->GetKey(VK_RETURN) == INPUTMGR_KEYON) {
		ZeroSceneMgr->ChangeScene(new GameScene());
	}
}

void TitleScene::Render()
{
	background1->Render();	
	background2->Render();
	title->Render();
	enterText->Render();
}

void TitleScene::MovingBackground(float eTime)
{
	background1->AddPosY(-450 * eTime);
	background2->AddPosY(-450 * eTime);
	if (background1->Pos().y + background1->Height() <= 0) {
		background1->SetPosY(background2->Pos().y + background1->Height());
	}
	if (background2->Pos().y + background2->Height() <= 0) {
		background2->SetPosY(background1->Pos().y + background2->Height());
	}
}