#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroSoundManager.h"

#include "Bullet.h"

#include <list>

using namespace std;

class PlayerCharacter :
	public ZeroIScene
{
private:
	pair<float, float> shootingTimer;
	pair<float, float> speedUpTimer;
	
	void Input(float eTime);
	void Shooting(float eTime);

public:
	PlayerCharacter();


	ZeroSprite* player;

	list<Bullet*> bulletList;

	int score;

	float health;

	bool isSpeedUp;
	bool isAlive;

	void BulletSpeedUp(float eTime);

	void Update(float eTime) override;
	void Render() override;
};

