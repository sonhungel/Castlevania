#pragma once
#ifndef __BRICK_H_
#define __BRICK_H_

#include "GameObject.h"

#define BRICK_WIDTH  32
class CBrick : public CGameObject
{
	int _width;	// vì scene đỏ và xanh dương có sprite rất bé so với thiết kế, nên brick cũng phải giảm nhỏ bounding box
public:
	CBrick(int scene) :CGameObject()
	{
		_width = scene;
		AddAnimation(499);
	}
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};
#endif