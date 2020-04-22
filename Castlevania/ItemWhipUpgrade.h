#pragma once
#include "Item.h"
#include"Whip.h"

//==========DEFINE================

class CItemWhipUpgrade :public CItem
{
public:
	CItemWhipUpgrade()
	{
		AddAnimation(701);
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

