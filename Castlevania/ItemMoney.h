#pragma once
#include "Item.h"
#include"Effect.h"

#define ITEM_MONEY_WIDTH 32
#define ITEM_MONEY_HEIGHT 27

#define ITEM_MONEY_EFFECT_100	810
#define ITEM_MONEY_EFFECT_400	811
#define ITEM_MONEY_EFFECT_700	812
#define ITEM_MONEY_EFFECT_1000	813

#define MONEY_EFFECT_TIME		1000

class CItemMoney :public CItem
{
private:
	DWORD dt_effection;
	CEffect* effect;

	float destination_x; // Dùng cho hiden money 1000
	float destination_y;

	static bool isStartShowHiden;	// dùng cho hiden money

public: 
	bool isEated;
	CItemMoney(float _x, float _y, int type, int ani_id) :CItem(_x, _y)
	{
		this->type = type;
		AddAnimation(ani_id);
		switch (this->type)
		{
		case eType::ITEM_RED_MONEY:
			effect = new CEffect(ITEM_MONEY_EFFECT_100, x, y);
			break;
		case eType::ITEM_YELLOW_MONEY:
			effect = new CEffect(ITEM_MONEY_EFFECT_400, x, y);
			break;
		case eType::ITEM_PURPLE_MONEY:
			effect = new CEffect(ITEM_MONEY_EFFECT_700, x, y);
			break;
		case eType::ITEM_HIDEN_MONEY:
			effect = new CEffect(ITEM_MONEY_EFFECT_1000, x, y);
			break;
		default:
			break;
		}
		dt_effection = 0;
		isEated = false;
		destination_x = x;
		destination_y = y - 33;
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	static void Start() { isStartShowHiden = true; }
	static void Stop() { isStartShowHiden = false; }
	static bool IsStart() { return isStartShowHiden; }

};

