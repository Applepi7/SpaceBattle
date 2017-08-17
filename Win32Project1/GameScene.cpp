#include "stdafx.h"
#include "GameScene.h"

#include "ZeroSoundManager.h"
#include "ZeroInputManager.h"
#include "ZeroSceneManager.h"

#include "Global.h"



GameScene::GameScene() : enemyShootingT(0.0f, 0.5f), EspawnTimer(0.0f, 3.0f), IspawnTimer(0.0f, 10.0f), isDistanceRender(false), distance(4500), score(0)
{
	p = new PlayerCharacter();
	b = new Boss();

	background1 = new ZeroSprite("Resource/Background/space.png");
	background2 = new ZeroSprite("Resource/Background/space.png");

	HBForeground = new ZeroSprite("Resource/HealthBar/Foreground.png");
	HBFill = new ZeroSprite("Resource/HealthBar/Fill.png");

	gameover = new ZeroSprite("Resource/Text/gameover.png");

	explosion = new ZeroAnimation(5.0f);
	explosion->PushSprite("Resource/Explosion/explosion_8.png");
	explosion->SetLooping(false);
	PushScene(explosion);

	scoreText = new ZeroFont(40, "");
	distanceText = new ZeroFont(80, "");

	finalscoreText = new ZeroFont(40, "");
	finaldistanceText = new ZeroFont(40, "");

	restartText = new ZeroFont(30, "");

	background2->SetPos(background1->Pos().x, background1->Pos().y + background1->Height());
	
	HBForeground->SetPosY(950 - HBForeground->Height());
	HBFill->SetPos(23, 883);
	scoreText->SetPos(480, 50);
	distanceText->SetPos(260, 200);

	finalscoreText->SetPos(250, 360 + gameover->Height());
	finaldistanceText->SetPos(250, finalscoreText->Pos().y + 50);

	restartText->SetPos(250, 800);

	gameover->SetPos(170, 350);

	PushScene(p);
	PushScene(b);

	ZeroSoundMgr->PushSound("Resource/Sound/bgm_1.wav", "bgm");
	ZeroSoundMgr->PushSound("Resource/Sound/pShooting.wav", "pShootingSound");
	ZeroSoundMgr->PushSound("Resource/Sound/Explosion.wav", "explosionSound");
	ZeroSoundMgr->PushSound("Resource/Sound/playerdamage.wav", "playerDamageSound");
	ZeroSoundMgr->PushSound("Resource/Sound/playerHeal.wav", "playerHealSound");
	ZeroSoundMgr->PushSound("Resource/Sound/playerSpeedUp.wav", "playerSpeedUpSound");

	ZeroSoundMgr->Play("bgm");
}

void GameScene::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	background1->Update(eTime);
	background2->Update(eTime);

	HBForeground->Update(eTime);
	HBFill->Update(eTime);

	finalscoreText->Update(eTime);
	finaldistanceText->Update(eTime);

	restartText->Update(eTime);

	UpdateBulletLists(eTime);

	for (auto i : itemList) {
		i->Update(eTime);
	}

	for (auto e : enemyList) {
		e->Update(eTime);
	}

	p->Update(eTime);
	b->Update(eTime);

	if (distance == 5000)
		SpawnBoss();

	if (p->isAlive) {
		distance += 1;

		distanceText->Update(eTime);
		explosion->Update(eTime);

		scoreText->SetString("SCORE : " + to_string(score));
		distanceText->SetString(to_string(distance / 500 * 500) + "km");

		MovingBackground(eTime);

		SelfHeal();
		EnemyShooting(eTime);
		SpawnEnemy(eTime);
		SpawnItem(eTime);
		PlayerDamaged();
		AutoScoring();
		ShowDistance();

		EatItem();
	}
	else {
		PopScene(distanceText);
		ZeroSoundMgr->PopSound("bgm");
		restartText->SetString("Press Enter To Restart");
	}

	for (auto item = itemList.begin(); item != itemList.end();) {
		if ((*item)->isDestroy) {
			itemList.erase(item++);
			PopScene(*item);
		}
		item++;
	}

	if (distance % 500 == 0) {
		if (EspawnTimer.second >= 1.5f) {
			EspawnTimer.second -= 0.5f;
		}
	}

	Restart();
	EnemyDeath();
	CheckOut();
}

