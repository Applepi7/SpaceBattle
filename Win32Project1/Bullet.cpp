#include "stdafx.h"
#include "Bullet.h"



Bullet::Bullet(int TYPE) : bulletSpeed(500)
{
	switch (TYPE)
	{
	case 0:		// PLAYER
		bullet1 = new ZeroSprite("Resource/Bullet/playerB.png");
		bullet2 = new ZeroSprite("Resource/Bullet/playerB.png");
		this->TYPE = TYPE;
		bulletSpeed *= -1;
		break;
	case 1:		// ENEMY_1
		bullet1 = new ZeroSprite("Resource/Bullet/enemyB.png");
		this->TYPE = TYPE;
		break;
	}
}


Bullet::~Bullet()
{
}


void Bullet::MoveY(float eTime, int TYPE)
{
	if (TYPE == 0) {
		bullet1->AddPosY(bulletSpeed * eTime);
		bullet2->AddPosY(bulletSpeed * eTime);
	}
	if (TYPE == 1) {
		bullet1->AddPosY(bulletSpeed * eTime);
	}
}

void Bullet::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	if (TYPE == 0) {
		bullet1->Update(eTime);
		bullet2->Update(eTime);
	}
	if (TYPE == 1) {
		bullet1->Update(eTime);
	}

	MoveY(eTime, TYPE);
}

void Bullet::Render()
{
	ZeroIScene::Render();
	if (TYPE == 0) {
		bullet1->Render();
		bullet2->Render();
	}
	if (TYPE == 1) {
		bullet1->Render();
	}
}


