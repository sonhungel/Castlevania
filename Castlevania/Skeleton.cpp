#include "Skeleton.h"
#include"Brick.h"

void CSkeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects )
{
	
	float cam_x, cam_y;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	if (this->blood > 0 && this->x >= cam_x && this->x <= cam_x + SCREEN_WIDTH)
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

		if (x >= target->x)
			nx = -1;
		else
			nx = 1;

		if (CalculateDistance(D3DXVECTOR2(this->x, this->y), D3DXVECTOR2(target->x, target->y))<DISTANCE_SKELETON_ACTIVE)
		{
			if (state_temp == STATE_ENEMY_SKELETON_IDLE)
				SetSkeletonState( STATE_ENEMY_SKELETON_ACTIVE);
		}
		Collision(coObjects);

		CGameObject::Update(dt);
		vy += ENEMY_SKELETON_GRAVITY * dt;

		if (isJump)
		{
			vy = -ENEMY_SKELETON_SPEED_Y;
			isJump = isCanJump = false;
		}

		// skeleton hoạt động theo cách di chuyển trong 1 khoảng nhất định từ simon nhưng sẽ k va chạm với simon để có thể bắn bone

		if (abs(x - target->x) > DISTANCE_SKELETON_WALK_TO_SIMON)	// Tiến tới simon
		{
			vx = ENEMY_SKELETON_SPEED_X * nx;
		}
		if (abs(x - target->x) < DISTANCE_SKELETON_WALK_OUT_OF_SIMON)	// Chuyển động tránh xa simon khi simon tiến lại gần
			//	=> vx sẽ phải đảo ngược lại 
		{
			vx = -ENEMY_SKELETON_SPEED_X * nx;
		}
	}
}

void CSkeleton::Render()
{
	if (blood > 1 && animations.size() > 0)
	{
		animations[0]->RenderTrend(x, y, nx);
		//DebugOut(L"Render black knight\n");
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

void CSkeleton::SetSkeletonState(int state)
{
	this->state_temp = state;
	switch (state)
	{
	case STATE_ENEMY_SKELETON_IDLE:
		vx = 0;
		vy = 0;
		break;
	case STATE_ENEMY_SKELETON_ACTIVE:
		break;
	}
}

void CSkeleton::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state == STATE_ENEMY_EXIST)
	{
		left = x;
		top = y;
		right = x + ENEMY_SKELETON_WIDTH;
		bottom = y + ENEMY_SKELETON_HEIGHT;
	}
	else if (state == STATE_ENEMY_ITEM_EXIST)
	{
		item->GetPosition(x, y);
		item->GetBoundingBox(left, top, right, bottom);
	}
}

void CSkeleton::Collision(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPGAMEOBJECT> listBrick;

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CBrick*>(coObjects->at(i)))
		{
			listBrick.push_back(coObjects->at(i));
		}
	}
	item->SetPosition(x, y);


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(&listBrick, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;

		if (isCanJump)
			isJump = true;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0, rdx = 0, rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.3f;
		y += min_ty * dy + ny * 0.2f;

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
						isCanJump = true;
					}
					else
						y += dy;
				}

				if (e->nx != 0)
				{
					vx = -vx;
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
	listBrick.clear();
}
