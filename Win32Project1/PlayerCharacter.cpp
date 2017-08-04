#include "stdafx.h"
#include "PlayerCharacter.h"

#include "ZeroInputManager.h"


PlayerCharacter::PlayerCharacter()
{
	player = new ZeroSprite("Resource/Player/Spaceship.png");

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

	SetPos(300, 600);
}

void PlayerCharacter::Render()
{
	ZeroIScene::Render();
	player->Render();

}

void PlayerCharacter::Input(float eTime)
{
	if (ZeroInputMgr->GetKey(VK_UP) == INPUTMGR_KEYON) {
		player->AddPosY(-150 * eTime);
	}
	if (ZeroInputMgr->GetKey(VK_LEFT) == INPUTMGR_KEYON) {
		player->AddPosX(-150 * eTime);
	}
	if (ZeroInputMgr->GetKey(VK_DOWN) == INPUTMGR_KEYON) {
		player->AddPosY(150 * eTime);
	}
	if (ZeroInputMgr->GetKey(VK_RIGHT) == INPUTMGR_KEYON) {
		player->AddPosX(150 * eTime);
	}
}
