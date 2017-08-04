#include "stdafx.h"
#include "GameScene.h"

#include "ZeroInputManager.h"


GameScene::GameScene()
{
	p = new PlayerCharacter();

	background = new ZeroSprite("Resource/Background/space.png");

	PushScene(p);

	PushScene(background);
}


GameScene::~GameScene()
{
}


void GameScene::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	background->Update(eTime);

	for (auto b : bulletList) {
		b->Update(eTime);
	}
	p->Update(eTime);

	Shooting();
	// CheckOut();

}

void GameScene::Render()
{
	ZeroIScene::Render();
	background->Render();

	for (auto b : bulletList) {
		b->Render();
	}
	p->Render();
}

void GameScene::Shooting()
{
	if (ZeroInputMgr->GetKey(VK_CONTROL) == INPUTMGR_KEYDOWN) {

		Bullet* b = new Bullet();

		b->bullet1->SetPos(p->Pos().x, p->Pos().y + 10);
		b->bullet2->SetPos(p->Pos().x + 80, p->Pos().y + 10);

		bulletList.push_back(b);
		PushScene(b);
	}
}

//void GameScene::CheckOut()
//{
//	for (auto b = bulletList.begin(); b != bulletList.end();) {
//		if ((*b)->Pos().y > 0) {
//			PopScene(*b);
//			bulletList.erase(b++);
//		}
//		else b++;
//	}
//
//}
