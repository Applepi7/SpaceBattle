#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"

class Item : public ZeroIScene
{
private:
	float speed;
	
	pair<float, float> movingTimer;
	pair<float, float> destroyTimer;

public:
	Item(int iTYPE);

	int iTYPE;

	bool isDestroy;

	ZeroSprite* item;

	void Update(float eTime) override;
	void Render() override;

	void Moving(float eTime);
	void AutoDestroy(float eTime);
};

