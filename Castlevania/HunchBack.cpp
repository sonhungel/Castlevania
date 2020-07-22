#include "HunchBack.h"
#include"Brick.h"
#include"Simon.h"


void CHunchBack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	float cam_x, cam_y;
	game->GetCamPos(cam_x, cam_y);

	if (this->blood > 0 && this->x >= cam_x && this->x <= cam_x + SCREEN_WIDTH)
	{
		vector<LPGAMEOBJECT> listBrick;

		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CBrick*>(coObjects->at(i)))
			{
				listBrick.push_back(coObjects->at(i));
			}
		}
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
					
					item->Update(dt, &listBrick);
				}
			}
		}
		if (item != NULL && item->GetState() == STATE_ITEM_NOT_EXSIST)
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

#pragma region Collision

		
		if (state != STATE_ENEMY_EXIST)
			vx = 0;

		this->vy += ENEMY_GRAVITY * dt;

		CGameObject::Update(dt);




		if (x >= target->x)
			nx = -1;
		else
			nx = 1;
		item->SetPosition(this->x, this->y);

		Collision(&listBrick);

		
		
#pragma endregion

#pragma region Logic_move

		if (blood>1)
		{
			if (CalculateDistance(D3DXVECTOR2(this->x, this->y), D3DXVECTOR2(target->x, target->y)) <= DISTANCE_ACTIVE_HUNCHBACK)
				// Chờ simon vào bên trong phần distance Active
			{
				if (isWalk == false)
				{
					isWalk = true;
					SetStateTemp(STATE_ENEMY_HUNCHBACK_JUMP);
				}
			}

			if (stateTemp != STATE_ENEMY_HUNCHBACK_WAIT)
			{
				if (x < target->x)
				{
					if (abs(target->x - x) > DISTANCE_WALK)
					{
						if (isJump == false)
						{
							nx = 1;
						}
						SetStateTemp(STATE_ENEMY_HUNCHBACK_WALK);
					}
				}
				else if (x > target->x)
				{
					if (abs(target->x - x) > DISTANCE_WALK)
					{
						if (isJump == false)
						{
							nx = -1;
						}
						SetStateTemp(STATE_ENEMY_HUNCHBACK_WALK);
					}
				}

				if (rand() % 60 < 3)	// random hunch back jump tỉ lệ 0.05
				{
					if (isJump == false && (abs(target->x - x) < DISTANCE_WALK))
					{
						SetStateTemp(STATE_ENEMY_HUNCHBACK_JUMP);
					}
				}
			}
		}
	} 
#pragma endregion

	//DebugOut(L"Vi tri HUNCHBACK : %d, %d\n", (int)this->x, (int)this->y);
	//DebugOut(L"Vx, Vy HUNCHBACK : %d, %d\n", (int)this->vx, (int)this->vy);
	DebugOut(L"state HUNCHBACK : %d\n", (int)this->state);
	game = NULL;
}

void CHunchBack::Render()
{
	if (blood > 1 && animations.size() > 0)
	{
		if(stateTemp == STATE_ENEMY_HUNCHBACK_JUMP)
			animations[ENEMY_HUNCHBACK_ANI_JUMP]->RenderTrend(x, y, nx);
		else if (stateTemp == STATE_ENEMY_HUNCHBACK_WAIT|| stateTemp == STATE_ENEMY_HUNCHBACK_WALK)
			animations[ENEMY_HUNCHBACK_ANI_WAIT]->RenderTrend(x, y, nx);
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

void CHunchBack::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state == STATE_ENEMY_EXIST)
	{
		left = x;
		top = y;
		right = x + ENEMY_HUNCHBACK_WIDTH;
		bottom = y + ENEMY_HUNCHBACK_HEIGHT;
	}
	else if (state == STATE_ENEMY_ITEM_EXIST)
	{

		item->GetBoundingBox(left, top, right, bottom);
	}
}

void CHunchBack::SetStateTemp(int _state)
{
	if (_state == STATE_ENEMY_HUNCHBACK_WAIT)
	{
		this->stateTemp = _state;
		this->vx = 0;
		this->vy = 0;
	}
	else if (_state == STATE_ENEMY_HUNCHBACK_WALK)
	{
		this->stateTemp = _state;
		if (nx > 0)
			vx = HUNCHBACK_SPEED_X;
		else
			vx = -HUNCHBACK_SPEED_X;
		if (isOnGround)
		{
			vy = -HUNCHBACK_SPEED_Y / 2;
			isOnGround = false;
		}
	}
	else if (_state == STATE_ENEMY_HUNCHBACK_JUMP)
	{
		this->stateTemp = _state;
		isJump = true;
		isOnGround = false;
		vy = -HUNCHBACK_SPEED_Y;
	}
}

void CHunchBack::Collision(vector<LPGAMEOBJECT>* listBrick)
{

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(listBrick, coEvents);

	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0, rdx = 0,rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny,rdx,rdy);

		x += min_tx * dx + nx * 0.3f;
		y += min_ty * dy + ny * 0.3f;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj))
			{
				if (e->ny != 0)
				{
					if (e->ny == -1)
					{
						vy = 0;
						isOnGround = true;
						if (isJump == true)
						{
							isJump = false;
						}
					}
					else
					{
						if (isJump == true)
						{
							if (state == STATE_ENEMY_EXIST)
							{
								if (e->obj->y < target->y)
									SetStateTemp(STATE_ENEMY_HUNCHBACK_JUMP);
								y += dy;
							}
						}
						
					}
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}
