#include "ItemMoney.h"
#include"Utils.h"

void CItemMoney::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (state == STATE_ITEM_EXSIST)
	{
		if (time_exsist==0)
			time_exsist = GetTickCount();
		else
		{
			if (GetTickCount() - time_exsist >= TIME_ITEM_EXSIST)
				state = STATE_ITEM_NOT_EXSIST;
		}
		if (isEated == true)
		{
			effect->SetPosition(this->x, this->y-20);
			if(dt_effection==0)
				dt_effection = GetTickCount();
		}
		if (dt_effection != 0)
		{
			if (GetTickCount() - dt_effection >= MONEY_EFFECT_TIME)
			{
				state = STATE_ITEM_NOT_EXSIST;
			}
		}
		CGameObject::Update(dt);

			// Simple fall down
		vy += GRAVITY_ITEM * dt;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		CalcPotentialCollisions(coObjects, coEvents);

			// No collision occured, proceed normally
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

				//// block 
				//x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y += min_ty * dy + ny * 0.8f;

			if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;
		}
			// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}

	//DebugOut(L"Vi tri item money : %d, %d\n", (int)this->x, (int)this->y);
}

void CItemMoney::Render()
{
	if (state == STATE_ITEM_EXSIST)
	{
		if (isEated==false)
		{
			animations[0]->Render(x, y);
		}
		else
		{
			effect->Render();
		}
	}
}

void CItemMoney::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	//if (state == STATE_ITEM_EXSIST && dt_effection == 0)
	//{
		left = x;
		right = x + ITEM_MONEY_WIDTH;
		top = y;
		bottom = y + ITEM_MONEY_HEIGHT;
	//}
}
