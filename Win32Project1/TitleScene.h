#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"

#include "ZeroFont.h"

class TitleScene :
	public ZeroIScene
{
private:

	ZeroSprite* title;
	ZeroSprite* background1;
	ZeroSprite* background2;

	ZeroFont* enterText;

	void MovingBackground(float eTime);

public:
	TitleScene();

	void Update(float eTime) override;
	void Render() override;
};

