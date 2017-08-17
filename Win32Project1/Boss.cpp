#include "stdafx.h"
#include "Boss.h"


Boss::Boss()
{
	boss = new ZeroSprite("Resource/Enemy/enemy_02.png");
	PushScene(boss);

	SetPos(100, 0);
}

void Boss::Update(float eTime)
{
	boss->Update(eTime);

	Move(eTime);
}

void Boss::Render()
{	
	boss->Render();
}

void Boss::Move(float eTime)
{
	AddPosY(50 * eTime);
}