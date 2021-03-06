#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"


class Bullet :
	public ZeroIScene
{

private:
	void MoveY(float eTime, int TYPE);

	int TYPE;
	float bulletSpeed;

public:
	Bullet(int TYPE);

	void Update(float eTime) override;
	void Render() override;


	ZeroSprite* bullet1;
	ZeroSprite* bullet2;
	ZeroSprite* bullet3;
	ZeroSprite* bullet4;
	ZeroSprite* bullet5;
};

