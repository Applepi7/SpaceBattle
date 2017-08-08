#include "stdafx.h"
#include "GameScene.h"

#include "ZeroSoundManager.h"

#include "Global.h"



GameScene::GameScene() : playerShootingT(0.f, 0.5f), enemyShootingT(0.f, 0.5f), EspawnTimer(0.0f, 1.0f),isShooting(true), isPAlive(true), meter(0)
{
	p = new PlayerCharacter();
	
	background1 = new ZeroSprite("Resource/Background/space.png");
	background2 = new ZeroSprite("Resource/Background/space.png");

	explosion = new ZeroAnimation(5.0f);
	explosion->PushSprite("Resource/Explosion/explosion_8.png");
	explosion->SetLooping(false);
	PushScene(explosion);

	distanceText = new ZeroFont(40, "");

	background2->SetPos(background1->Pos().x, background1->Pos().y + background1->Height());
	distanceText->SetPos(500, 50);

	PushScene(p);

	ZeroSoundMgr->PushSound("Resource/Sound/pShooting.wav", "pShootingSound");
	ZeroSoundMgr->PushSound("Resource/Sound/Explosion.wav", "explosionSound");
}


GameScene::~GameScene()
{
}


void GameScene::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	background1->Update(eTime);
	background2->Update(eTime);

	distanceText->Update(eTime);

	distanceText->SetString(to_string(meter) + "m");

	UpdateBulletLists(eTime);

	for (auto e : enemyList) {
		e->Update(eTime);
	}
	p->Update(eTime);


	playerShootingT.first += eTime;
	
	if (isPAlive) {
		meter += eTime;

		MovingBackground(eTime);
		PlayerShooting(eTime);
		SpawnEnemy(eTime);
		PlayerDamaged();
	}

	EnemyShooting(eTime);

	EnemyDeath();
	CheckOut();

	explosion->Update(eTime);
}

void GameScene::Render()
{
	ZeroIScene::Render();

	background1->Render();
	background2->Render();

	distanceText->Render();

	RenderBulletLists();

	for (auto e : enemyList) {
		e->Render();
	}
	p->Render();

	explosion->Render();
}

void GameScene::UpdateBulletLists(float eTime)
{
	for (auto b : PbulletList) {
		b->Update(eTime);
	}
	for (auto e1B : E1bulletList) {
		e1B->Update(eTime);
	}
	for (auto e2B : E2bulletList) {
		e2B->Update(eTime);
	}
	for (auto e3B : E3bulletList) {
		e3B->Update(eTime);
	}
}

void GameScene::RenderBulletLists()
{
	for (auto pB : PbulletList) {
		pB->Render();
	}
	for (auto eB : E1bulletList) {
		eB->Render();
	}
	for (auto eB : E2bulletList) {
		eB->Render();
	}
	for (auto eB : E3bulletList) {
		eB->Render();
	}
}

void GameScene::PlayerShooting(float eTime)
{
	if (isPAlive) {
		playerShootingT.first += eTime;

		if (playerShootingT.first >= playerShootingT.second) {
			Bullet* b = new Bullet(0);

			b->bullet1->SetPos(p->Pos().x, p->Pos().y + 10);
			b->bullet2->SetPos(p->Pos().x + 80, p->Pos().y + 10);

			ZeroSoundMgr->Play("pShootingSound");

			PbulletList.push_back(b);
			PushScene(b);

			playerShootingT.first = 0;
		}
	}
}

