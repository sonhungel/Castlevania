#include "Effect.h"
#include"Utils.h"



void CEffect::Render()
{
	animations[0]->Render(x, y);
	//DebugOut(L"Render effect \n");
	RenderBoundingBox();
}

void CEffect::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + EFFECT_WIDTH;
	bottom = y + EFFECT_HEIGHT;
}
