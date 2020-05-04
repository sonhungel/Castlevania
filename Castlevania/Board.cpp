#include "Board.h"
#include"Game.h"


CBoard* CBoard::__instance = NULL;
CBoard* CBoard::GetInstance()
{
	if (__instance == NULL) __instance = new CBoard();
	return __instance;
}

void CBoard::Update(DWORD dt)
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
	float cx, cy;
	game->GetCamPos(cx, cy);
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(50000)->Draw(cx-1, cy);
}


