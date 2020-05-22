#pragma once
#include"GameObject.h"

#define EFFECT_WIDTH 25
#define EFFECT_HEIGHT 37

// Tất cả effect đều đc sử dụng chung bằng class này, đối với những effect có số lượng animation frame <4 thì sẽ phải add
// thêm những animation frame blank cho đủ 4

class CEffect:public CGameObject
{
public:
	CEffect(int animationID)
	{
		AddAnimation(animationID);
	}
	~CEffect() {};
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	CAnimation* GetAnimation() { if (animations.size() > 0)return animations[0]; } // get animation off effect để tính frame thay vì đo thời gian
};
