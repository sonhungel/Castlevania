﻿#include "Knife.h"
#include"Game.h"
#include"Candle.h"


CKnife* CKnife::__instance = NULL;

CKnife* CKnife::GetInstance()
{
	if (__instance == NULL) __instance = new CKnife();
	return __instance;
}

void CKnife::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	if (state == STATE_SUBWEAPON_APPEAR)
	{
		CGameObject::Update(dt);
		if (start_attack == 0)
			start_attack = GetTickCount();
		if (nx > 0)
			this->x += dx;
		else
			this->x -= dx;
		CollisionWithObject(dt, *coObjects);
		if (GetTickCount() - start_attack > KNIFE_TIME)
		{
			state = STATE_SUBWEAPON_HIDE;
			start_attack = 0;
		}
	}
	
}

void CKnife::Render()
{
	if (state == STATE_SUBWEAPON_APPEAR)
	{
		animations[0]->RenderTrend(x, y, nx);
		DebugOut(L"Knife rendered\n");
		//RenderBoundingBox();
	}
}

void CKnife::SetPosition(float simon_x, float simon_y)
{
	if (nx < 0)
	{
		this->x = simon_x ;
	}
	else
	{
		this->x = simon_x +20;
	}
	this->y = simon_y+10;
}

void CKnife::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_SUBWEAPON_APPEAR)
	{
		left = x;
		top = y;
		right = x + KNIFE_WIDTH;
		bottom = y + KNIFE_HEIGHT;
	}
}

void CKnife::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	if (STATE_SUBWEAPON_HIDE)
		return;

	RECT rect1, rect2;

	float l1, t1, r1, b1;
	float l2, t2, r2, b2;
	// Get bounding box of knife
	GetBoundingBox(l1, t1, r1, b1);
	rect1.left = (int)l1;
	rect1.top = (int)t1;
	rect1.right = (int)r1;
	rect1.bottom = (int)b1;

	for (int i = 0; i < listObj.size(); i++)
	{
		if (dynamic_cast<CTorch*>(listObj.at(i)))
		{
			CTorch* torch = dynamic_cast<CTorch*>(listObj.at(i));
			if (listObj.at(i)->GetState() == STATE_TORCH_EXIST)
			{
				// get bounding box of the object that knife collision
				listObj.at(i)->GetBoundingBox(l2, t2, r2, b2); 
				rect2.left = (int)l2;
				rect2.top = (int)t2;
				rect2.right = (int)r2;
				rect2.bottom = (int)b2;
				if (CGame::GetInstance()->isCollision(rect1, rect2)) // => có đụng độ
				{
					torch->isStrock = true;
					torch->SetState(STATE_TORCH_NOT_EXIST);
					this->state = STATE_SUBWEAPON_HIDE;
				}
			}
		}
		if (dynamic_cast<CCandle*>(listObj.at(i)))
		{
			CCandle* candle = dynamic_cast<CCandle*>(listObj.at(i));
			if (candle->GetState() == STATE_CANDLE_EXIST)
			{
				candle->GetBoundingBox(l2, t2, r2, b2);
				rect2.left = (int)l2;
				rect2.top = (int)t2;
				rect2.right = (int)r2;
				rect2.bottom = (int)b2;
				if (CGame::GetInstance()->isCollision(rect1, rect2)) // => có đụng độ
				{
					candle->isStrock = true;
					candle->SetState(STATE_CANDLE_NOT_EXIST);
					this->state = STATE_SUBWEAPON_HIDE;
				}
			}
		}
	}
}
