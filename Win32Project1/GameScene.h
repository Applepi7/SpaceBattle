#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"

#include "PlayerCharacter.h"
#include "Bullet.h"

#include <list>

using namespace std;

class GameScene :
	public ZeroIScene
{
private:
	ZeroSprite* background;

	PlayerCharacter* p;
	list<Bullet*> bulletList;


	void Update(float eTime) override;
	void Render() override;

	void Shooting();
	// void CheckOut();

public:
	GameScene();
	~GameScene();
};

