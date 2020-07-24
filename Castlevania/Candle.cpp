#include "Candle.h"
#include"ItemSmallHeart.h"
#include"ItemNormal.h"
#include"ItemMoney.h"
#include"Brick.h"

CCandle::CCandle(int typeitem,float _x, float _y)
{
	this->type == eType::CANDLE;
	this->x = _x;
	this->y = _y;

	dt_die = 0;
	dt_strock = 0;

	this->blood = 1;
	state = STATE_CANDLE_EXIST;

	isStrock = false;

	effectDie = new CEffect(DEATH_EFFECT_ANI_ID, this->x, this->y);
	effectHit = new CEffect(HIT_EFFECT_ANI_ID, this->x, this->y);

	if (typeitem == eType::ITEM_SMALLHEART)
		item = new CItemSmallHeart(x, y);
	else if (typeitem == eType::ITEM_RED_MONEY ||
		typeitem == eType::ITEM_YELLOW_MONEY ||
		typeitem == eType::ITEM_PURPLE_MONEY ||
		typeitem == eType::ITEM_BLUE_MONEY)
		item = new CItemMoney(x, y, typeitem);
	else
		item = new CItemNormal(x, y, typeitem); //
}

void CCandle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPGAMEOBJECT> listBrick;

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CBrick*>(coObjects->at(i)))
		{
			listBrick.push_back(coObjects->at(i));
		}
	}

	if (dt_die == 0)
	{
		if (state == STATE_CANDLE_NOT_EXIST)
		{
			dt_die = GetTickCount();
		}
	}
	else
	{
		if (item != NULL)		// => c� item 
		{
			if (GetTickCount() - dt_die > TIME_EFFECT_DEATH) // 100 is time default
			{
				delete effectDie;
				effectDie = NULL;
				state = STATE_CANDLE_ITEM_EXIST;
			}
			if(state==STATE_CANDLE_ITEM_EXIST)
				item->Update(dt, &listBrick);
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

void CCandle::Render()
{
	if (state == STATE_CANDLE_EXIST)
	{
		if(animations.size()>0)
			animations[0]->Render(x, y);
	}
	else if (effectDie != NULL)
	{
		effectDie->Render();
	}
	if (isStrock == true)
		effectHit->Render();
	if (state == STATE_CANDLE_ITEM_EXIST)
	{
		if (item != NULL)
		{
			item->Render();
		}
	}
	//RenderBoundingBox();
}

void CCandle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_CANDLE_EXIST)
	{
		left = x;
		top = y;
		right = x + CANDLE_WIDTH;
		bottom = y + CANDLE_HEIGHT;
	}
	else if (state == STATE_CANDLE_ITEM_EXIST)
	{
		item->GetPosition(x, y);
		item->GetBoundingBox(left, top, right, bottom);
	}
}
