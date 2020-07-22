#include "Zombie.h"
#include"Brick.h"

void CZombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
#pragma region Xu_Ly_Hieu_Ung&Item
	if (dt_die == 0)	// đo thời gian die
	{
		//if (this->state==STATE_ENEMY_BLACK_KNIGHT_NOT_EXIST)
		if (blood < 2)
		{
			dt_die = GetTickCount();
		}
	}
	else
	{
		if (item != NULL)		// => có item 
		{
			if (GetTickCount() - dt_die > TIME_EFFECT_DIE_ENEMY) // 100 is time default
			{
				delete effectDie;
				effectDie = NULL;
			}
			else
				state = STATE_ENEMY_ITEM_EXIST;
			if (state == STATE_ENEMY_ITEM_EXIST)
			{
				item->Update(dt, coObjects);
			}
		}
	}
	if (item->GetState() == STATE_ITEM_NOT_EXSIST)
		this->blood = 0;
	if (dt_strock == 0)			// đo thời gian effect
	{
		if (isStrock == true)
			dt_strock = GetTickCount();
	}
	else
	{
		if (isStrock == true)
		{
			if (GetTickCount() - dt_strock > TIME_EFFECT_HIT_ENEMY) // 100 is time default
			{
				isStrock = false;
				dt_strock = 0;
				blood--;
			}
		}
	}
#pragma endregion

#pragma region collision

	if (blood > 1)
	{
		vector<LPGAMEOBJECT> listBrick;

		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CBrick*>(coObjects->at(i)))
			{
				listBrick.push_back(coObjects->at(i));
			}
		}
		item->SetPosition(x, y);
		CGameObject::Update(dt);

		if (this->x >= X_LEFT_LIMIT)
		{
			nx = -1;
			vx = -ENEMY_ZOMBIE_SPEED;
		}
		this->vy += ENEMY_ZOMBIE_GRAVITY * dt;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		CalcPotentialCollisions(&listBrick, coEvents);

		if (coEvents.size() == 0)
		{
			y += dy;
			x += dx;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny = 0, rdx = 0, rdy = 0;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;		

			if (ny != 0)
				vy = 0;
			
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
		listBrick.clear();
	}
	//DebugOut(L"Vi tri ZOMBIE : %d, %d\n", (int)this->x, (int)this->y);
#pragma endregion
}

void CZombie::Render()
{
	if (blood > 1 && animations.size() > 0)
	{
		animations[0]->RenderTrend(x, y, nx);
		//DebugOut(L"Render black knight\n");
		RenderBoundingBox();
	}
	else if (effectDie != NULL)
	{
		effectDie->SetPosition(x, y);
		effectDie->Render();
	}
	if (isStrock == true)
	{
		effectHit->SetPosition(x, y);
		effectHit->Render();
	}
	if (state == STATE_ENEMY_ITEM_EXIST)
	{
		if (item != NULL)
		{
			item->Render();
		}
	}
}

void CZombie::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_ENEMY_EXIST)
	{
		left = x;
		top = y;
		right = x + ENEMY_ZOMBIE_WIDTH;
		bottom = y + ENEMY_ZOMBIE_HEIGHT;
	}
	else if (state == STATE_ENEMY_ITEM_EXIST)
	{
		item->GetPosition(x, y);
		item->GetBoundingBox(left, top, right, bottom);
	}
}
