#pragma once
#include"GameObject.h"

#define HIDENOBJECT_TYPE_UPSTAIR	1
#define HIDENOBJECT_TYPE_DOWNSTAIR  2

#define HIDENOBJECT_WIDTH	10
#define HIDENOBJECT_HEIGHT	50


class CHidenObject :public CGameObject
{
private:
	int _autoX;
	int ny;
public:
	CHidenObject(float _x = 0, float _y = 0, int state = 0, int trendX = 0, int trendY = 0) 
	{
		this->x = _x;
		this->y = _y;

		nx = trendX;
		ny = trendY;
		this->state = state;
		if (state == HIDENOBJECT_TYPE_DOWNSTAIR)
		{
			if (nx > 0)
				_autoX = x - 10;
			else
				_autoX = x + 20;
		}
		else if (state == HIDENOBJECT_TYPE_UPSTAIR)
		{
			if (nx < 0)
				_autoX = x - 30;
			else
				_autoX = x + 40;

		}
		else
			_autoX = x + 40;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	int getNx() { return nx; }
	int getNy() { return ny; }
	int GetAutoX() { return _autoX; }
};

