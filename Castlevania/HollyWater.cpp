#include "HollyWater.h"
#include"Torch.h"
#include"Game.h"
#include"Brick.h"
#include"Candle.h"

CHollyWater* CHollyWater::__instance = NULL;

CHollyWater* CHollyWater::GetInstance()
{
	if (__instance == NULL)
		__instance = new CHollyWater();
	return __instance;
}

CHollyWater::CHollyWater()
{
	type = eType::WEAPON_HOLLYWATER;
	AddAnimation(HOLLYWATER_ANI_ID);
	state = STATE_HOLLYWATER_HIDE;
	start_attack = 0;

	effect = new CEffect(HOLLYWATER_EFFECT_ANI_ID, this->x, this->y);
	isBroke = false;
}

void CHollyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == STATE_HOLLYWATER_APPEAR)
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

		if (start_attack == 0)
			start_attack = GetTickCount();

		if (isBroke == false)
		{
			x += vx * dt;
			vy += GRAVITY * dt;
			//y += vy * dt;
		}
		else
		{
			vy += GRAVITY * dt;
			//y += vy * dt;
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

			isBroke = true;
			vx = 0;
			vy = 0;
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];

		CollisionWithObject(dt, *coObjects);

		if (GetTickCount() - start_attack > HOLLYWATER_TIME)
		{
			state = STATE_HOLLYWATER_HIDE;
			start_attack = 0;

			isBroke = false;
		}
	}
}

void CHollyWater::Render()
{
	if (state == STATE_HOLLYWATER_APPEAR)
	{
		if (isBroke == true)
		{
			effect->Render();
		}
		else
		{
			animations[0]->RenderTrend(x, y, nx);
			RenderBoundingBox();
		}
	}
}

void CHollyWater::SetPosition(float simon_x, float simon_y)
{
	if (nx < 0)
	{
		this->x = simon_x + 5;
	}
	else {
		this->x = simon_x + 10;
	}

	this->y = simon_y;
}

void CHollyWater::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	if (state == STATE_HOLLYWATER_HIDE)
		return;

	RECT rect1, rect2;
	vector<LPGAMEOBJECT> listBrick;
	listBrick.clear();

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
					this->state = STATE_HOLLYWATER_APPEAR;
					this->isBroke = true;
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
					this->state = STATE_HOLLYWATER_APPEAR;
					this->isBroke = true;
				}
			}
		}
		
	}
}

void CHollyWater::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_HOLLYWATER_APPEAR)
	{
		left = x;
		top = y;
		right = x + HOLLYWATER_WIDTH;
		bottom = y + HOLLYWATER_HEIGHT;
	}
}

void CHollyWater::SetState(int st)
{
	// Xử lý tương tự axe
	this->state = st;
	if (st == STATE_HOLLYWATER_APPEAR)
	{
		vx = nx * HOLLYWATER_SPEED_X;
		vy = -HOLLYWATER_SPEED_Y;
	}
}
