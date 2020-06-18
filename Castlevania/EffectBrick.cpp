#include "EffectBrick.h"

void CEffectBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += GRAVITY * dt;
	x += dx;
	y += dy;
}

void CEffectBrick::Render()
{
	if (animations.size() > 0)
		animations[0]->Render(x, y);
}

void CEffectBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = top = right = bottom = 0;
}
