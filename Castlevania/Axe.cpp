#include "Axe.h"
#include"Torch.h"
#include"Brick.h"
#include"Game.h"
#include"Define.h"
#include"Candle.h"

CAxe* CAxe::__instance = NULL;

CAxe* CAxe::GetInstance()
{
	if (__instance == NULL)
		__instance = new CAxe();
	return __instance;
}

CAxe::CAxe()
{
	type = eType::WEAPON_AXE;
	AddAnimation(AXE_ANI_ID);
	state = STATE_AXE_HIDE;
	start_attack = 0;
}

void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->state == STATE_AXE_APPEAR)
	{
		CGameObject::Update(dt);
		if (start_attack == 0)
			start_attack = GetTickCount();

		x += vx * dt;
		vy += GRAVITY * dt;
		y += vy * dt;

		CollisionWithObject(dt, *coObjects);

		if (GetTickCount() - start_attack > AXE_TIME)
		{
			state = STATE_AXE_HIDE;
			start_attack = 0;
			animations[0]->ResetFrame();
		}
	}
}

void CAxe::SetPosition(float simon_x, float simon_y)
{
	if (nx < 0)
	{
		this->x = simon_x ;
	}
	else {
		this->x = simon_x + 10;
	}

	this->y = simon_y;
}

void CAxe::Render()
{
	if (state == STATE_AXE_APPEAR)
	{
		animations[0]->RenderTrend(x, y, nx);

		RenderBoundingBox();
	}
}

void CAxe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_AXE_APPEAR)
	{
		left = x;
		right = x + AXE_WIDTH;
		top = y;
		bottom = y + AXE_HEIGHT;
	}
}

void CAxe::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	if (state==STATE_AXE_HIDE)
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
					vx = vy = 0;
					torch->SetState(STATE_TORCH_NOT_EXIST);
					this->state = STATE_AXE_HIDE;
					start_attack = 0;
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
					this->state = STATE_AXE_HIDE;
					start_attack = 0;
				}
			}
		}
	}
}

void CAxe::SetState(int st)
{
	this->state = st;
	if (st == STATE_AXE_APPEAR)
	{
		vx = nx * AXE_SPEED_X;
		vy = -AXE_SPEED_Y;
	}
}
