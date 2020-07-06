#include "HunchBack.h"

void CHunchBack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	float cam_x, cam_y;
	game->GetCamPos(cam_x, cam_y);

	if (this->x > cam_x + SCREEN_WIDTH || this->x < cam_x - ENEMY_HUNCHBACK_WIDTH || state == STATE_ENEMY_HUNCHBACK_NOT_EXIST)
	{
		this->blood = 0;
	}
	if (this->blood > 0)
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
					state = STATE_ENEMY_HUNCHBACK_ITEM_EXIST;
				if (state == STATE_ENEMY_HUNCHBACK_ITEM_EXIST)
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

	} 
}

void CHunchBack::Render()
{
	if (blood > 1 && animations.size() > 0)
	{
		animations[0]->RenderTrend(x, y, nx);
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
	if (state == STATE_ENEMY_HUNCHBACK_ITEM_EXIST)
	{
		if (item != NULL)
		{
			item->Render();
		}
	}
}

void CHunchBack::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (this->blood > 0)
	{
		left = x;
		top = y;
		right = x + ENEMY_HUNCHBACK_WIDTH;
		bottom = y + ENEMY_HUNCHBACK_HEIGHT;
	}
}
