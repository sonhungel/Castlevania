#include "Torch.h"

CTorch::CTorch(int id, int level) : CGameObject()
{
	dt_die = 0;
	state = TORCH_STATE_EXSIST;
	if (level == 0)
	{
		AddAnimation(501);
	}
	else
	{
		AddAnimation(502);
	}
	AddAnimation(800);

}

void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (dt_die == 0)
	{
		if (state == TORCH_STATE_NOT_EXSIST)
			dt_die = GetTickCount();
	}
}

void CTorch::Render()
{
	if (state == TORCH_STATE_EXSIST)
	{
		animations[0]->Render(x, y);
	}

}

void CTorch::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == TORCH_STATE_EXSIST)
	{
		left = x;
		top = y;
		right = x + TORCH_WIDTH;
		bottom = y + TORCH_HEIGHT;
	}
}
