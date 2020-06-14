#include "Torch.h"
#include"ItemSmallHeart.h"

CTorch::CTorch(int id) : CGameObject()
{
	dt_die = 0;
	this->blood = 1;
	state = STATE_TORCH_EXSIST;
	effect = new CEffect(ID_ANIMATION_EFFECT);
	switch (id)
	{
	case TYPE_ITEM_HEART:
		item = new CItemHeart(x,y);
		break;
	case TYPE_ITEM_WHIPUPGRADE:
		item = new CItemWhipUpgrade(x,y);
		break;
	case TYPE_ITEM_KNIFE:
		item = new CItemKnife(x,y);
		break;
	case TYPE_ITEM_AXE:
		item = new CItemAxe(x,y);
		break;
	case TYPE_ITEM_SMALLHEART:
		item = new CItemSmallHeart(x, y);
	case TYPE_ITEM_UNKNOW:
		break;
	}
}

void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (dt_die == 0)
	{
		if (state == STATE_TORCH_NOT_EXSIST)
		{
			if (effect != NULL)
			{
				effect->SetPosition(this->x, this->y);
			}
			dt_die = GetTickCount();
		}
	}
	else
	{
		if (item != NULL)		// => có item 
		{
			if (GetTickCount() - dt_die > TIME_EFFECT) // 100 is time default
			{
				delete effect;
				effect = NULL;

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
	else if(effect!=NULL)
	{
			effect->Render();
	}
	if (state == STATE_TORCH_ITEM_EXSIST)
	{
		if (item != NULL)
		{
			item->Render();
		}
	}
	RenderBoundingBox();
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
