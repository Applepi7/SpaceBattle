#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroFont.h"
#include "ZeroAnimation.h"

#include "PlayerCharacter.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Item.h"

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

enum ITEM {
	HEALPACK,
	SPEEDUP
};

private:
	ZeroSprite* background1;
	ZeroSprite* background2;

	ZeroSprite* HBForeground;
	ZeroSprite* HBFill;

	ZeroSprite* gameover;

	ZeroAnimation* explosion;

	ZeroFont* scoreText;
	ZeroFont* distanceText;
	ZeroFont* finalscoreText;
	ZeroFont* finaldistanceText;
	ZeroFont* restartText;

	PlayerCharacter* p;
	list<Enemy*> enemyList;

	list<Bullet*> PbulletList;
	list<Bullet*> E1bulletList;
	list<Bullet*> E2bulletList;
	list<Bullet*> E3bulletList;

	list<Item*> itemList;

	pair<float, float> playerShootingT;
	pair<float, float> enemyShootingT;
	pair<float, float> EspawnTimer;
	pair<float, float> IspawnTimer;
	pair<float, float> speedUpT;

	bool isDistanceRender;
	bool isSpeedUp;

	int distance;
	int score;

	int randomINT;

	void Update(float eTime) override;
	void Render() override;

	void UpdateBulletLists(float eTime);
	void RenderBulletLists();

	void PlayerShooting(float eTime);
	void EnemyShooting(float eTime); 
	void SpawnEnemy(float eTime);
	void SpawnItem(float eTime);
	void EnemyDeath();
	void PlayerDamaged();
	void PlayerDead();
	void Explosion(Enemy* e);
	void Explosion(PlayerCharacter* p);
	void Scoring(Enemy* e);
	void SelfHeal();
	void AutoScoring();
	void BulletSpeedUp(float eTime);
	void EatItem();
	void SetResultText();
	void CheckOut();
	void MovingBackground(float eTime);
	void ShowDistance();
	void Restart();

public:
	GameScene();
};

