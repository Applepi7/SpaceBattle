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
	Enemy();
	~Enemy();

	void Update(float eTime) override;
	void Render() override;


	ZeroSprite* enemy;

};

