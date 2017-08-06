#include "stdafx.h"
#include "GameScene.h"

#include "ZeroInputManager.h"


GameScene::GameScene() : playerShootingT(0.f, 0.5f), enemyShootingT(0.f, 0.5f), isShooting(true)
{
	p = new PlayerCharacter();
	e = new Enemy();

	background = new ZeroSprite("Resource/Background/space.png");

	PushScene(p);
	PushScene(e);

	PushScene(background);
}


GameScene::~GameScene()
{
}


void GameScene::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	background->Update(eTime);

	for (auto b : PbulletList) {
		b->Update(eTime);
	}
	for (auto eB : EbulletList) {
		eB->Update(eTime);
	}
	p->Update(eTime);
	e->Update(eTime);

	playerShootingT.first += eTime;

	PlayerShooting(eTime);
	EnemyShooting(eTime);

	CheckOut();

}

void GameScene::Render()
{
	ZeroIScene::Render();
	background->Render();

	for (auto pB : PbulletList) {
		pB->Render();
	}
	for (auto eB : EbulletList) {
		eB->Render();
	}

	e->Render();
	p->Render();
}

void GameScene::PlayerShooting(float eTime)
{
	playerShootingT.first += eTime;

	if (playerShootingT.first >= playerShootingT.second) {
		Bullet* b = new Bullet(0);

		b->bullet1->SetPos(p->Pos().x, p->Pos().y + 10);
		b->bullet2->SetPos(p->Pos().x + 80, p->Pos().y + 10);

		PbulletList.push_back(b);
		PushScene(b);

		playerShootingT.first = 0;
	}
}

void GameScene::EnemyShooting(float eTime)
{
	enemyShootingT.first += eTime;

	if (enemyShootingT.first >= enemyShootingT.second) {
		Bullet* b = new Bullet(1);

		b->bullet1->SetPos(e->Pos().x, e->Pos().y + 50);
		b->bullet2->SetPos(e->Pos().x + 80, e->Pos().y + 50);

		EbulletList.push_back(b);
		PushScene(b);

		enemyShootingT.first = 0;
	}
}

void GameScene::CheckOut()
{
	for (auto b = PbulletList.begin(); b != PbulletList.end();) {

		if ((*b)->Pos().y < 0) {
			PopScene(*b);
			PbulletList.erase(b++);
		}
		else b++;
	}

}
