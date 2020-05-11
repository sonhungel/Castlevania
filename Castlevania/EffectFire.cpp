#include "EffectFire.h"


void CEffectFire::Render()
{
	if (isDone == false)
		animations[0]->Render(x,y);
}

void CEffectFire::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x;
	bottom = y;
}
