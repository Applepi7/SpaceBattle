#include "stdafx.h"
#include "PlayerCharacter.h"

#include "ZeroInputManager.h"


PlayerCharacter::PlayerCharacter() : health(100)
{
	player = new ZeroSprite("Resource/Player/Spaceship.png");
	PushScene(player);

	SetPos(300, 600);

}


PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	player->Update(eTime);

	Input(eTime);

}

void PlayerCharacter::Render()
{
	ZeroIScene::Render();
	player->Render();

}

void PlayerCharacter::Input(float eTime)
{
	if (Pos().y > 0) {
		if (ZeroInputMgr->GetKey(VK_UP) == INPUTMGR_KEYON) {
			AddPosY(-150 * eTime);
		}
	}
	if (Pos().x > 0) {
		if (ZeroInputMgr->GetKey(VK_LEFT) == INPUTMGR_KEYON) {
			AddPosX(-150 * eTime);
		}
	}
	if (Pos().y < 950 - player->Height()) {
		if (ZeroInputMgr->GetKey(VK_DOWN) == INPUTMGR_KEYON) {
			AddPosY(150 * eTime);
		}
	}
	if (Pos().x < 700 - player->Width()) {
		if (ZeroInputMgr->GetKey(VK_RIGHT) == INPUTMGR_KEYON) {
			AddPosX(150 * eTime);
		}
	}
}
