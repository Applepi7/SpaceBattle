#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroAnimation.h"

#include "Bullet.h"

class Boss :
	public ZeroIScene
{
private:
	int speed;

	bool isShooting;
	bool isLaser;
	bool isCircle;

	void Move(float eTime);
	void Attack(float eTime);

	void Shooting(float eTime);
	void Laser(float eTime);
	void Circle(float eTime);

	void CheckOut();

	pair<float, float> movingTimer;
	pair<float, float> attackTimer;

	pair<float, float> shootingTimer;
	pair<float, float> ATimer;

public:
	Boss();

	int health;

	ZeroSprite* boss;
	ZeroAnimation* explosion;

	list<Bullet*> bulletList;

	bool isAlive;

	void Update(float eTime) override;
	void Render() override;

	void Death();
};

