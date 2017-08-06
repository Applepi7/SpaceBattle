#include "stdafx.h"
#include "Enemy.h"




Enemy::Enemy() : speed(150), movingTimer(0.0f, 1.0f)
{
	enemy = new ZeroSprite("Resource/Enemy/enemy_01.png");
	PushScene(enemy);
}


Enemy::~Enemy()
{
}

void Enemy::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	enemy->Update(eTime);

	Moving(eTime);
}

void Enemy::Render()
{
	ZeroIScene::Render();
	enemy->Render();
}

void Enemy::Moving(float eTime)
{
	movingTimer.first += eTime;

	AddPosY(75 * eTime);

	if (movingTimer.first >= movingTimer.second) {
		speed *= -1;
		movingTimer.first = 0;
	}

	AddPosX(speed * eTime);
}