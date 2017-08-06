#include "stdafx.h"
#include "GameScene.h"

#include "Global.h"

#include "ZeroInputManager.h"


GameScene::GameScene() : playerShootingT(0.f, 0.5f), enemyShootingT(0.f, 0.5f), EspawnTimer(0.0f, 5.0f),isShooting(true)
{
	p = new PlayerCharacter();

	background = new ZeroSprite("Resource/Background/space.png");
	ship = new ZeroSprite("Resource/Background/ship.png");

	PushScene(p);

	PushScene(background);
	PushScene(ship);

	ship->SetPos(-10, 750);
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

	for (auto e : enemyList) {
		e->Update(eTime);
	}
	p->Update(eTime);
	

	playerShootingT.first += eTime;

	PlayerShooting(eTime);
	SpawnEnemy(eTime);
	EnemyShooting(eTime);

	CheckOut();

}

void GameScene::Render()
{
	ZeroIScene::Render();
	background->Render();
	ship->Render();

	for (auto pB : PbulletList) {
		pB->Render();
	}
	for (auto eB : EbulletList) {
		eB->Render();
	}

	for (auto e : enemyList) {
		e->Render();
	}
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
	for (auto e : enemyList) {
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
}

void GameScene::SpawnEnemy(float eTime)
{
	EspawnTimer.first += eTime;

	if (EspawnTimer.first >= EspawnTimer.second) {
		Enemy* e = new Enemy();

		enemyList.push_back(e);
		PushScene(e);

		e->SetPos(Random(0, 700 - e->Width()), 0);

		EspawnTimer.first = 0;

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
