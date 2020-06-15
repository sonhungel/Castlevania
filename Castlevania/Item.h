#pragma once
#ifndef __ITEM_H_
#define __ITEM_H_


#include"GameObject.h"
#include"Simon.h"
#include"Textures.h"
#include"Define.h"

//===========DEFINE================

#define STATE_ITEM_NOT_EXSIST	0
#define STATE_ITEM_EXSIST		1

#define TYPE_ITEM_UNKNOW		0
#define TYPE_ITEM_KNIFE			1	// 701
#define TYPE_ITEM_WHIPUPGRADE	2	// 700
#define TYPE_ITEM_HEART			3	// 702
#define TYPE_ITEM_AXE			4	// 703
#define TYPE_ITEM_SMALLHEART	5	// 704	// đặc biệt vì có di chuyển zic zac
#define TYPE_ITEM_RED_MONEY		6	// 705	// có effect
#define TYPE_ITEM_YELLOW_MONEY	7	// 706	// có effect
#define TYPE_ITEM_PURPLE_MONEY	8	// 707	// có effect
#define TYPE_ITEM_CLOCK			10	// 709
#define TYPE_ITEM_CROSS			11	// 710
#define TYPE_ITEM_II			12	// 711
#define TYPE_ITEM_III			13	// 712
#define TYPE_ITEM_HOLLYWATER	14	// 713
#define TYPE_ITEM_BALL_BOSS		15	// 714
#define TYPE_ITEM_BOMMERANG		16	// 715
#define TYPE_ITEM_VASE			17	// 716
#define TYPE_ITEM_HIDEN_MONEY	18	// 717	// có effect

#define GRAVITY_ITEM		  0.002f

#define TIME_ITEM_EXSIST 5000


class CItem;
typedef CItem* LPITEM;

class CItem:public CGameObject
{
protected:
	DWORD time_exsist;
public:
	CItem(float _x = 0, float _y = 0) :CGameObject()
	{
		this->x = _x;
		this->y = _y;
		state = STATE_ITEM_EXSIST;
		type = eType::UNKNOW;
		time_exsist = 0;
	}
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
#endif