void GameScene::Render()
{
	ZeroIScene::Render();

	background1->Render();
	background2->Render();

	explosion->Render();

	RenderBulletLists();

	for (auto i : itemList) {
		i->Render();
	}

	for (auto e : enemyList) {
		e->Render();
	}
	p->Render();
	b->Render();

	if (p->isAlive) {
		HBForeground->Render();
		HBFill->Render();

		scoreText->Render();
		if (isDistanceRender)
			distanceText->Render();
	}
	else {
		gameover->Render();
		finaldistanceText->Render();
		finalscoreText->Render();
		restartText->Render();
	}
}

void GameScene::UpdateBulletLists(float eTime)
{
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

		randomINT = Random(1, 10);

		if (randomINT <= 5) {	// 50%
			e = new Enemy(BLACK);
		}
		else if (randomINT > 5 && randomINT <= 8) {		// 30%
			e = new Enemy(RED);
		}
		else {		// 20%
			e = new Enemy(GREY);
		}

		enemyList.push_back(e);
		PushScene(e);

		e->SetPos(Random(e->Width(), 600 - e->Width()), 0);

		EspawnTimer.first = 0;
	}
}

void GameScene::SpawnItem(float eTime)
{
	IspawnTimer.first += eTime;

	if (IspawnTimer.first >= IspawnTimer.second) {

		Item* item;

		if (p->health <= 50)
			item = new Item(HEALPACK);
		else
			item = new Item(SPEEDUP);

		itemList.push_back(item);
		PushScene(item);

		item->SetPos(Random(200, 500), Random(300, 600));

		IspawnTimer.first = 0;
	}
}

void GameScene::SpawnBoss()
{
}

