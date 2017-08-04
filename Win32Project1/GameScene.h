#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"

#include "PlayerCharacter.h"


class GameScene :
	public ZeroIScene
{
private:
	ZeroSprite* background;

	PlayerCharacter* p;


	void Update(float eTime) override;
	void Render() override;

public:
	GameScene();
	~GameScene();
};

