#include "Boss.h"
#include"time.h"
#include"Game.h"


// 1150	100
CBoss* CBoss::__instance = NULL;

CBoss* CBoss::GetInstance()
{
	if (__instance == NULL) __instance = new CBoss(1150,100);
	return __instance;
}

void CBoss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isActive == true)
		state = STATE_BOSS_FLY;
	else
		return;
#pragma region Xu_Ly_Hieu_Ung&Item
	if (dt_die == 0)	// đo thời gian die
	{
		if (blood < 2)
		{
			dt_die = GetTickCount();
		}
	}
	else
	{
		if (item != NULL)		// => có item 
		{
			if (GetTickCount() - dt_die > TIME_EFFECT_DIE_ENEMY) // 100 is time default
			{
				delete effectDie;
				effectDie = NULL;
			}
			else
				state = STATE_ENEMY_ITEM_EXIST;
			if (state == STATE_ENEMY_ITEM_EXIST)
			{
				item->Update(dt, coObjects);
			}
		}
	}
	if (item->GetState() == STATE_ITEM_NOT_EXSIST)
		this->blood = 0;
	if (dt_strock == 0)			// đo thời gian effect
	{
		if (isStrock == true)
			dt_strock = GetTickCount();
	}
	else
	{
		if (isStrock == true)
		{
			if (GetTickCount() - dt_strock > TIME_EFFECT_HIT_ENEMY) // 100 is time default
			{
				isStrock = false;
				dt_strock = 0;
				blood--;
			}
		}
	}
#pragma endregion

	if(this->blood>1)
	{
		D3DXVECTOR2 simonPosition;
		CSimon::GetInstance()->GetPositionVector2(simonPosition);
		if (GetTickCount() - start_attack >= TIME_BOSS_ATTACK && start_fly == 0)
		{

		}
	}
}

void CBoss::Render()
{
	if (blood > 1 && animations.size() > 0)
	{
		if (state == STATE_BOSS_SLEEP)
			animations[BOSS_ANI_SLEEPING]->RenderTrend(x, y, nx);
		else 
			animations[BOSS_ANI_FLYING]->RenderTrend(x, y, nx);
		RenderBoundingBox();
	}
	else if (effectDie != NULL)
	{
		effectDie->SetPosition(x, y);
		effectDie->Render();
	}
	if (isStrock == true)
	{
		effectHit->SetPosition(x, y);
		effectHit->Render();
	}
	if (state == STATE_ENEMY_ITEM_EXIST)
	{
		if (item != NULL)
		{
			item->Render();
		}
	}
}

void CBoss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_BOSS_ITEM)
	{
		item->GetBoundingBox(left, top, right, bottom);
	}
	else 
	{
		left = x;
		top = y;
		right = x + BOSS_WIDTH;
		bottom = y + BOSS_HEIGHT;
	}
}

void CBoss::AutoFly(float next_x, float next_y)
{
	position0.x = x;
	position0.y = y;
	// position 1 không cần tính ở trong này vì quỹ đạo bay không lấy simon làm target
	position2.x = next_x;
	position2.y = next_y;

	CSimon::GetInstance()->GetPositionVector2(position1);
	position1.y += SIMON_HEIGHT_STAND / 2;
	if (x < next_x)
		vx = BOSS_SPEED_AUTO_FLY_X;
	else
		vx = -BOSS_SPEED_AUTO_FLY_X;
	vy = BOSS_SPEED_AUTO_FLY_Y;
}

void CBoss::AutoAttack(float next_x, float next_y)
{
	CSimon::GetInstance()->GetPositionVector2(position1);
	position2.x = next_x;
	position2.y = next_y + SIMON_HEIGHT_STAND / 2;	// phải lao vào simon sâu hơn
}

void CBoss::FlyStraight(float next_x, float next_y)
{
	if (x < next_x)
	{
		nx = 1;
	}
	else
	{
		nx = -1;
	}
	if (next_x != x && next_y != y)
	{
		vx = BOSS_SPEED_STRAIGHT * nx;
		vy = 1.0 * (next_y - y) / (next_x - x) * nx * BOSS_SPEED_STRAIGHT;
	}
}

void CBoss::FlyCurve(float next_x, float next_y)
{
	// chỉ lấy chiều vì phải xử lý thêm bên ngoài
	if (x < next_x)
	{
		nx = 1;
	}
	else
	{
		nx = -1;
	}
}

void CBoss::SetFly()
{
	start_fly = 0;
	int _type; // kiểu bay > thẳng hoặc lượn

	// Random tỉ lệ các kiểu bay

	srand((unsigned)time(0));		// tăng độ random vì time(0) luôn luôn thay đổi theo thời gian
	_type = rand() % 3;	// 1/3 và 2/3

	if (_type == 2)
		type = TYPE_FLY_STRAIGHT;	// bay thẳng
	else
		type = TYPE_FLY_CURVE;	// bay lượn


	float cam_x, cam_y;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);

	if (type == TYPE_FLY_CURVE)
	{
		start_curve = GetTickCount();
		
		srand((unsigned)time(0));
		int ranValue= rand() % 2;

		float next_x, next_y;

		if (ranValue == 0)
		{
			if (x < cam_x + BOSS_WIDTH * 3 / 2)
				next_x = x + BOSS_WIDTH * 3 / 2;
			else
				next_x = x - BOSS_WIDTH * 3 / 2;
		}
		else
		{
			if (x < cam_x + BOSS_WIDTH / 2)
				next_x = x + SCREEN_WIDTH - BOSS_WIDTH * 3 / 2;
			else if (x > cam_x + SCREEN_WIDTH - BOSS_WIDTH)
				next_x = x - (SCREEN_WIDTH - BOSS_WIDTH);
			else if (x < cam_x + BOSS_WIDTH * 3 / 2)
				next_x = x + BOSS_WIDTH * 3 / 2;
			else
				next_x = x - BOSS_WIDTH * 3 / 2;
		}
		AutoFly(next_x, y);
	}
	else
	{
		if (x < cam_x + BOSS_WIDTH * 2)
			AutoAttack(x + BOSS_WIDTH / 2, y);
		else
			AutoAttack(x - BOSS_WIDTH / 2, y);
	}
}

void CBoss::Reset()
{
	SetState(STATE_BOSS_SLEEP);
	SetPosition(startPosition.x, startPosition.y);
	vx = vy = 0;
}
