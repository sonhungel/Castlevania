#include "Torch.h"

CTorch::CTorch(int id,int level) : CGameObject()
{
	dt_die = 0;
	state = STATE_TORCH_EXSIST;
	if (level == 0)
	{
		AddAnimation(501);
	}
	
	AddAnimation(800);	// fire after stroke torch
	switch (id)
	{
	case ID_ITEM_HEART:
		item = new CItemHeart();
		break;
	case ID_ITEM_WHIPUPGRADE:
		item = new CItemWhipUpgrade();
		break;
	case ID_ITEM_KNIFE:
		item = new CItemKnife();
	case 0:
		break;
	}

}

void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (dt_die == 0)
	{
		if (state == STATE_TORCH_NOT_EXSIST)
			dt_die = GetTickCount();
	}
	else
	{
		if (item != NULL)		// => có item 
		{
			if (GetTickCount() - dt_die > 250) // wait for the fire after stroke torch end
			{
				state = STATE_TORCH_ITEM_EXSIST;
				item->Update(dt, coObjects);
			}
		}
	}
}

void CTorch::Render()
{
	if (state == STATE_TORCH_EXSIST)
	{
		animations[0]->Render(x, y);
		
	}
	else 
	{
		if (GetTickCount() - dt_die < FIRE_TIME)
			animations[1]->Render(x, y);
	}
	if (state == STATE_TORCH_ITEM_EXSIST)
	{
		if (item != NULL)
		{
			item->Render();
		}
	}
	//RenderBoundingBox();
}

void CTorch::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_TORCH_EXSIST)
	{
		left = x;
		top = y;
		right = x + TORCH_WIDTH;
		bottom = y + TORCH_HEIGHT;
	}
	else if (state == STATE_TORCH_ITEM_EXSIST)
	{
		item->GetPosition(x, y);
		item->GetBoundingBox(left,top,right,bottom);
	}
}
