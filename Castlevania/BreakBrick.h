#pragma once
#include "GameObject.h"
#include"EffectBrick.h"

#define EFFECT_BRICK_ANI_ID  830

#define BREAK_BRICK_WIDTH		32
#define BREAK_BRICK_HEIGHT		32

class CBreakBrick :public CGameObject
{
	// effect gạch vỡ phải xây dựng 4 cái, có thể tạo list hoặc dùng 4 pointer
	// mỗi effec vì di chuyển ra 4 hướng nên cần phân chia các hướng di chuyển cho từng effect
};

