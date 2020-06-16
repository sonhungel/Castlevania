#include "Knife.h"
#include"Game.h"

CKnife* CKnife::__instance = NULL;

CKnife* CKnife::GetInstance()
{
	if (__instance == NULL) __instance = new CKnife();
	return __instance;
}

void CKnife::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	if (state == STATE_KNIFE_APPEAR)
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
			state = STATE_KNIFE_HIDE;
			start_attack = 0;
		}
	}
	
}

void CKnife::Render()
{
	if (state == STATE_KNIFE_APPEAR)
	{
		animations[0]->RenderTrend(x, y, nx);
		DebugOut(L"Knife rendered\n");
		//RenderBoundingBox();
	}
}

void CKnife::SetPosition(float x, float y)
{
	if (nx < 0)
	{
		this->x = x;
	}
	else
	{
		this->x = x;
	}
	this->y = y;
}

void CKnife::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KNIFE_WIDTH;
	bottom = y + KNIFE_HEIGHT;
}

void CKnife::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	if (STATE_KNIFE_HIDE)
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
					listObj.at(i)->SetState(STATE_TORCH_NOT_EXSIST);
					this->state = STATE_KNIFE_HIDE;
				}
			}
		}
	}
}
