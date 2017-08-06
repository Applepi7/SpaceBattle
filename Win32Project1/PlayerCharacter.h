#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"



class PlayerCharacter :
	public ZeroIScene
{
private:
	void Input(float eTime);


public:
	PlayerCharacter();
	~PlayerCharacter();

	ZeroSprite* player;

	void Update(float eTime) override;
	void Render() override;

};

