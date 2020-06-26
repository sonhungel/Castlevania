#pragma once

#include"GameObject.h"
#include"Simon.h"
#include"Textures.h"
#include"Item.h"
#include"ItemNormal.h"
#include"Effect.h"


//===========DEFINE=======================
#define CANDLE_WIDTH			15
#define CANDLE_HEIGHT			30

#define STATE_CANDLE_NOT_EXIST			0
#define STATE_CANDLE_EXIST				1
#define STATE_CANDLE_ITEM_EXIST		2
#define STATE_CANDLE_ITEM_NOT_EXIST	3


#define TIME_EFFECT_DEATH		400	// thời gian bằng đúng số lượng frame animation* 100 mili seconds
#define TIME_EFFECT_HIT		200

class CCandle : public CGameObject
{
	DWORD dt_die; // đo thời gian cho animation lửa xuất hiện sau khi đánh 
	DWORD dt_strock;
	CItem* item;

	CEffect* effectDie;
	CEffect* effectHit;
public:
	bool isStrock;

	CCandle(int type, int ani_id, float _x, float _y);
	~CCandle()
	{
		CGameObject::~CGameObject();
		if (item != NULL)
			delete item;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetPosition(float _x, float _y)
	{
		x = _x;
		y = _y;
		if (item != NULL)
			item->SetPosition(x + 7, y);
	}
	CItem* GetItem() { return item; }
};

