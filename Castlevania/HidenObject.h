﻿#pragma once
#include"GameObject.h"

#define HIDENOBJECT_TYPE_STAIR_ABOVE	1
#define HIDENOBJECT_TYPE_STAIR_BELOW  2
#define HIDENOBJECT_TYPE_SPECIAL	 3

#define HIDENOBJECT_TYPE_ACTIVE_BOSS	4

#define HIDENOBJECT_TYPE_ACTIVE_SECRET	5


class CHidenObject :public CGameObject
{
private:
	int width;
	int height;
	int _autoX;	// vị trí để simon bắt đầu auto move
	int ny;// kết hợp nx để xác định hướng của thang
public:
	CHidenObject(float _x = 0, float _y = 0,int w=0,int h=0, int state = 0, int trendX = 0, int trendY = 0) 
	{
		this->blood = 1;

		this->width = w;
		this->height = h;
		this->x = _x;
		this->y = _y;

		nx = trendX;
		ny = trendY;
		this->state = state;
		if (state == HIDENOBJECT_TYPE_STAIR_BELOW)
		{
			if (nx > 0)
				_autoX = (int)x - 10;
			else
				_autoX = (int)x + 20;
		}
		else if (state == HIDENOBJECT_TYPE_STAIR_ABOVE)
		{
			if (nx < 0)
				_autoX = (int)x - 10;
			else
				_autoX = (int)x -35;
		}
		else if (state == HIDENOBJECT_TYPE_SPECIAL)
		{
			_autoX = (int)x;
		}
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	int getNx() { return nx; }
	int getNy() { return ny; }
	int GetAutoX() { return _autoX; }
};

