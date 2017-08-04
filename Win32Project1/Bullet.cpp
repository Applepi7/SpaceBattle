#include "stdafx.h"
#include "Bullet.h"



Bullet::Bullet()
{
	bullet1 = new ZeroSprite("Resource/Bullet/missile.png");
	bullet2 = new ZeroSprite("Resource/Bullet/missile.png");
}


Bullet::~Bullet()
{
}


void Bullet::MoveY(float eTime)
{
	bullet1->AddPosY(-500 * eTime);
	bullet2->AddPosY(-500 * eTime);
}

void Bullet::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	bullet1->Update(eTime);
	bullet2->Update(eTime);

	MoveY(eTime);
}

void Bullet::Render()
{
	ZeroIScene::Render();
	bullet1->Render();
	bullet2->Render();
}
