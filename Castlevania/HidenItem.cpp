#include "HidenItem.h"
#include"Utils.h"

bool CHidenItem::isStartShowHiden = false;

void CHidenItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (y >= destination_y && CHidenItem::IsStart())
	{
		y -= 0.1f * dt;
	}

	/*
	if (isStartShowHiden == false)
	{
		DebugOut(L"FALSE show hiden\n");
	}
	else
	{
		DebugOut(L"TRUE show hiden\n");
	}*/
}

void CHidenItem::Render()
{
	if (CHidenItem::IsStart())
	{
		if (state == STATE_ITEM_EXSIST)
		{
			if (animations.size() > 0)
				animations[0]->Render(x, y);
		}
	}
}

void CHidenItem::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_ITEM_EXSIST)
	{
		left = x;
		right = x + HIDEN_ITEM_WIDTH;
		top = y;
		bottom = y + HIDEN_ITEM_HEIGHT;
	}
}
