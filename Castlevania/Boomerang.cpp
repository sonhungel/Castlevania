#include "Boomerang.h"
#include"Torch.h"
#include"Game.h"
#include"Simon.h"
#include"Candle.h"
#include"BreakBrick.h"
#include"Brick.h"
#include"Enemy.h"

CBoomerang::CBoomerang(float simon_x, float simon_y, int simon_trend)
{
	if (simon_trend < 0)
	{
		this->x = simon_x;
	}
	else {
		this->x = simon_x + 20;
	}

	this->y = simon_y + 5;

	nx = simon_trend;
	vx = nx * BOOMERANG_SPEED;

	turn = 0;
	float temp;
	CGame::GetInstance()->GetCamPos(x_left, temp);

	x_right = x_left + SCREEN_WIDTH - 50;	// Căn chỉnh lại x right phù hợp 

	this->blood = 1;

	type = eType::WEAPON_BOOMERANG;
	AddAnimation(BOOMERANG_ANI_ID);

	start_attack = 0;
	turn = 0;

}

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float cam_x, cam_y;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	if (this->x <cam_x - BOOMERANG_WIDTH || this->x>cam_x + SCREEN_WIDTH)
	{
		blood = 0;
	}

	if (blood > 0)
	{

		CGameObject::Update(dt);
		if (start_attack == 0)
			start_attack = GetTickCount();

		x += vx * dt;

		vx -= BOOMERANG_SLOW_DOWN_X;

		if (GetTickCount() - start_attack > BOOMERANG_TIME)
		{
			blood = 0;
			vx = nx * BOOMERANG_SPEED;
			start_attack = 0;

			turn = 0;
		}
		if ((x < x_left && vx < 0) || (x > x_right && vx > 0))
		{
			nx = -nx;
			vx = nx * BOOMERANG_SPEED;
			turn++;
		}
		if (turn >= 2)
			blood = 0;
		if (turn < 2)
			CollisionWithObject(dt, *coObjects);
	}

}

void CBoomerang::Render()
{
	if (blood > 0 && turn < 2)
	{
		if (animations.size() > 0)
			animations[0]->RenderTrend(x, y, nx);
		//RenderBoundingBox();
	}
}

void CBoomerang::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (blood > 0)
	{
		left = x;
		top = y;
		right = x + BOOMERANG_WIDTH;
		bottom = y + BOOMERANG_HEIGHT;
	}
}

void CBoomerang::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
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
					this->blood = 0;
				}

			}
		}

	}
	if (turn > 0)
	{
		// Khi boomerang va chạm simon sẽ state=hide
		CSimon::GetInstance()->GetBoundingBox(l2, t2, r2, b2);
		rect2.left = (int)l2;
		rect2.top = (int)t2;
		rect2.right = (int)r2;
		rect2.bottom = (int)b2;
		if (CGame::GetInstance()->isCollision(rect1, rect2))
		{
			this->blood = 0;
			vx = vy = 0;
		}
	}
}