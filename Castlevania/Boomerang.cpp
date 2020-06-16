#include "Boomerang.h"
#include"Torch.h"
#include"Game.h"
CBoomerang* CBoomerang::__instance = NULL;

CBoomerang* CBoomerang::GetInstance()
{
	if (__instance == NULL)
		__instance = new CBoomerang();
	return __instance;
}

CBoomerang::CBoomerang()
{
	type = eType::WEAPON_BOOMERANG;
	AddAnimation(BOOMERANG_ANI_ID);
	state = STATE_BOOMERANG_HIDE;
	start_attack = 0;
}

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->state == STATE_BOOMERANG_APPEAR)
	{
		CGameObject::Update(dt);
		if (start_attack == 0)
			start_attack = GetTickCount();

		x += vx * dt;

		if (GetTickCount() - start_attack > BOOMERANG_TIME)
		{
			state = STATE_BOOMERANG_HIDE;
			start_attack = 0;
			animations[0]->ResetFrame();
		}
		if (x <= x_left || x >= x_right)
		{
			vx = -vx;
			turn++;
		}
		if(turn<2)
			CollisionWithObject(dt, *coObjects);
		//DebugOut(L"AXE appear\n");
	}
}

void CBoomerang::SetPosition(float simon_x, float simon_y)
{
	if (nx < 0)
	{
		this->x = simon_x + 5;
	}
	else {
		this->x = simon_x - 10;
	}

	this->y = simon_y;
}

void CBoomerang::Render()
{
	if (state == STATE_BOOMERANG_APPEAR)
	{
		animations[0]->RenderTrend(x, y, nx);
	}
}

void CBoomerang::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_BOOMERANG_APPEAR)
	{
		left = x;
		top = y;
		right = x + BOOMERANG_WIDTH;
		bottom = y + BOOMERANG_HEIGHT;
	}
}

void CBoomerang::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	if (state==STATE_BOOMERANG_HIDE)
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
					this->state = STATE_BOOMERANG_HIDE;
					start_attack = 0;
				}
			}
		}
	}
}

void CBoomerang::SetState(int st)
{
	this->state = st;
	if (st == STATE_BOOMERANG_APPEAR)
	{
		vx = nx * BOOMERANG_SPEED;

		float temp;
		CGame::GetInstance()->GetCamPos(x_left,temp);
		x_right = x_left + SCREEN_WIDTH;
	}
}
