#include "HollyWater.h"
#include"Torch.h"
#include"Game.h"
#include"Brick.h"

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
			y += vy * dt;
		}

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		CalcPotentialCollisions(&listBrick, coEvents);

		if (coEvents.size() == 0)
		{
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			// block 
			//x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y -= 10;//min_ty * dy + ny * 0.5f;

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
			//DebugOut(L"AXE rendered\n");
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
			if (listObj.at(i)->GetState() == STATE_TORCH_EXSIST)
			{
				// get bounding box of the object that knife collision
				listObj.at(i)->GetBoundingBox(l2, t2, r2, b2);
				rect2.left = (int)l2;
				rect2.top = (int)t2;
				rect2.right = (int)r2;
				rect2.bottom = (int)b2;
				if (CGame::GetInstance()->isCollision(rect1, rect2)) // => có đụng độ
				{
					vx = vy = 0;
					listObj.at(i)->SetState(STATE_TORCH_NOT_EXSIST);
					this->state = STATE_HOLLYWATER_HIDE;
					start_attack = 0;
				}
			}
		}
		
		/*
		if (dynamic_cast<CBrick*>(listObj.at(i)))
		{
			listObj.at(i)->GetBoundingBox(l2, t2, r2, b2);
			rect2.left = (int)l2;
			rect2.top = (int)t2;
			rect2.right = (int)r2;
			rect2.bottom = (int)b2;
			if (CGame::GetInstance()->isCollision(rect1, rect2)) // => có đụng độ
			{
				vx = vy = 0;
				//isBroke = true;
				y -= 15;
				//start_attack = 0;
			}
		}*/
	}
}

void CHollyWater::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_HOLLYWATER_APPEAR)
	{
		if (isBroke == false)
		{
			left = x;
			top = y;
			right = x + HOLLYWATER_WIDTH;
			bottom = y + HOLLYWATER_HEIGHT;
		}
		else
		{
			left = x;
			top = y;
			right = x + 25;
			bottom = y + 30;
		}
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
