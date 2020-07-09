#include "Bat.h"
#include"Utils.h"
#include"Game.h"

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	float x_simon, y_simon;
	float cam_x, cam_y;
	game->GetCamPos(cam_x, cam_y);

	target->GetPosition(x_simon, y_simon);
	if (CalculateDistance(D3DXVECTOR2(this->x, this->y), D3DXVECTOR2(target->x, target->y)) < DISTANCE_ACTIVE)
	{
		if (isActive == false)
			isActive = true;
	}
	if (this->x > cam_x + SCREEN_WIDTH|| this->x < cam_x - ENEMY_BAT_WIDTH || state==STATE_ENEMY_BAT_NOT_EXIST)
	{
		this->blood = 0;
	}
	if (isActive == true && this->blood > 0)
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
					state = STATE_ENEMY_BAT_ITEM_EXIST;
				if (state == STATE_ENEMY_BAT_ITEM_EXIST)
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
		
		CGameObject::Update(dt);
		
		if (this->y <= bottomLimit)
		{
			y += dx;
			vy = 0;
		}
		else
			this->vy += ENEMY_BAT_SPEED_Y * dt;
		x += dx;
		//DebugOut(L"Vi tri BAT : %d, %d\n", (int)this->x, (int)this->y);
		
	}
	game = NULL;
}

void CBat::Render()
{
	if (blood > 1 && animations.size() > 0)
	{
		if (isActive == false)
			animations[ENEMY_BAT_ANI_IDLE]->RenderTrend(x, y, nx);
		else
			animations[ENEMY_BAT_ANI_FLY]->RenderTrend(x, y, nx);
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
	if (state == STATE_ENEMY_BAT_ITEM_EXIST)
	{
		if (item != NULL)
		{
			item->Render();
		}
	}
}

void CBat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (this->blood > 0)
	{
		left = x;
		top = y;
		right = x + ENEMY_BAT_WIDTH;
		bottom = y + ENEMY_BAT_HEIGHT;
	}
}
