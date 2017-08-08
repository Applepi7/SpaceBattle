#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"


class Enemy :
	public ZeroIScene
{


private:
	float speed;
	pair<float, float> movingTimer;
	
	void Moving(float eTime);

public:
	Enemy(int eTYPE);
	~Enemy();

	bool isEAlive;

	int eTYPE;

	void Update(float eTime) override;
	void Render() override;

	/* enum TYPE {
		BLACK,
		RED,
		GREY
	}; */

	ZeroSprite* enemy;

};

