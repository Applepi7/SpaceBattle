#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"

#include "PlayerCharacter.h"
#include "Enemy.h"
#include "Bullet.h"

#include <list>

using namespace std;

class GameScene :
	public ZeroIScene
{
private:
	ZeroSprite* background;

	PlayerCharacter* p;
	Enemy* e;
	list<Bullet*> PbulletList;
	list<Bullet*> EbulletList;


	pair<float, float> playerShootingT;
	pair<float, float> enemyShootingT;
	

	bool isShooting;

	void Update(float eTime) override;
	void Render() override;

	void PlayerShooting(float eTime);
	void EnemyShooting(float eTime);
	void CheckOut();

public:
	GameScene();
	~GameScene();
};

