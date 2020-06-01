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
	CSimon* simon = CSimon::GetInstance();
	float cx, cy;
	game->GetCamPos(cx, cy);
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(50000)->Draw(cx-1, cy);

	code->DrawNumber(4, cx + 295, cy + 12, _time);
	code->DrawNumber(2, cx + 400, cy + 32, simon->GetHeart());
	code->DrawNumber(6, cx + 110, cy + 12, simon->GetScore());
	code->DrawNumber(2, cx + 400, cy + 52, simon->GetLive());
	code->DrawNumber(2, cx + 465, cy + 12, game->GetIDCurrentScene());

	code->DrawBloodBar(cx + 110, cy + 30, 0, simon->GetBlood());

}


