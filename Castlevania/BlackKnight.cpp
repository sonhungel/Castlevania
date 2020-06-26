﻿#include "BlackKnight.h"
#include"Utils.h"
#include"Brick.h"


void CBlackKnight::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (dt_die == 0)	// đo thời gian die
	{
		//if (this->state==STATE_ENEMY_BLACK_KNIGHT_NOT_EXIST)
		if(blood<2)
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
				state = STATE_ENEMY_BLACK_KNIGHT_ITEM_EXIST;
			if (state == STATE_ENEMY_BLACK_KNIGHT_ITEM_EXIST)
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
	
	

#pragma region collision
	if (blood>1)
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
		x += dx;
		this->vy += GRAVITY_ITEM * dt;

		if ((x < x_left && vx < 0) || (x > x_right && vx > 0))
		{
			nx = -nx;
			vx = nx * ENEMY_BLACK_KNIGHT_SPEED;
		}

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		CalcPotentialCollisions(&listBrick, coEvents);

		if (coEvents.size() == 0)
		{

			y += dy;
		}
		else
		{
			//float min_tx, min_ty, nx = 0, ny;
			//float rdx = 0;
			//float rdy = 0;

			//FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			// block 
			//x += dx;	// nx*0.4f : need to push out a bit to avoid overlapping next frame
			//y += min_ty * dy + ny * 0.4f;
		}
		
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
		listBrick.clear();
	}
#pragma endregion
	//DebugOut(L"Vi tri knight : %d, %d\n", (int)this->x, (int)this->y);

}

void CBlackKnight::Render()
{
	if (blood>1 && animations.size() > 0)
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
	if (state == STATE_ENEMY_BLACK_KNIGHT_ITEM_EXIST)
	{
		if (item != NULL)
		{
			item->Render();
		}
	}

}

void CBlackKnight::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (this->blood > 0)
	{
		left = x;
		top = y;
		right = x + ENEMY_BLACK_KNIGHT_WIDTH;
		bottom = y + ENEMY_BLACK_KNIGHT_HEIGHT;
	}
}
