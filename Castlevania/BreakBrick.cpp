#include "BreakBrick.h"
#include"Brick.h"

void CBreakBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state==STATE_BREAK_BRICK_EXIST)
		return;

	vector<LPGAMEOBJECT> listBrick;

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CBrick*>(coObjects->at(i)))
		{
			listBrick.push_back(coObjects->at(i));
		}
	}

	if (item != NULL)
	{
		if(state==STATE_BREAK_BRICK_ITEM_EXIST)
			item->Update(dt,&listBrick);
		if (item->GetState() == STATE_ITEM_NOT_EXSIST)
			this->blood = 0;
	}

	if (dt_effect == 0)
	{

	}
	else
	{
		for (UINT i = 0; i < listEffect.size(); i++)
		{
			listEffect[i]->Update(dt);
		}
	}
	if (GetTickCount() - dt_effect >= BREAK_BRICK_EFFECT_TIME)
	{
		dt_effect = 0;
		for (UINT i = 0; i < listEffect.size(); i++)
		{
			delete listEffect[i];
		}
		listEffect.clear();
		if (item == NULL)
			blood = 0;
	}
}

void CBreakBrick::Render()
{
	if (state==STATE_BREAK_BRICK_EXIST)
	{
		if (animations.size() > 0 && blood > 1)
			animations[0]->Render(x, y);
		RenderBoundingBox();
	}
	else 
	{
		if (item != NULL)
			item->Render();
		for (UINT i = 0; i < listEffect.size(); i++)
		{
			listEffect[i]->Render();
		}
	}
}

void CBreakBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state==STATE_BREAK_BRICK_EXIST)
	{
		left = x;
		top = y;
		right = x + BREAK_BRICK_WIDTH;
		bottom = y + BREAK_BRICK_HEIGHT;
	}
	else if (STATE_BREAK_BRICK_ITEM_EXIST)
	{
		if (item != NULL)
		{
			item->GetBoundingBox(left, top, right, bottom);
		}
		else
			left = top = right = bottom = 0;
	}
}