void GameScene::EnemyShooting(float eTime)
{
	for (auto e : enemyList) {
		enemyShootingT.first += eTime;

		if (enemyShootingT.first >= enemyShootingT.second) {

			Bullet* b;

			if (e->eTYPE == BLACK) {
				b = new Bullet(1);
				b->bullet1->SetPos(e->Pos().x, e->Pos().y + e->enemy->Height());
				b->bullet2->SetPos(e->Pos().x + e->enemy->Width(), e->Pos().y + e->enemy->Height());
				E1bulletList.push_back(b);
				PushScene(b);
			}
			if (e->eTYPE == RED) {
				b = new Bullet(2);
				b->bullet1->SetPos(e->Pos().x, e->Pos().y + e->enemy->Height() - 20);
				b->bullet2->SetPos(e->Pos().x + (0.5f * e->enemy->Width()), e->Pos().y + e->enemy->Height() + 30);
				b->bullet3->SetPos(e->Pos().x + e->enemy->Width(), e->Pos().y + e->enemy->Height() - 20);
				E2bulletList.push_back(b);
				PushScene(b);
			}
			if (e->eTYPE == GREY) {
				b = new Bullet(3);
				b->bullet1->SetPos(e->Pos().x + (0.5f * e->enemy->Width()), e->Pos().y + e->enemy->Height());
				E3bulletList.push_back(b);
				PushScene(b);
			}

			enemyShootingT.first = 0;
		}
	}
}

void GameScene::SpawnEnemy(float eTime)
{
	EspawnTimer.first += eTime;

	if (EspawnTimer.first >= EspawnTimer.second) {

		Enemy* e;

		randomINT = Random(1, 100);

		if (randomINT <= 5) {	// 50%
			e = new Enemy(0);
		}
		else if (randomINT > 5 && randomINT <= 88) {		// 30%
			e = new Enemy(1);
		}
		else {		// 20%
			e = new Enemy(2);
		}

		enemyList.push_back(e);
		PushScene(e);

		e->SetPos(Random(0, 700 - e->Width()), 0);
		
		EspawnTimer.first = 0;

	}
}

void GameScene::EnemyDeath()
{
	for (auto e = enemyList.begin(); e != enemyList.end();) {
		for (auto b = PbulletList.begin(); b != PbulletList.end();) {
			if ((*e)->enemy->IsOverlapped((*b)->bullet1) || (*e)->enemy->IsOverlapped((*b)->bullet2)) {

				(*e)->isEAlive = false;

				Explosion(*e);

				PopScene(*e);
				PopScene(*b);

				ZeroSoundMgr->Play("explosionSound");

				enemyList.erase(e++);
				PbulletList.erase(b++);
				if (b == PbulletList.end()) break;
				if (e == enemyList.end()) break;
			}
			else {
				b++;
				if (b == PbulletList.end()) break;
			}
		}
		e++;
		if (e == enemyList.end()) break;
	}
}

void GameScene::PlayerDamaged()
{
	for (auto e1B = E1bulletList.begin(); e1B != E1bulletList.end();) {
		if (p->player->IsOverlapped((*e1B)->bullet1) || p->player->IsOverlapped((*e1B)->bullet2)) {
			PopScene(p);
			PopScene(*e1B);
			E1bulletList.erase(e1B++);

			isPAlive = false;
		}
		else e1B++;
	}
	for (auto e2B = E2bulletList.begin(); e2B != E2bulletList.end();) {
		if (p->player->IsOverlapped((*e2B)->bullet1) || p->player->IsOverlapped((*e2B)->bullet2 || p->player->IsOverlapped((*e2B)->bullet3))) {
			PopScene(p);
			PopScene(*e2B);
			E2bulletList.erase(e2B++);

			isPAlive = false;
		}
		else e2B++;
	}
	for (auto e3B = E3bulletList.begin(); e3B != E3bulletList.end();) {
		if (p->player->IsOverlapped((*e3B)->bullet1)) {
			PopScene(p);
			PopScene(*e3B);
			E3bulletList.erase(e3B++);

			isPAlive = false;
		}
		else e3B++;
	}

}

void GameScene::Explosion(Enemy* e)
{
	explosion = new ZeroAnimation(5.0f);
	for (int i = 1; i <= 8; i++) {
		explosion->PushSprite("Resource/Explosion/explosion_%d.png", i);
	}
	explosion->SetLooping(false);
	PushScene(explosion);

	explosion->SetPos(e->Pos().x, e->Pos().y);
}


void GameScene::CheckOut()
{
	for (auto pb = PbulletList.begin(); pb != PbulletList.end();) {

		if ((*pb)->Pos().y < 0) {
			PopScene(*pb);
			PbulletList.erase(pb++);
		}
		else pb++;
	}
}

void GameScene::MovingBackground(float eTime)
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

void GameScene::Distance()
{
}
