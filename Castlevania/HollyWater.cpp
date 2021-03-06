﻿#include "HollyWater.h"
#include"Torch.h"
#include"Game.h"
#include"Brick.h"
#include"Candle.h"
#include"BreakBrick.h"
#include"Brick.h"
#include"Enemy.h"
CHollyWater::CHollyWater(float simon_x, float simon_y, int simon_trend)
{
	if (simon_trend < 0)
	{
		this->x = simon_x + 5;
	}
	else {
		this->x = simon_x + 25;
	}

	this->y = simon_y + 10;

	nx = simon_trend;

	vx = nx * HOLLYWATER_SPEED_X;
	vy = -HOLLYWATER_SPEED_Y;

	this->blood = 1;

	type = eType::WEAPON_HOLLYWATER;
	AddAnimation(HOLLYWATER_ANI_ID);

	start_attack = 0;

	effect = new CEffect(HOLLYWATER_EFFECT_ANI_ID, this->x, this->y);
	isBroke = false;
}

void CHollyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->y > SCREEN_HEIGHT)
	{
		blood = 0;
	}
	if (this->blood > 0)
	{
		effect->SetPosition(this->x, this->y);

		vector<LPGAMEOBJECT> listBrick;
		listBrick.clear();

		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CBrick*>(coObjects->at(i)))
			{
				CBrick* brick = dynamic_cast<CBrick*>(coObjects->at(i));
				listBrick.push_back(brick);
			}
		}

		CGameObject::Update(dt);



		if (isBroke == false)
		{
			x += vx * dt;
			vy += GRAVITY * dt;
		}
		else
		{
			//vy += GRAVITY * dt;
			vy = 0;
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
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			// block 
			y += min_ty * dy + ny * 0.5f;
			x += min_tx * dx + nx * 0.4f;

			isBroke = true;
			vx = 0;
			vy = 0;
			if (start_attack == 0)
				start_attack = GetTickCount();
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];

		CollisionWithObject(dt, *coObjects);

		if (start_attack > 0)
		{
			if (GetTickCount() - start_attack > HOLLYWATER_TIME)
			{
				start_attack = 0;
				blood = 0;
				isBroke = false;
			}
		}
	//	DebugOut(L"VY của HollyWater :%f\n", this->vy);
	}
}

void CHollyWater::Render()
{
	if (blood > 0)
	{
		if (isBroke == true)
		{
			effect->Render();
		}
		else if (animations.size() > 0)
		{
			animations[0]->RenderTrend(x, y, nx);
			//RenderBoundingBox();
		}
	}
}


void CHollyWater::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	RECT rect1, rect2;
	//vector<LPGAMEOBJECT> listBrick;
	//listBrick.clear();

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
					//this->state = STATE_SUBWEAPON_APPEAR;
					this->isBroke = true;
					if (start_attack == 0)
						start_attack = GetTickCount();

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
					//this->state = STATE_SUBWEAPON_APPEAR;
					this->isBroke = true;
					if (start_attack == 0)
						start_attack = GetTickCount();
				}
			}
		}
		if (dynamic_cast<CEnemy*>(listObj.at(i)))
		{

			if (listObj.at(i)->GetState() == STATE_ENEMY_EXIST)
			{
				CEnemy* enemy = dynamic_cast<CEnemy*>(listObj.at(i));
				enemy->GetBoundingBox(l2, t2, r2, b2);
				rect2.left = (int)l2;
				rect2.top = (int)t2;
				rect2.right = (int)r2;
				rect2.bottom = (int)b2;
				if (CGame::GetInstance()->isCollision(rect1, rect2)) // => có đụng độ
				{
					if (enemy->blood > 1)
						enemy->isStrock = true;
					if (start_attack == 0)
						start_attack = GetTickCount();
					//this->isBroke = true;
					// bên trong enemey sẽ tự bộng từ blood qua cờ isStrock 
				}

			}
		}

	}
}

void CHollyWater::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + HOLLYWATER_WIDTH;
	bottom = y + HOLLYWATER_HEIGHT;
}