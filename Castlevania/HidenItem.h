#pragma once
#include "Item.h"

#define CROWN_ANI_ID	718

#define HIDEN_ITEM_WIDTH	32
#define HIDEN_ITEM_HEIGHT	34

class CHidenItem : public CItem
{
	float destination_x;
	float destination_y;
	static bool isStartShowHiden;

public:
	CHidenItem(float _x, float _y,float d_x,float d_y) :CItem(_x, _y)
	{
		destination_x = d_x;
		destination_y = d_y;

		AddAnimation(CROWN_ANI_ID);

		state = STATE_ITEM_EXSIST;

		this->type = eType::ITEM_HIDEN;
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	static void Start() { isStartShowHiden = true; }
	static void Stop() { isStartShowHiden = false; }
	static bool IsStart() { return isStartShowHiden; }
};

