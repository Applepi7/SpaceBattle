#include "stdafx.h"
#include "PlayerCharacter.h"

#include "ZeroInputManager.h"


PlayerCharacter::PlayerCharacter()
{
	player = new ZeroSprite("Resource/Player/Spaceship.png");
	SetPos(300, 600);

	PushScene(player);
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
	if (ZeroInputMgr->GetKey(VK_UP) == INPUTMGR_KEYON) {
		AddPosY(-150 * eTime);
	}
	if (ZeroInputMgr->GetKey(VK_LEFT) == INPUTMGR_KEYON) {
		AddPosX(-150 * eTime);
	}
	if (ZeroInputMgr->GetKey(VK_DOWN) == INPUTMGR_KEYON) {
		AddPosY(150 * eTime);
	}
	if (ZeroInputMgr->GetKey(VK_RIGHT) == INPUTMGR_KEYON) {
		AddPosX(150 * eTime);
	}
}
