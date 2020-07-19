#include "Effect.h"
#include"Utils.h"



void CEffect::Render()
{
	if (animations.size() > 0)
	{
		animations[0]->Render(x, y);
		//RenderBoundingBox();
	}
}

void CEffect::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + EFFECT_WIDTH;
	bottom = y + EFFECT_HEIGHT;
}
