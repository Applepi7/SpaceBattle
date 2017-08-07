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
	ZeroSprite* background1;
	ZeroSprite* background2;

	PlayerCharacter* p;
	list<Enemy*> enemyList;

	list<Bullet*> PbulletList;
	list<Bullet*> E1bulletList;


	pair<float, float> playerShootingT;
	pair<float, float> enemyShootingT;
	pair<float, float> EspawnTimer;
	

	bool isShooting;
	bool isAlive;


	void Update(float eTime) override;
	void Render() override;

	void PlayerShooting(float eTime);
	void EnemyShooting(float eTime);
	void SpawnEnemy(float eTime);
	void EnemyDead();
	void AttackPlayer();
	void CheckOut();
	void MovingBackground(float eTime);

public:
	GameScene();
	~GameScene();
};

