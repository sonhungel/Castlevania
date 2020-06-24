#include "Torch.h"
#include"ItemSmallHeart.h"
#include"ItemNormal.h"
#include"ItemMoney.h"

CTorch::CTorch(int type, int ani_id,float _x, float _y) : CGameObject()
{
	this->type == eType::TORCH;
	this->x = _x;
	this->y = _y;

	dt_die = 0;
	dt_strock = 0;

	this->blood = 1;
	state = STATE_TORCH_EXSIST;
	
	isStrock = false;

	effectDie = new CEffect(DEATH_EFFECT_ANI_ID, this->x, this->y);
	effectHit = new CEffect(HIT_EFFECT_ANI_ID, this->x, this->y);

	if (type == eType::ITEM_SMALLHEART)
		item = new CItemSmallHeart(x, y);
	else if (type == eType::ITEM_RED_MONEY ||
		type == eType::ITEM_YELLOW_MONEY ||
		type == eType::ITEM_PURPLE_MONEY ||
		type == eType::ITEM_BLUE_MONEY)
		item = new CItemMoney(x,y,type,ani_id);
	else
		item = new CItemNormal(x, y, type, ani_id); //
}

void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (dt_die == 0)
	{
		if (state == STATE_TORCH_NOT_EXSIST)
		{
			dt_die = GetTickCount();
		}
	}
	else
	{
		if (item != NULL)		// => có item 
		{
			if (GetTickCount() - dt_die > TIME_EFFECT_DEATH) // 100 is time default
			{
				delete effectDie;
				effectDie = NULL;
				state = STATE_TORCH_ITEM_EXSIST;
			}
			if(state==STATE_TORCH_ITEM_EXSIST)
				item->Update(dt, coObjects);
		}
	}
	if (item->state == STATE_ITEM_NOT_EXSIST)
		blood--;
	if (dt_strock == 0)
	{
		if (isStrock == true)
			dt_strock = GetTickCount();
	}
	else
	{
		if (isStrock == true)
		{
			if (GetTickCount() - dt_strock > TIME_EFFECT_HIT) // 100 is time default
			{
				isStrock = false;
				delete effectHit;
				effectHit = NULL;
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
	else if(effectDie!=NULL)
	{
			effectDie->Render();
	}
	if (isStrock == true)
		effectHit->Render();
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
