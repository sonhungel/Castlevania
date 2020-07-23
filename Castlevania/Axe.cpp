#include "Axe.h"
#include"Torch.h"
#include"Brick.h"
#include"Game.h"
#include"Define.h"
#include"Candle.h"
#include"BreakBrick.h"
#include"Brick.h"
#include"Enemy.h"


CAxe::CAxe(float simon_x, float simon_y, int simon_trend)
{
	if (simon_trend < 0)
	{
		this->x = simon_x;
	}
	else {
		this->x = simon_x + 25;
	}

	this->y = simon_y + 5;

	nx = simon_trend;

	vx = nx * AXE_SPEED_X;
	vy = -AXE_SPEED_Y;

	this->blood = 1;

	type = eType::WEAPON_AXE;
	AddAnimation(AXE_ANI_ID);
}

void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->y > SCREEN_WIDTH)
	{
		blood = 0;
	}

	if (blood>0)
	{
		CGameObject::Update(dt);

		x += vx * dt;
		vy += GRAVITY * dt;
		y += vy * dt;

		CollisionWithObject(dt, *coObjects);

	}
}


void CAxe::Render()
{
	if (animations.size()>0)
	{
		animations[0]->RenderTrend(x, y, nx);
	}
	RenderBoundingBox();
}

void CAxe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (blood > 0)
	{
		left = x;
		right = x + AXE_WIDTH;
		top = y;
		bottom = y + AXE_HEIGHT;
	}
	else
		left = top = right = bottom = 0;
}

void CAxe::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	//if (state==STATE_SUBWEAPON_HIDE)
	//	return;
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
					vx = vy = 0;
					torch->SetState(STATE_TORCH_NOT_EXIST);
					//this->state = STATE_SUBWEAPON_HIDE;
					this->blood = 0;
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
					vx = vy = 0;
					//this->state = STATE_SUBWEAPON_HIDE;
					this->blood = 0;
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
					// bên trong enemey sẽ tự bộng từ blood qua cờ isStrock 
					this->blood = 0;
				}

			}
		}
		/*
		if (dynamic_cast<CBreakBrick*>(listObj.at(i)))
		{
			if ((listObj.at(i))->GetState() == STATE_BREAK_BRICK_EXIST)
			{
				CBreakBrick* brick = dynamic_cast<CBreakBrick*>(listObj.at(i));
				brick->GetBoundingBox(l2, t2, r2, b2);
				rect2.left = (int)l2;
				rect2.top = (int)t2;
				rect2.right = (int)r2;
				rect2.bottom = (int)b2;
				if (CGame::GetInstance()->isCollision(rect1, rect2)) // => có đụng độ
				{
					brick->SetState(STATE_BREAK_BRICK_ITEM_EXIST);
					this->blood = 0;
				}
			}
		}*/
	}
}


