#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroFont.h"
#include "ZeroAnimation.h"

#include "PlayerCharacter.h"
#include "Enemy.h"
#include "Bullet.h"

#include <list>

using namespace std;

class GameScene :
	public ZeroIScene
{

enum ENEMY {
	BLACK,
	RED,
	GREY
};

private:
	ZeroSprite* background1;
	ZeroSprite* background2;

	ZeroAnimation* explosion;

	ZeroFont* scoreText;
	ZeroFont* distanceText;

	PlayerCharacter* p;
	list<Enemy*> enemyList;

	list<Bullet*> PbulletList;
	list<Bullet*> E1bulletList;
	list<Bullet*> E2bulletList;
	list<Bullet*> E3bulletList;


	pair<float, float> playerShootingT;
	pair<float, float> enemyShootingT;
	pair<float, float> EspawnTimer;
	

	bool isShooting;
	bool isPAlive;
	bool isDistanceRender;

	int meter;
	int score;

	float randomINT;

	void Update(float eTime) override;
	void Render() override;

	void UpdateBulletLists(float eTime);
	void RenderBulletLists();

	void PlayerShooting(float eTime);
	void EnemyShooting(float eTime);
	void SpawnEnemy(float eTime);
	void EnemyDeath();
	void PlayerDamaged();
	void Explosion(Enemy* e);
	void CheckOut();
	void MovingBackground(float eTime);
	void ShowDistance();

public:
	GameScene();
	~GameScene();
};

