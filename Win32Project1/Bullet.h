#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"


class Bullet :
	public ZeroIScene
{
private:
	void MoveY(float eTime);

public:
	Bullet();
	~Bullet();

	void Update(float eTime) override;
	void Render() override;

	ZeroSprite* bullet1;
	ZeroSprite* bullet2;
};

