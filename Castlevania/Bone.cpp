#include "Bone.h"

void CBone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects )
{
	if (blood > 0 )
	{
		if (this->y >= SCREEN_HEIGHT)
		{
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
	if (this->blood > 0 )
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

