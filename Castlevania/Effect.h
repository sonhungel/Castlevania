#pragma once
#include"GameObject.h"

#define EFFECT_WIDTH 25
#define EFFECT_HEIGHT 37

#define DEATH_EFFECT_ANI_ID	800

#define HIT_EFFECT_ANI_ID	801

// Tất cả effect đều đc sử dụng chung bằng class này, đối với những effect có số lượng animation frame <4 thì sẽ phải add
// thêm những animation frame blank cho đủ 4

class CEffect:public CGameObject
{
public:
	CEffect(int ani_id, float _x, float _y)
	{
		this->x = _x;
		this->y = _y;
		AddAnimation(ani_id);
	}
	~CEffect() {};
	virtual  void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
