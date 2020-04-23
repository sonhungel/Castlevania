
#pragma once

#include"GameObject.h"
#include"Simon.h"
#include"Textures.h"
#include"Item.h"
#include"ItemHeart.h"
#include"ItemWhipUpgrade.h"
#include"ItemKnife.h"


//===========DEFINE=======================
#define TORCH_WIDTH			32
#define TORCH_HEIGHT		68

#define STATE_TORCH_NOT_EXSIST		0
#define STATE_TORCH_EXSIST			1
#define STATE_TORCH_ITEM_EXSIST		2
#define STATE_TORCH_ITEM_NOT_EXSIST 3

#define ID_ITEM_HEART				1
#define ID_ITEM_WHIPUPGRADE			2
#define ID_ITEM_KNIFE				3

#define FIRE_TIME			300

class CTorch:public CGameObject
{
	DWORD dt_die; // đo thời gian cho animation lửa xuất hiện sau khi đánh stroke torch
	CItem* item;
	int level;
	
public:
	CTorch(int id = 0,int level=0); // id Item, level là của whip
	~CTorch()
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
			item->SetPosition(x+7, y);
	}
	CItem* GetItem() { return item; }
};

