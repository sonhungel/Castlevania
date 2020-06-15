#include "Axe.h"
#include"Torch.h"
#include"Brick.h"
#include"Game.h"
#include"Define.h"

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
	state = AXE_STATE_HIDE;
	start_attack = 0;
}

void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (state == AXE_STATE_APPEAR)
	{
		if (start_attack == 0)
			start_attack = GetTickCount();
		if (GetTickCount() - start_attack > AXE_TIME)
		{
			state = AXE_STATE_HIDE;
			start_attack = 0;
			animations[0]->ResetFrame();
		}
		x += vx * dt;
		vy += GRAVITY * dt;
		y += vy * dt;
		DebugOut(L"AXE appear\n");
	}
}

void CAxe::SetPosition(float simon_x, float simon_y)
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

void CAxe::Render()
{
	if (state == AXE_STATE_APPEAR)
	{
		animations[0]->Render(x, y, nx);
		//DebugOut(L"Knife rendered\n");
		RenderBoundingBox();
	}
}

void CAxe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = x + AXE_WIDTH;
	top = y;
	bottom = y + AXE_HEIGHT;
}

void CAxe::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	if (AXE_STATE_HIDE)
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
					this->state = AXE_STATE_HIDE;
					start_attack = 0;
				}
			}
		}
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
				this->state = AXE_STATE_HIDE;
				start_attack = 0;
			}
		}
	}
}

void CAxe::SetState(int st)
{
	this->state == st;
	if (st == AXE_STATE_APPEAR)
	{
		vx = nx * AXE_SPEED_X;
		vy = -AXE_SPEED_Y;
	}
}
