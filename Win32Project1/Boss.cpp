#include "stdafx.h"
#include "Boss.h"

#include "Global.h"

Boss::Boss() : health(200), speed(5), isAlive(false), isShooting(false), isLaser(false), isCircle(false), movingTimer(0.f, 2.f), attackTimer(0.f, 3.f), shootingTimer(0.f, 0.7f), ATimer(0.f, 4.f)
{
	boss = new ZeroSprite("Resource/Enemy/boss.png");
	PushScene(boss);
	
	explosion = new ZeroAnimation(5.0f);
	explosion->PushSprite("Resource/Explosion/BossExplosion/explosion_15.png");
	PushScene(explosion);

	SetPos(100, -boss->Height());
}

void Boss::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	boss->Update(eTime);
	explosion->Update(eTime);

	Move(eTime);

	Attack(eTime);

	Shooting(eTime);
	Laser(eTime);
	Circle(eTime);

	CheckOut();

	for (auto b : bulletList) {
		b->Update(eTime);
	}
}

void Boss::Render()
{
	ZeroIScene::Render();

	for (auto b : bulletList) {
		b->Render();
	}

	boss->Render();
	explosion->Render();
}

void Boss::Death()
{
	for (int i = 1; i <= 14; i++) {
		explosion->PushSprite("Resource/Explosion/BossExplosion/explosion_%d.png");
	}
	explosion->SetPos(Pos().x, Pos().y);
}

void Boss::Move(float eTime)
{
	if (isAlive) {
		if (Pos().y <= -boss->Height() * 0.5f) {
			AddPosY(70 * eTime);
		}

		movingTimer.first += eTime;
		AddPosX(speed * eTime);
		if (movingTimer.first >= movingTimer.second) {
			speed *= -1;
			movingTimer.first = 0;
		}
	}
}

void Boss::Shooting(float eTime)
{
	if (isShooting) {
		attackTimer.first += eTime;
		shootingTimer.first += eTime;

		if (shootingTimer.first >= shootingTimer.second) {
			Bullet* b = new Bullet(4);
			bulletList.push_back(b);
			PushScene(b);

			int randomX = Random(200, 250);
			int randomY = Random(400, 500);

			b->bullet1->SetPos(Pos().x + randomX, Pos().y + randomY);
			b->bullet2->SetPos(Pos().x + randomX, Pos().y + randomY);
			b->bullet3->SetPos(Pos().x + randomX, Pos().y + randomY);
			b->bullet4->SetPos(Pos().x + randomX, Pos().y + randomY);
			b->bullet5->SetPos(Pos().x + randomX, Pos().y + randomY);

			b->bullet1->SetRot(25);
			b->bullet2->SetRot(10);
			b->bullet4->SetRot(-10);
			b->bullet5->SetRot(-25);

			shootingTimer.first = 0;
		}
		if (attackTimer.first >= attackTimer.second) {
			isShooting = false;
			speed = 5;
			attackTimer.first = 0;
		}
	}	
}

void Boss::Laser(float eTime)
{
	if (isLaser) {

	}
}

void Boss::Circle(float eTime)
{
	if (isCircle) {

	}
}

void Boss::CheckOut()
{
	for (auto b = bulletList.begin(); b != bulletList.end();) {
		if ((*b)->Pos().y > 950) {
			PopScene(*b);
			bulletList.erase(b++);
		}
		b++;
	}
}

void Boss::Attack(float eTime)
{
	if (isAlive) {
		ATimer.first += eTime;
		if (ATimer.first >= ATimer.second) {
			isShooting = true;
			/*switch (n)
			{
			case 0:
				isShooting = true;
				break;
			case 1:
				isLaser = true;
				break;
			case 2:
				isCircle = true;
				break;
			}*/
			ATimer.first = 0;
		}
	}
}

