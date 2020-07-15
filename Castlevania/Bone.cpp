#include "Bone.h"

void CBone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects )
{
	if (blood > 0 && state == STATE_BONE_APPEAR)
	{
		if (CheckOutCam() == true)
		{
			this->state = STATE_BONE_HIDE;
			this->blood = 0;
		}

		CGameObject::Update(dt);

		vy += BONE_GRAVITY * dt;

		x += dx;
		y += dy;
	}
}

void CBone::Render()
{
	if (blood > 0 && state == STATE_BONE_APPEAR)
	{
		animations[0]->RenderTrend(x, y, nx);
		RenderBoundingBox();
	}
}

void CBone::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BONE_WIDTH;
	bottom = y + BONE_HEIGHT;
}

bool CBone::CheckOutCam()
{
	if (this->y >= SCREEN_HEIGHT)
		return true;
	return false;
}
