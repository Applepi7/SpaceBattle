#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"


class Boss :
	public ZeroIScene
{
private:
	void Move(float eTime);

public:
	Boss();

	void Update(float eTime) override;
	void Render() override;

	ZeroSprite* boss;
};

