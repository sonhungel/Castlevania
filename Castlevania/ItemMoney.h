#pragma once
#include "Item.h"
#include"Effect.h"

#define ITEM_MONEY_WIDTH 32
#define ITEM_MONEY_HEIGHT 27

#define ITEM_MONEY_EFFECT_100	810
#define ITEM_MONEY_EFFECT_400	811
#define ITEM_MONEY_EFFECT_700	812
#define ITEM_MONEY_EFFECT_1000	813

#define ITEM_MONEY_RED_ANI_ID	705
#define ITEM_MONEY_YELLOW_ANI_ID	706
#define ITEM_MONEY_PURPLE_ANI_ID	707
#define ITEM_MONEY_BLUE_ANI_ID	717

#define MONEY_EFFECT_TIME		1000

class CItemMoney :public CItem
{
private:
	DWORD dt_effection;
	CEffect* effect;


public: 
	bool isEated;
	CItemMoney(float _x, float _y, int type) :CItem(_x, _y)
	{
		this->type = type;

		switch (this->type)
		{
		case eType::ITEM_RED_MONEY:
		{
			effect = new CEffect(ITEM_MONEY_EFFECT_100, x, y); 
			AddAnimation(ITEM_MONEY_RED_ANI_ID);
		}
			break;
		case eType::ITEM_YELLOW_MONEY:
		{
			effect = new CEffect(ITEM_MONEY_EFFECT_400, x, y); 
			AddAnimation(ITEM_MONEY_YELLOW_ANI_ID);
		}
			break;
		case eType::ITEM_PURPLE_MONEY:
		{
			effect = new CEffect(ITEM_MONEY_EFFECT_700, x, y);
			AddAnimation(ITEM_MONEY_PURPLE_ANI_ID);
		}
			break;
		case eType::ITEM_BLUE_MONEY:
		{
			effect = new CEffect(ITEM_MONEY_EFFECT_1000, x, y);
			AddAnimation(ITEM_MONEY_BLUE_ANI_ID);
		}
			break;
		default:
			break;
		}
		dt_effection = 0;
		isEated = false;
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

