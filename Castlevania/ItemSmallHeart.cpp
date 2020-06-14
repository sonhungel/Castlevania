#include "ItemSmallHeart.h"
#include"Utils.h"

void CItemSmallHeart::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_ITEM_EXSIST)
	{
		left = x;
		top = y;
		right = x + SMALLHEART_WIDTH;
		bottom = y + SMALLHEART_HEIGHT;
	}
}

void CItemSmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (time_exsist == 0)
		time_exsist = GetTickCount();
	else
	{
		if (GetTickCount() - time_exsist >= TIME_ITEM_EXSIST)
			state = STATE_ITEM_NOT_EXSIST;
	}
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		vx = vy = 0;
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

	if (x <= x_left || x >= x_right)
	{
		vx = -vx;
	}
	DebugOut(L"Vi tri smallheart : %d, %d\n",(int)this->x,(int)this->y);
}
