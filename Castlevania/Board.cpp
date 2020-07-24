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
		if(_time>0)
			_time--;
		_count = GetTickCount();
	}
	if (timeItem > 0)
	{
		if (GetTickCount() - timeItem >= 10000)
		{
			number = 0;
			timeItem = 0;
		}
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

	if (this->boss == NULL)
	{
		code->DrawBloodBar(cx + 111, cy + 50, 1, MAX_BLOOD);
	}
	else
	{
		int bossBlood = boss->GetBlood() - 1;
		if (bossBlood <= 0)
			bossBlood = 0;
		code->DrawBloodBar(cx + 111, cy + 50, 1, bossBlood);
	}

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
			sprites->Get(13001)->Draw(cx + 310, cy + 40);
		}
		else if (simon->GetWeapon() == eType::WEAPON_CLOCK)
		{
			sprites->Get(13008)->Draw(cx + 310, cy + 29);
		}
	}

	if (number != 0)
	{
		if (number== 2)
		{
			sprites->Get(13012)->Draw(cx + 450, cy + 35);
		}
		else if (number == 3)
		{
			sprites->Get(13014)->Draw(cx + 450, cy + 35);
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
		simon->SetWeapon(eType::WEAPON_CLOCK);
		break;
	case eType::WEAPON_CLOCK:
		simon->SetWeapon(eType::WEAPON_KNIFE);
		break;
	default:
		break;
	}
	simon = NULL;
}


