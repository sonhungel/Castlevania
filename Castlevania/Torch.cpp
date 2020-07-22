#include "Torch.h"
#include"ItemSmallHeart.h"
#include"ItemNormal.h"
#include"ItemMoney.h"
#include"Brick.h"

CTorch::CTorch(int typeitem,float _x, float _y) : CGameObject()
{
	this->type = eType::TORCH;
	this->x = _x;
	this->y = _y;

	dt_die = 0;
	dt_strock = 0;

	this->blood = 1;
	state = STATE_TORCH_EXIST;
	
	isStrock = false;

	effectDie = new CEffect(DEATH_EFFECT_ANI_ID, this->x, this->y);
	effectHit = new CEffect(HIT_EFFECT_ANI_ID, this->x, this->y);

	if (typeitem == eType::ITEM_SMALLHEART)
		item = new CItemSmallHeart(x, y);
	else if (typeitem == eType::ITEM_RED_MONEY ||
		typeitem == eType::ITEM_YELLOW_MONEY ||
		typeitem == eType::ITEM_PURPLE_MONEY ||
		typeitem == eType::ITEM_BLUE_MONEY)
		item = new CItemMoney(x,y,typeitem);
	else
		item = new CItemNormal(x, y, typeitem); //
}

void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPGAMEOBJECT> listBrick;

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CBrick*>(coObjects->at(i)))
		{
			listBrick.push_back(coObjects->at(i));
		}
	}

	if (dt_die == 0)	// đo thời gian die
	{
		if (state == STATE_TORCH_NOT_EXIST)
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
				state = STATE_TORCH_ITEM_EXIST;
			}

			if(state==STATE_TORCH_ITEM_EXIST)
				item->Update(dt, &listBrick);
		}
	}
	if (item->state == STATE_ITEM_NOT_EXSIST)
		this->blood=0;
	if (dt_strock == 0)			// đo thời gian effect
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
	if (state == STATE_TORCH_EXIST)
	{
		animations[0]->Render(x, y);
		
	}
	else if(effectDie!=NULL)
	{
			effectDie->Render();
	}
	if (isStrock == true)
		effectHit->Render();
	if (state == STATE_TORCH_ITEM_EXIST)
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
	if (state == STATE_TORCH_EXIST)
	{
		left = x;
		top = y;
		right = x + TORCH_WIDTH;
		bottom = y + TORCH_HEIGHT;
	}
	else if (state == STATE_TORCH_ITEM_EXIST)
	{
		item->GetPosition(x, y);
		item->GetBoundingBox(left,top,right,bottom);
	}
}
