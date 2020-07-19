#include "Board.h"
#include"Game.h"
#include"Define.h"


CBoard* CBoard::__instance = NULL;
CBoard* CBoard::GetInstance()
{
	if (__instance == NULL) __instance = new CBoard();
	return __instance;
}

void CBoard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isStop)
	{
		return;
	}
	if (GetTickCount() - _count >= 1000)
	{
		_time--;
		_count = GetTickCount();
	}
}

void CBoard::Render()
{
	CGame* game = CGame::GetInstance();
	CSimon* simon = CSimon::GetInstance();

	float cx, cy;
	game->GetCamPos(cx, cy);
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(50000)->Draw(cx-1, cy); //background

	code->DrawNumber(4, cx + 295, cy + 12, _time);
	code->DrawNumber(2, cx + 400, cy + 32, simon->GetHeart());
	code->DrawNumber(6, cx + 110, cy + 12, simon->GetScore());
	code->DrawNumber(2, cx + 400, cy + 52, simon->GetLive());
	code->DrawNumber(2, cx + 465, cy + 12, game->GetIDCurrentScene());

	code->DrawBloodBar(cx + 110, cy + 30, 0, simon->GetBlood());

	if (simon->GetWeapon() != -1)
	{
		if (simon->GetWeapon() == eType::WEAPON_AXE)
		{
			sprites->Get(12030)->Draw(cx + 310, cy + 30);
		}
		else if (simon->GetWeapon() == eType::WEAPON_BOOMERANG)
		{ 
			sprites->Get(13016)->Draw(cx + 310, cy + 27);
		}
		else if (simon->GetWeapon() == eType::WEAPON_HOLLYWATER)
		{
			sprites->Get(13013)->Draw(cx + 310, cy + 27);
		}
		else if (simon->GetWeapon() == eType::WEAPON_KNIFE)
		{ 
			sprites->Get(13001)->Draw(cx + 310, cy + 40);;
		}
	}
	game = NULL;
	sprites = NULL;
	simon = NULL;
}

void CBoard::ChangeWeapon()
{
	CSimon* simon = CSimon::GetInstance();

	switch (simon->GetWeapon())
	{
	case 0:
		simon->SetWeapon(eType::WEAPON_KNIFE);
		break;
	case eType::WEAPON_KNIFE:
		simon->SetWeapon(eType::WEAPON_AXE);
		break;
	case eType::WEAPON_AXE:
		simon->SetWeapon(eType::WEAPON_HOLLYWATER);
		break;
	case eType::WEAPON_HOLLYWATER:
		simon->SetWeapon(eType::WEAPON_BOOMERANG);
		break;
	case eType::WEAPON_BOOMERANG:
		simon->SetWeapon(eType::WEAPON_KNIFE);
		break;
	default:
		break;
	}
	simon = NULL;
}