void GameScene::EnemyDeath()
{
	for (auto e = enemyList.begin(); e != enemyList.end();) {
		for (auto b = p->bulletList.begin(); b != p->bulletList.end();) {
			if ((*e)->enemy->IsOverlapped((*b)->bullet1) || (*e)->enemy->IsOverlapped((*b)->bullet2)) {

				(*e)->isEAlive = false;

				Explosion(*e);
				Scoring(*e);

				PopScene(*e);
				PopScene(*b);

				enemyList.erase(e++);
				p->bulletList.erase(b++);
				if (b == p->bulletList.end()) break;
				if (e == enemyList.end()) break;
			}
			else {
				b++;
				if (b == p->bulletList.end()) break;
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
			p->health -= 10;
			HBFill->AddScaleX(-0.1f);
			ZeroSoundMgr->Play("playerDamageSound");
			PopScene(*e1B);
			E1bulletList.erase(e1B++);
		}
		else e1B++;
	}
	for (auto e2B = E2bulletList.begin(); e2B != E2bulletList.end();) {
		if (p->player->IsOverlapped((*e2B)->bullet1) || p->player->IsOverlapped((*e2B)->bullet2 || p->player->IsOverlapped((*e2B)->bullet3))) {
			p->health -= 20;
			HBFill->AddScaleX(-0.2f);
			ZeroSoundMgr->Play("playerDamageSound");
			PopScene(*e2B);
			E2bulletList.erase(e2B++);
		}
		else e2B++;
	}
	for (auto e3B = E3bulletList.begin(); e3B != E3bulletList.end();) {
		if (p->player->IsOverlapped((*e3B)->bullet1)) {
			p->health -= 50;
			HBFill->AddScaleX(-0.5f);
			ZeroSoundMgr->Play("playerDamageSound");
			PopScene(*e3B);
			E3bulletList.erase(e3B++);
		}
		else e3B++;
	}


	if (p->health <= 0) PlayerDead();
}

void GameScene::PlayerDead()
{
	p->isAlive = false;

	Explosion(p);
	PopScene(p);
	SetResultText();
}

void GameScene::Explosion(Enemy* e)
{
	explosion = new ZeroAnimation(5.0f);
	for (int i = 1; i <= 8; i++) {
		explosion->PushSprite("Resource/Explosion/explosion_%d.png", i);
	}
	explosion->SetLooping(false);
	PushScene(explosion);

	ZeroSoundMgr->Play("explosionSound");

	explosion->SetPos(e->Pos().x, e->Pos().y);
}

void GameScene::Explosion(PlayerCharacter* p)
{
	explosion = new ZeroAnimation(5.0f);
	for (int i = 1; i <= 8; i++) {
		explosion->PushSprite("Resource/Explosion/explosion_%d.png", i);
	}
	explosion->SetLooping(false);
	PushScene(explosion);

	ZeroSoundMgr->Play("explosionSound");

	explosion->SetPos(p->Pos().x, p->Pos().y);
}

void GameScene::Scoring(Enemy* e)
{
	switch (e->eTYPE)
	{
	case BLACK:
		score += 50;
		break;
	case RED:
		score += 100;
		break;
	case GREY:
		score += 200;
		break;
	}
}

void GameScene::SelfHeal()
{
	if (p->health + 0.001f < 100) {
		p->health += 0.001f;
		HBFill->AddScaleX(0.0001f);
	}
}

void GameScene::AutoScoring()
{
	if (distance % 5 == 0) {
		score += 1;
	}
}	

void GameScene::EatItem()
{
	for (auto item = itemList.begin(); item != itemList.end();) {
		if (p->player->IsOverlapped((*item)->item)) {
			if ((*item)->iTYPE == HEALPACK) {
				p->health += 30;
				HBFill->AddScaleX(0.3f);
				ZeroSoundMgr->Play("playerHealSound");
			}
			else if ((*item)->iTYPE == SPEEDUP) {
				p->isSpeedUp = true;
				ZeroSoundMgr->Play("playerSpeedUpSound");
			}

			itemList.erase(item++);
			PopScene(*item);

			item++;
		}
		else item++;
	}
}

void GameScene::SetResultText()
{
	finalscoreText->SetString("Score : " + to_string(score));
	finaldistanceText->SetString("Distance : " + to_string(distance) + "km");
}

void GameScene::CheckOut()
{

	for (auto eB = E1bulletList.begin(); eB != E1bulletList.end();) {
		if ((*eB)->Pos().y > 950) {
			PopScene(*eB);
			E1bulletList.erase(eB++);
		}
		eB++;
	}

	for (auto eB = E2bulletList.begin(); eB != E2bulletList.end();) {
		if ((*eB)->Pos().y > 950) {
			PopScene(*eB);
			E2bulletList.erase(eB++);
		}
		eB++;
	}

	for (auto eB = E2bulletList.begin(); eB != E2bulletList.end();) {
		if ((*eB)->Pos().y > 950) {
			PopScene(*eB);
			E2bulletList.erase(eB++);
		}
		eB++;
	}

	for (auto e = enemyList.begin(); e != enemyList.end();) {
		if ((*e)->Pos().y > 950) {
			PopScene(*e);
			enemyList.erase(e++);
		}
		e++;
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

void GameScene::ShowDistance()
{
	int n = distance % 500;

	if (distance >= 100 && ((n >= 0 && n <= 30) || (n >= 60 && n <= 90)))
		isDistanceRender = true;
	else
		isDistanceRender = false;
}

void GameScene::Restart()
{
	if (!p->isAlive) {
		if (ZeroInputMgr->GetKey(VK_RETURN) == INPUTMGR_KEYON) {
			ZeroSceneMgr->ChangeScene(new GameScene());
		}
	}
}
