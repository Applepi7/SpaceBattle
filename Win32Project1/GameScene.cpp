#include "stdafx.h"
#include "GameScene.h"



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

	p->Update(eTime);

}

void GameScene::Render()
{
	ZeroIScene::Render();
	background->Render();

	p->Render();
}
