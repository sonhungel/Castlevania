#include "Knife.h"
#include"Game.h"
#include"Candle.h"
#include"BreakBrick.h"
#include"Brick.h"
#include"Enemy.h"
void CKnife::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float cam_x, cam_y;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	if (this->x <cam_x || this->x>(cam_x + SCREEN_WIDTH - KNIFE_WIDTH))
	{
		blood = 0;
	}

	if (blood > 0)
	{
		CGameObject::Update(dt);

		this->x += dx;
		CollisionWithObject(dt, *coObjects);

	}
	//DebugOut(L"Vi tri Knife :%f,%f\n", this->x, this->y);
}

void CKnife::Render()
{
	if (animations.size() > 0)
	{
		animations[0]->RenderTrend(x, y, nx);
	}
	//RenderBoundingBox();
}


void CKnife::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (blood > 0)
	{
		left = x;
		top = y;
		right = x + KNIFE_WIDTH;
		bottom = y + KNIFE_HEIGHT;
	}
	else
		left = top = right = bottom = 0;
}

void CKnife::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
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
	}
}