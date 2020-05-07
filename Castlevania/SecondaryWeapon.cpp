#include "SecondaryWeapon.h"
#include"Torch.h"
#include"Brick.h"

#define SCREEN_WIDTH 560
#define SCREEN_HEIGHT 500


void CSecondaryWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	switch (state)
	{
	case TYPE_WEAPON_AXE:
		vy += dt * WEAPON_GRAVITY;
		break;
	default:
		break;
	}
	CollisionWithObject(dt, *coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		// kiểm tra va chạm với object
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny,rdx,rdy);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick*>(e->obj))
			{
				isCollisonWithBrick = true;
			}
			if (dynamic_cast<CTorch*>(e->obj))
			{
				CTorch* torch = dynamic_cast<CTorch*>(e->obj);
				if (torch->GetState() == STATE_TORCH_EXSIST)
					torch->SetState(STATE_TORCH_NOT_EXSIST);
			}
		}
	}
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CSecondaryWeapon::Render()
{
	if (isCollisonWithBrick==false&&CheckOutCam(xBefore)==false)
	{
		if (state == TYPE_WEAPON_KNIFE)
			animations[TYPE_WEAPON_KNIFE]->RenderTrend(x, y, nx);
		else if (state == TYPE_WEAPON_AXE)
			animations[TYPE_WEAPON_AXE]->RenderTrend(x, y, nx);

	}
}

void CSecondaryWeapon::SetPosition(float x, float y)
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
	xBefore = x;
}

void CSecondaryWeapon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case TYPE_WEAPON_KNIFE:
		if (nx > 0)
			vx = KNIFE_SPEED;
		else
			vx = -KNIFE_SPEED;
		vy = 0;
	case TYPE_WEAPON_AXE:
		if (nx > 0) 
			vx = AXE_SPEED_X;
		else 
			vx = -AXE_SPEED_X;
		vy = -AXE_SPEED_y;
		break;
	default:
		break;
	}
}

bool CSecondaryWeapon::CheckOutCam(float x)
{
	if (vx > 0)
	{
		if (this->x - x >= (SCREEN_WIDTH / 2))
			return true;
	}
	else if (vx < 0)
	{
		if (x - this->x >= (SCREEN_WIDTH / 2))
			return true;
	}
	return false;
}

void CSecondaryWeapon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state== TYPE_WEAPON_KNIFE)
	{
		left = x;
		top = y;
		right = x + KNIFE_WIDTH;
		bottom = y + KNIFE_HEIGHT;
	}
	if (state == TYPE_WEAPON_AXE)
	{
		left = x;
		top = y;
		right = x + AXE_WIDTH;
		bottom = y + AXE_HEIGHT;
	}
}

/*void CSecondaryWeapon::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	for (int i = 0; i < listObj.size(); i++)
	{
		if (dynamic_cast<CTorch*>(listObj.at(i)))
		{
			if (listObj.at(i)->GetState() == STATE_TORCH_EXSIST)
			{
				LPCOLLISIONEVENT temp = SweptAABBEx(listObj.at(i));
				if (temp->t > 0) // => có đụng độ
				{
					listObj.at(i)->SetState(STATE_TORCH_NOT_EXSIST);
				}
			}
		}
	}
}*/
