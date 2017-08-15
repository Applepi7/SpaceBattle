#include "stdafx.h"
#include "PlayerCharacter.h"

#include "ZeroInputManager.h"


PlayerCharacter::PlayerCharacter() : shootingTimer(0, 1), speedUpTimer(0, 5), health(100), isAlive(true), isSpeedUp(false)
{
	player = new ZeroSprite("Resource/Player/Spaceship.png");
	PushScene(player);

	SetPos(350 - (player->Width() * 0.5f), 600);
}

void PlayerCharacter::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	player->Update(eTime);

	for (auto b : bulletList) {
		b->Update(eTime);
	}

	Input(eTime);
	Shooting(eTime);
	BulletSpeedUp(eTime);
}

void PlayerCharacter::Render()
{
	ZeroIScene::Render();
	player->Render();

	for (auto b : bulletList) {
		b->Render();
	}
}

void PlayerCharacter::Input(float eTime)
{
	if (Pos().y > 0) {
		if (ZeroInputMgr->GetKey(VK_UP) == INPUTMGR_KEYON) {
			AddPosY(-150 * eTime);
		}
	}
	if (Pos().x > 0) {
		if (ZeroInputMgr->GetKey(VK_LEFT) == INPUTMGR_KEYON) {
			AddPosX(-150 * eTime);
		}
	}
	if (Pos().y < 950 - player->Height() - 100) {
		if (ZeroInputMgr->GetKey(VK_DOWN) == INPUTMGR_KEYON) {
			AddPosY(150 * eTime);
		}
	}
	if (Pos().x < 700 - player->Width()) {
		if (ZeroInputMgr->GetKey(VK_RIGHT) == INPUTMGR_KEYON) {
			AddPosX(150 * eTime);
		}
	}
}

void PlayerCharacter::Shooting(float eTime)
{

	shootingTimer.first += eTime;

	if (shootingTimer.first >= shootingTimer.second) {
		Bullet* b = new Bullet(0);

		b->bullet1->SetPos(Pos().x, Pos().y + 10);
		b->bullet2->SetPos(Pos().x + 80, Pos().y + 10);

		ZeroSoundMgr->Play("pShootingSound");

		bulletList.push_back(b);
		PushScene(b);

		shootingTimer.first = 0;
	}
}

void PlayerCharacter::BulletSpeedUp(float eTime)
{
	if (isSpeedUp) {
		speedUpTimer.first += eTime;
		if (speedUpTimer.first <= speedUpTimer.second)
			shootingTimer.second = 0.3f;
		else {
			shootingTimer.second = 1.0f;
			speedUpTimer.first = 0;
			isSpeedUp = false;
		}
	}
}
