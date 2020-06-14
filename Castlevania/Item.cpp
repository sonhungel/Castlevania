#include "Item.h"
#include"Brick.h"

void CItem::Render()
{
	if (state == STATE_ITEM_EXSIST)
	{
		if (animations.size() > 0)
			animations[0]->Render(x, y);
		
	}
	RenderBoundingBox();
}

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!time_exsist)
		time_exsist = GetTickCount();
	else
	{
		if (GetTickCount() - time_exsist >= TIME_ITEM_EXSIST)
			state = STATE_ITEM_NOT_EXSIST;
	}

	CGameObject::Update(dt);
	this->vy += GRAVITY_ITEM * dt;

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
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0)
			vx = 0;
		if (ny != 0)
			vy = 0;
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) 
		delete coEvents[i];

}

void CItem::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = top = right = bottom = 0;
}
