#include "stdafx.h"
#include "Item.h"

#include "PlayerCharacter.h"

#include "Global.h"


Item::Item(int iTYPE) : speed(5.0f), movingTimer(0.0f, 3.0f), destroyTimer(0.0f, 10.0f), isDestroy(false)
{
	if (iTYPE == 0) {
		item = new ZeroSprite("Resource/Item/healpack.png");
		PushScene(item);
		this->iTYPE = iTYPE;
	}
	else if (iTYPE == 1) {
		item = new ZeroSprite("Resource/Item/speedUp.png");
		PushScene(item);
		this->iTYPE = iTYPE;
	}
}

void Item::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	item->Update(eTime);

	Moving(eTime);
}

void Item::Render()
{
	ZeroIScene::Render();
	item->Render();
}

void Item::Moving(float eTime)
{
	AddPosY(speed * eTime);

	movingTimer.first += eTime;
	if (movingTimer.first >= movingTimer.second) {
		speed *= -1;

		movingTimer.first = 0;
	}
}

void Item::AutoDestroy(float eTime)
{
	destroyTimer.first += eTime;

	if (destroyTimer.first > destroyTimer.second) {
		isDestroy = true;
	}
}
