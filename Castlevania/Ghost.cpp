#include "Ghost.h"
#include"Game.h"

#include"Simon.h"
#include"Brick.h"

void CGhost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	float cam_x, cam_y;
	game->GetCamPos(cam_x, cam_y);

	if (this->x > cam_x + SCREEN_WIDTH || this->x < cam_x - ENEMY_GHOST_WIDTH || state == STATE_ENEMY_NOT_EXIST)
	{
		this->blood = 0;
	}
	if (this->blood > 0)
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
					item->SetPosition(this->x, this->y);
					item->Update(dt, &listBrick);
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

#pragma region Xu_ly_di_chuyen

		GhostMoving();

		CGameObject::Update(dt); // Update dt, dx, dy

		y += dy;
		x += dx;

#pragma endregion
		game = NULL;
		//DebugOut(L"Vi tri GHOST : %d, %d\n", (int)this->x, (int)this->y);
	}
}

void CGhost::Render()
{
	if (blood > 1 && animations.size() > 0)
	{
		animations[0]->RenderTrend(x, y, nx);
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

void CGhost::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state == STATE_ENEMY_EXIST)
	{
		left = x;
		top = y;
		right = x + ENEMY_GHOST_WIDTH;
		bottom = y + ENEMY_GHOST_HEIGHT;
	}
	else if (state == STATE_ENEMY_ITEM_EXIST)
	{
		item->GetPosition(x, y);
		item->GetBoundingBox(left, top, right, bottom);
	}
}

void CGhost::GhostMoving()
{
	if (autoGo == true)
	{
		//if (abs(this->x - target->x) > 20)
		if (CalculateDistance(D3DXVECTOR2(this->x, this->y), D3DXVECTOR2(target->x, target->y)) > 20)	// chỉ số tính toán
			autoGo = false;
	}
	else
	{

		if (abs(this->x - target->x) <= 5 && abs(this->y - (target->y + 5)) <= 5)	// các chỉ số thêm vào để ghost di chuyển đẹp hơn
		{
			autoGo = true;

			srand((unsigned)time(0));
			int signX = rand() & 1 ? -1 : 1;	// random -1, +1
			int signY = rand() & 1 ? -1 : 1;

			nx = signX;
			vx = nx * GHOST_SPEED_X;
			vy = signY * GHOST_SPEED_Y;
			
		}
		else // định hướng
		{
			if (this->x < target->x)
			{
				this->nx = 1;
				vx = nx * GHOST_SPEED_X;
			}
			else
			{
				this->nx = -1;
				vx = nx * GHOST_SPEED_X;
			}

			if (this->y < target->y + 5)
			{
				vy = GHOST_SPEED_Y;
			}
			else
			{
				vy = -GHOST_SPEED_Y;
			}
		}
	}
}

