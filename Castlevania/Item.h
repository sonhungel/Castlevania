#pragma once
#ifndef __ITEM_H_
#define __ITEM_H_


#include"GameObject.h"
#include"Simon.h"
#include"Textures.h"

//===========DEFINE================

#define STATE_ITEM_NOT_EXSIST	0
#define STATE_ITEM_EXSIST		1

#define TYPE_ITEM_UNKNOW		0
#define TYPE_ITEM_KNIFE			1
#define TYPE_ITEM_WHIPUPGRADE	2
#define TYPE_ITEM_HEART			3
#define TYPE_ITEM_AXE			4
#define TYPE_ITEM_SMALLHEART	5
#define TYPE_ITEM_RED_MONEY		6
#define TYPE_ITEM_YELLOW_MONEY	7
#define TYPE_ITEM_PURPLE_MONEY	8
#define TYPE_ITEM_BLUE_MONEY	9
#define TYPE_ITEM_CLOCK			10
#define TYPE_ITEM_CROSS			11
#define TYPE_ITEM_II			12
#define TYPE_ITEM_III			13
#define TYPE_ITEM_HOLLYWATER	14
#define TYPE_ITEM_BALL_BOSS		15
#define TYPE_ITEM_BOMMERANG		16
#define TYPE_ITEM_VASE			17
#define TYPE_ITEM_HIDEN_MONEY	18

#define GRAVITY_ITEM		  0.002f

#define TIME_ITEM_EXSIST 5000


class CItem;
typedef CItem* LPITEM;

class CItem:public CGameObject
{
protected:
	DWORD time_exsist;
	int type_Item; // định dang item
public:
	CItem(float _x = 0, float _y = 0) :CGameObject()
	{
		this->x = _x;
		this->y = _y;
		state = STATE_ITEM_EXSIST;
		type_Item = TYPE_ITEM_UNKNOW;
		time_exsist = 0;
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual int getType() { return type_Item; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
#endif

