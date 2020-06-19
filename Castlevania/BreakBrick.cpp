#include "BreakBrick.h"

void CBreakBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isStroke == true)
	{
		if (item != NULL)
		{
			item->Update(dt);

			if (item->GetState() == STATE_ITEM_NOT_EXSIST)
				this->blood = 0;
		}
		for (UINT i = 0; i < listEffect.size(); i++)
		{
			listEffect[i]->Update(dt);
		}
	}
}

void CBreakBrick::Render()
{
	if (isStroke == false)
	{
		animations[0]->Render(x, y);
	}
	else
	{
		for (UINT i = 0; i < listEffect.size(); i++)
		{
			listEffect[i]->Render();
		}
	}
}

void CBreakBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isStroke == false)
	{
		left = x;
		top = y;
		right = x + BREAK_BRICK_WIDTH;
		bottom = y + BREAK_BRICK_HEIGHT;
	}
	else
		left = top = right = bottom = 0;
}
