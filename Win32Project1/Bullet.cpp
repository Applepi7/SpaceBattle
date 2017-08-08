#include "stdafx.h"
#include "Bullet.h"



Bullet::Bullet(int TYPE)
{
	switch (TYPE)
	{
	case 0:		// PLAYER
		bullet1 = new ZeroSprite("Resource/Bullet/playerB.png");
		bullet2 = new ZeroSprite("Resource/Bullet/playerB.png");
		this->TYPE = TYPE;
		bulletSpeed = -500;
		break;
	case 1:		// ENEMY_1
		bullet1 = new ZeroSprite("Resource/Bullet/enemy01B.png");
		bullet2 = new ZeroSprite("Resource/Bullet/enemy01B.png");
		bulletSpeed = 300;
		this->TYPE = TYPE;
		break;
	case 2:		// ENEMY_2
		bullet1 = new ZeroSprite("Resource/Bullet/enemy02B.png");
		bullet2 = new ZeroSprite("Resource/Bullet/enemy02B.png");
		bullet3 = new ZeroSprite("Resource/Bullet/enemy02B.png");
		bulletSpeed = 300;
		this->TYPE = TYPE;
		break;
	case 3:		// ENEMY_3
		bullet1 = new ZeroSprite("Resource/Bullet/enemy03B.png");
		bulletSpeed = 300;
		this->TYPE = TYPE;
		break;
	}
}


Bullet::~Bullet()
{
}

void Bullet::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	switch (TYPE)
	{
	case 0:
		bullet1->Update(eTime);
		bullet2->Update(eTime);
		break;	 
	case 1:		 
		bullet1->Update(eTime);
		bullet2->Update(eTime);
		break;	 
	case 2:		 
		bullet1->Update(eTime);
		bullet2->Update(eTime);
		bullet3->Update(eTime);
		break;	 
	case 3:		 
		bullet1->Update(eTime);
		break;
	}

	MoveY(eTime, TYPE);
}

void Bullet::Render()
{
	ZeroIScene::Render();
	switch (TYPE)
	{
	case 0:
		bullet1->Render();
		bullet2->Render();
		break;
	case 1:
		bullet1->Render();
		bullet2->Render();
		break;
	case 2:
		bullet1->Render();
		bullet2->Render();
		bullet3->Render();
		break;
	case 3:
		bullet1->Render();
		break;
	}
}

void Bullet::MoveY(float eTime, int TYPE)
{
	switch (TYPE)
	{
	case 0:
		bullet1->AddPosY(bulletSpeed * eTime);
		bullet2->AddPosY(bulletSpeed * eTime);
		break;
	case 1:
		bullet1->AddPosY(bulletSpeed * eTime);
		bullet2->AddPosY(bulletSpeed * eTime);
		break;
	case 2:
		bullet1->AddPosY(bulletSpeed * eTime);
		bullet2->AddPosY(bulletSpeed * eTime);
		bullet3->AddPosY(bulletSpeed * eTime);
		break;
	case 3:
		bullet1->AddPosY(bulletSpeed * eTime);
		break;
	}
}
