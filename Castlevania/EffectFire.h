#pragma once
#include"Effect.h"


class CEffectFire:public CEffect
{
public:
	CEffectFire()
	{
		isDone = false;
		animation = animations[0];
	}
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

