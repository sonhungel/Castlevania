#include "Raven.h"
#include"Game.h"
#include"Define.h"



void CRaven::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	float cam_x, cam_y;
	game->GetCamPos(cam_x, cam_y);
	if (blood > 0 && this->x >= cam_x && this->x <= (cam_x + SCREEN_WIDTH))
	{
#pragma region Xu_Ly_Hieu_Ung&Item
		if (dt_die == 0)	// đo thời gian die
		{
			//if (this->state==STATE_ENEMY_BLACK_KNIGHT_NOT_EXIST)
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

		if (simon->x < this->x)
			nx = -1;
		else
			nx = 1;

		// Xử lý chờ trước khi xử lý di chuyển
		// phần này tăng độ chính xác với logic game gốc
		if (ravenActive==false &&dt_wait==0)
			dt_wait = GetTickCount();
		if (ravenActive == false && dt_wait > 0)
		{
			if (GetTickCount() - dt_wait > RAVEN_TIME_WAIT)
			{
				ravenActive = true;
				dt_wait = 0;
				stateTemp = STATE_ENEMY_RAVEN_FLY;
			}
		}

		if (ravenActive)
		{
			
			D3DXVECTOR2 ravenPosition = D3DXVECTOR2(x, y);

			if (isGettedPositionFirt == false)
			{
				RandomPositonFirst(targetFirst);
				isGettedPositionFirt = true;
			}

			if (ravenPosition == targetFirst)
			{
				if (dt_waitAttack == 0)
					dt_waitAttack = GetTickCount();
			}

			if (dt_waitAttack > 0)
			{
				if (GetTickCount() - dt_waitAttack > RAVEN_TIME_WAIT)
				{
					dt_waitAttack = 0;
					switchTargetToSimon = true;
				}
			}


			if (!switchTargetToSimon)
			{
				ravenPosition += Rada(targetFirst, ravenPosition, ENEMY_RAVEN_SPEED_NORMAL);
			}
			else
			{
				ravenPosition += Rada(D3DXVECTOR2(simon->x, simon->y-ENEMY_RAVEN_HEIGHT+20), ravenPosition, ENEMY_RAVEN_SPEED_BUFF);
			}

			x = ravenPosition.x;
			y = ravenPosition.y;

			CGameObject::Update(dt);

			//DebugOut(L"Vi tri RAVEN : %d, %d\n", (int)this->x, (int)this->y);
		}
	}
}

void CRaven::Render()
{
	if (blood > 1 && animations.size() > 0)
	{
		if (stateTemp == STATE_ENEMY_RAVEN_IDLE)
			animations[ENEMY_RAVEN_ANI_IDLE]->RenderTrend(x, y, nx);
		else if (stateTemp == STATE_ENEMY_RAVEN_FLY)
			animations[ENEMY_RAVEN_ANI_FLY]->RenderTrend(x, y, nx);
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

void CRaven::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state == STATE_ENEMY_EXIST)
	{
		left = x;
		top = y;
		right = x + ENEMY_RAVEN_WIDTH;
		bottom = y + ENEMY_RAVEN_HEIGHT;
	}
	else if (state == STATE_ENEMY_ITEM_EXIST)
	{
		item->GetPosition(x, y);
		item->GetBoundingBox(left, top, right, bottom);
	}
}

void CRaven::RandomPositonFirst(D3DXVECTOR2 & targetFirst)
{
	srand((unsigned)time(0));
	int signX = rand() & 1 ? -1 : 1;	// random -1, +1
	//int signY = rand() & 1 ? -1 : 1;

	targetFirst.x = simon->x + signX * DISTANCE_FROM_SIMON_TO_TARGET_FIRST;
	targetFirst.y = simon->y - ENEMY_RAVEN_HEIGHT+20; //+ signY * DISTANCE_FROM_SIMON_TO_TARGET_FIRST;
}

D3DXVECTOR2 CRaven::Rada(D3DXVECTOR2 raven, D3DXVECTOR2 target, float speedOfRaven)	// = quãng đường
{
	float distance = CalculateDistance(raven, target);
	if (distance < speedOfRaven)
		return raven-target;
	else
		return ( raven- target )*speedOfRaven / distance;	// trường hợp này thì x+ thêm = speedOfRaven

}

