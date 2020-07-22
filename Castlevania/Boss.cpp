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
		if (state == STATE_BOSS_IDLE )
		{
			if (abs(CSimon::GetInstance()->x - this->x) < 100)
			{
				SetState(STATE_BOSS_ACTIVE);
			}
			else return;
		}

		if (GetTickCount() - attackTime > BOSS_ATTACK_TIME_WAITING)	//enemy fire
		{
			attackTime = 0;
			isFlying = true;
			startAttack();
			flyToSimonPercent = rand() % 3 + 1; // ==1 thi flytosimon
			if (flyToSimonPercent == 1)
			{
				CSimon::GetInstance()->GetPosition(position0.x, position0.y);
			}
			else
			{
				RandomNewPosition();
			}

		}

		if (isFlying)
		{
			if (this->x > position0.x) vx = -0.15f;
			else vx = 0.15f;
			if (this->y > position0.y) vy = -0.15f;
			else vy = 0.15f;
			FlyToTarget(dt, position0);
		}
	}
}

void CBoss::Render()
{
	if (blood > 1 && animations.size() > 0)
	{
		if (state == STATE_BOSS_IDLE)
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

void CBoss::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case STATE_BOSS_IDLE:
		vx = 0;
		vy = 0;
		break;
	case STATE_BOSS_ACTIVE:
		float yCam;
		CGame::GetInstance()->GetCamPos(xCam, yCam);
		vx = 0.1f;
		vy = 0.05f;
		startAttack();
		break;
	case STATE_BOSS_FLY_AWAY:
		RandomNewPosition();
		isFlying = true;
		attackTime = 0;
		break;
	default:
		break;
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
		left = x+35;
		top = y;
		right = left + BOSS_WIDTH;
		bottom = y + BOSS_HEIGHT;
	}
}

void CBoss::FlyToTarget(DWORD dt, D3DXVECTOR2 target)
{
	x += vx * dt;
	y += vy * dt;

	if (abs(x - target.x) <= 1.0f && abs(y - target.y) <= 1.0f)
	{
		isFlyToTarget = false;
		this->SetPosition(target.x, target.y);
		isFlying = false;
	}
}

void CBoss::Flying(DWORD dt)
{
	flyToSimonPercent = rand() % 3 + 1; // ==1 thi flytosimon

	if (flyToSimonPercent == 1)
	{
		CSimon::GetInstance()->GetPosition(simonPostion.x, simonPostion.y);
		FlyToTarget(dt, simonPostion);
	}
	else
	{
		RandomNewPosition();
		FlyToTarget(dt, position0);
	}
}

void CBoss::RandomNewPosition()
{

	srand(time(NULL));
	position0.x = rand() % (SCREEN_WIDTH - BOSS_WIDTH) + xCam;
	position0.y = rand() % (SCREEN_HEIGHT - 160) + 80;
}

D3DXVECTOR2 CBoss::Rada(D3DXVECTOR2 boss, D3DXVECTOR2 target, float speedOfRaven)
{
	float distance = CalculateDistance(boss, target);
	if (distance < speedOfRaven)
		return boss - target;
	else
		return (boss - target) * speedOfRaven / distance;	// trường hợp này thì x+ thêm = speedOfRaven
}

