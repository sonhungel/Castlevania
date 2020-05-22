﻿#include <algorithm>
#include"Utils.h"

#include "Simon.h"
#include "Game.h"
#include"Torch.h"
#include"Whip.h"
#include"Brick.h"
#include"Knife.h"
#include"Portal.h"

CSimon* CSimon::__instance = NULL;

CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}

CSimon::CSimon()
{
	whip = CWhip::GetInstance();
	
	untouchable = 0;
	trans_start = 0;
	DirectionMoveOnStair;
	isBeingOnStair = false;
	typeStairSimonTouchFirst = 0;
	isAutoGo = false;
	_stairTrend = -1;
	auto_x = -1;
	/*
	CSimon::AddAnimation(400);		//0. idle left 
	CSimon::AddAnimation(401);		//1. walk left
	CSimon::AddAnimation(402);		//2. jump left
	CSimon::AddAnimation(403);		//3. sit left
	CSimon::AddAnimation(404);		//4. stand attack
	CSimon::AddAnimation(405);		//5. sit attack
	CSimon::AddAnimation(399);		//6. trans
	CSimon::AddAnimation(406);		//7. go up
	CSimon::AddAnimation(407);		//8. go down
	CSimon::AddAnimation(408);		//9. hurt
	CSimon::AddAnimation(409);		//10. idle up
	CSimon::AddAnimation(410);		//11. idle down
	*/
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (trans_start > 0)
	{
		vx = 0;
		if (GetTickCount() - trans_start > TRANSITION_TIME)
		{
			trans_start = 0;
		}
	}
	else if (isAutoGo)
	{
		AutoGo(); // xác định lại hướng simon cần di chuyển để phù hợp cho vị trí auto go
		if (abs(auto_x - x) > 0.5f)
		{
			x += nx;
		}
		else
		{
			isAutoGo = false;
		}
		return;
	}
	else
	{
		// Calculate dx, dy 
		//CGameObject::Update(dt);

		//vy += SIMON_GRAVITY * dt;

		vector<LPGAMEOBJECT> listTorch;
		vector<LPGAMEOBJECT> listBrick;
		vector<LPGAMEOBJECT> listHideObject;

		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CHidenObject*>(coObjects->at(i)))
			{
				CHidenObject* hidenObj = dynamic_cast<CHidenObject*>(coObjects->at(i));
				listHideObject.push_back(hidenObj);
			}
		}
		// xử lý phần stair
		if (isBeingOnStair)
		{
			if (state == STATE_SIMON_GO_DOWN)
			{
				if (_stairTrend == -1)	// stair left
				{
					nx = -1;
					dx = -2.0f;
					dy = 2.0f;
				}
				else  // stair right
				{
					nx = 1;
					dx = 2.0f;
					dy = 2.0f;
				}
			}
			else if (state == STATE_SIMON_GO_UP)
			{
				if (_stairTrend == -1)	// stair left
				{
					nx = 1;
					dx = 2.0f;
					dy = -2.0f;
				}
				else  // stair right
				{
					nx = -1;
					dx = -2.0f;
					dy = -2.0f;
				}
			}
			else
			{
				dx = 0;
				dy = 0;
			}
		}
		else
		{
			CGameObject::Update(dt);
			vy += SIMON_GRAVITY * dt;
		}

		//if (listHideObject.size() > 0)
		//	IsCanOnStair(listHideObject); // dùng để bắt đầu thang, còn việc phát hiện va chạm AABB là để kết thúc thang
		//listHideObject.clear();

		if (state == STATE_SIMON_SIT_ATTACK || state == STATE_SIMON_STAND_ATTACK)
		{
			
			whip->SetPosition(x, y);
			whip->SetTrend(nx);
			whip->CollisionWithObject(dt, *coObjects);
		}


		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		// turn off collision when die 
		if (state != STATE_SIMON_DIE)
			CalcPotentialCollisions(coObjects, coEvents);

		// reset untouchable timer if untouchable time has passed
		if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
		{
			untouchable_start = 0;
			untouchable = 0;
		}

		// No collision occured, proceed normally
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;

			auto_x = -1;
			DirectionMoveOnStair = 0;
		}
		else // Xử lý collision for simon
		{
			float min_tx, min_ty, nx = 0, ny=0;
			float rdx = 0;
			float rdy = 0;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		//
		// Collision logic with objects
		//

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CPortal*>(e->obj))
				{
					CPortal* portal = dynamic_cast<CPortal*>(e->obj);
					DebugOut(L"[INFO] Collision with portal\n");
					tagSwitchScene = portal->GetSceneId();
				}
				else if (dynamic_cast<CBrick*>(e->obj))
				{
					if (!isBeingOnStair)
					{
						CBrick* brick = dynamic_cast<CBrick*>(e->obj);
						listBrick.push_back(brick);

						CollisionWithBrick(dt, listBrick, min_tx, min_ty, nx, ny, rdx, rdy);
						listBrick.clear();
					}
					else
					{
						x += dx;
						y += dy;
					}
				}
				else if (dynamic_cast<CTorch*>(e->obj))
				{
					if (untouchable == 0)
					{
						CTorch* torch = dynamic_cast<CTorch*>(e->obj);
						listTorch.push_back(torch);
						CollisionWithTorch(dt, listTorch, min_tx, min_ty, nx, ny, rdx, rdy);
						listTorch.clear();
					}
				}
				else if (dynamic_cast<CHidenObject*>(e->obj))
				{
					DebugOut(L"Va cham thang\n");
					CHidenObject* hidenObj = dynamic_cast<CHidenObject*>(e->obj);
					listHideObject.push_back(hidenObj);
					CollisionWithHidenObject(dt,listHideObject, min_tx, min_ty, nx, ny, rdx, rdy);
					listHideObject.clear();

				}
			}
		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void CSimon::Render()
{
	int ani = 0;
	if (state == STATE_SIMON_DIE)
	{
		ani = ANI_SIMON_IDLE;
	}
	else if (state == STATE_SIMON_SIT)
	{
		ani = ANI_SIMON_SITTING;
	}
	else if (state == STATE_SIMON_JUMP)
	{
		if (vy < 0)
			ani = ANI_SIMON_JUMPING;
		else
			ani = ANI_SIMON_IDLE;
	}
	else if (state == STATE_SIMON_STAND_ATTACK)
	{
		ani = ANI_SIMON_STANDING_ATTACKING;
		whip->GetAnimation()->SetFrame(animations[ANI_SIMON_STANDING_ATTACKING]->GetCurrentFrame());
		whip->Render();
	}
	else if (state == STATE_SIMON_SIT_ATTACK)
	{
		whip->GetAnimation()->SetFrame(animations[ANI_SIMON_SITTING_ATTACKING]->GetCurrentFrame());
		ani = ANI_SIMON_SITTING_ATTACKING;
		whip->Render();
	}
	else if (state == STATE_SIMON_ATTACK_KNIFE)
	{
		if (subWeapon==true)
			ani = ANI_SIMON_STANDING_ATTACKING;
	}
	else if (trans_start > 0) {
		ani = ANI_SIMON_TRANS;
	}
	else if (state == STATE_SIMON_IDLE_DOWN)
	{
		id = ANI_SIMON_IDLE_DOWN;
	}
	else if (state == STATE_SIMON_IDLE_UP)
	{
		id = ANI_SIMON_IDLE_UP;
	}
	else if (state = STATE_SIMON_GO_UP && (DirectionMoveOnStair == 1 || isBeingOnStair))
	{
		id = ANI_SIMON_GO_UP;
	}
	else if (state == STATE_SIMON_GO_DOWN)
	{
		if (DirectionMoveOnStair = -1 || isBeingOnStair)
			id = ANI_SIMON_GO_DOWN;
		else
			id = ANI_SIMON_SITTING;
	}
	else {
		if (vx == 0)
		{
			if(state!=STATE_SIMON_SIT_ATTACK||state!=STATE_SIMON_STAND_ATTACK)
			ani = ANI_SIMON_IDLE;
		}
		else
		{
			ani = ANI_SIMON_WALKING;
		}
	}

	int alpha = 255;
	if (untouchable) alpha = 128;
	animations[ani]->RenderTrend(x, y, nx,alpha);

	RenderBoundingBox();
}


void CSimon::SetState(int state)
{
	if (animations[ANI_SIMON_STANDING_ATTACKING]->GetCurrentFrame() > 0)
	{
	}
	else if (animations[ANI_SIMON_SITTING_ATTACKING]->GetCurrentFrame() > 0)
	{
	}
	else if (trans_start > 0)
	{
	}
	else if (animations[ANI_SIMON_GO_UP]->GetCurrentFrame() > 0 && isBeingOnStair)
	{
	}
	else if (animations[ANI_SIMON_GO_DOWN]->GetCurrentFrame() > 0 && isBeingOnStair)
	{
	}
	else if (animations[ANI_SIMON_JUMPING]->GetCurrentFrame() > 0)
	{

	}
	else
	{
		CGameObject::SetState(state);
		switch (state)
		{
		case STATE_SIMON_WALKING_RIGHT:
			vx = SIMON_WALKING_SPEED;
			nx = 1;
			break;
		case STATE_SIMON_WALKING_LEFT:
			vx = -SIMON_WALKING_SPEED;
			nx = -1;
			break;
		case STATE_SIMON_SIT:
			vx = 0;
			break;
		case STATE_SIMON_JUMP:
			if (vy == 0) {
				vy = -SIMON_JUMP_SPEED_Y;
				//vx = 0;
			}
			break;
		case STATE_SIMON_UP:
			y -= 15;
		case STATE_SIMON_IDLE:
			vx = 0;
			break;
		case STATE_SIMON_STAND_ATTACK:
			vx = 0;
			break;
		case STATE_SIMON_SIT_ATTACK:
			vx = 0;
			break;
		case STATE_SIMON_ATTACK_KNIFE:
			vx = 0;
			if (subWeapon)
			{
				CKnife* knife = CKnife::GetInstance();
				if (knife->GetState() == STATE_KNIFE_HIDE)
				{
					knife->SetState(STATE_KNIFE_APPEAR);
					knife->SetPosition(x, y);
					knife->SetTrend(nx);
					knife->Render();
				}
			}
			break;
		case STATE_SIMON_GO_UP:
			if (isBeingOnStair)
				break;
			if (DirectionMoveOnStair != 1)
			{
				vx = 0;
				state = STATE_SIMON_IDLE;
			}
			else
			{
				isBeingOnStair = true;
				//if (abs(auto_x - x) > 0.5f)
					//isAutoGo = true;
			}
			break;
		case STATE_SIMON_GO_DOWN:
			if (isBeingOnStair)
				break;
			if (DirectionMoveOnStair != -1)
			{
				vx = 0;
				state = STATE_SIMON_SIT;
			}
			else
			{
				isBeingOnStair = true;
			}
			break;
		case STATE_SIMON_IDLE_UP:
			vx = vy = 0;
			break;
		case STATE_SIMON_IDLE_DOWN:
			vx = vy = 0;
			break;
		}
	}
	
}
void CSimon::CollisionWithItem(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	for (int i = 0; i < listObj.size(); i++)
	{
		if (listObj.at(i)->GetState() == STATE_ITEM_EXSIST)
		{
			if (listObj.at(i)->getType() == TYPE_ITEM_HEART) // item heart
			{
				trans_start = GetTickCount();
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
				
			}
			if (listObj.at(i)->getType() == TYPE_ITEM_WHIPUPGRADE)	// item whipUpgrade
			{
				trans_start = GetTickCount();
				whip->setUpLevel();
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
			}
			if (listObj.at(i)->getType() == TYPE_ITEM_KNIFE)	// item knife
			{
				trans_start = GetTickCount();
				CKnife* knife = CKnife::GetInstance();
				subWeapon = true;
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
			}
		}
	}
}

void CSimon::CollisionWithBrick(DWORD dt, vector<LPGAMEOBJECT>& listBrick, float min_tx0, float min_ty0, int nx0, int ny0, 
																										float rdx0, float rdy0)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != STATE_SIMON_DIE)
		CalcPotentialCollisions(&listBrick, coEvents);

	float min_tx, min_ty, nx = 0, ny;
	float rdx = 0;
	float rdy = 0;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

	//	if (rdy != 0 && rdy == dy)
		//x += ny * abs(rdy);
	
	// xử lý va chạm với birck theo chiều y để tránh bug logic
	// block 
	if (min_tx <= min_tx0)
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	if (min_ty <= min_ty0)
		y += min_ty * dy + ny * 0.4f;

	if (nx != 0)
		vx = 0;
	if (ny != 0)
		vy = 0;
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
}

void CSimon::CollisionWithTorch(DWORD dt, vector<LPGAMEOBJECT>& listTorch, float min_tx0, float min_ty0, int nx0, int ny0, float rdx0, float rdy0)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();


	CalcPotentialCollisions(&listTorch, coEvents);

	float min_tx, min_ty, nx = 0, ny;
	float rdx = 0, rdy = 0;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny,rdx,rdy);

	//// block 
	if (min_tx <= min_tx0)
		x += dx;
	if (min_ty <= min_ty0)
		y += dy;

	// clean up collision events
	
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	vector<LPGAMEOBJECT> listItem;
	for (UINT i = 0; i < listTorch.size(); i++)
	{
		CTorch* torch = dynamic_cast<CTorch*>(listTorch.at(i));	// Check torch is true??
		if (torch->GetState() == STATE_TORCH_EXSIST)
		{
		}
		else
		{
			if (dynamic_cast<CItem*>(torch->GetItem()))	// check					
			{
				CItem* item = dynamic_cast<CItem*>(torch->GetItem());
				listItem.push_back(item);
				torch->SetState(STATE_TORCH_ITEM_NOT_EXSIST);	// item was eated
			}
		}
	}
	CollisionWithItem(dt, listItem);
}

void CSimon::CollisionWithHidenObject(DWORD dt, vector<LPGAMEOBJECT>& listHidenObj, float min_tx0, float min_ty0, int nx0, int ny0, float rdx0, float rdy0)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();


	CalcPotentialCollisions(&listHidenObj, coEvents);

	float min_tx, min_ty, nx = 0, ny;
	float rdx = 0, rdy = 0;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

	//// block 
	if (min_tx <= min_tx0)
		x += dx;
	if (min_ty <= min_ty0)
		y += dy;
	//if (nx != 0) vx = 0;
	//if (ny != 0)vy = 0;

	for (UINT i = 0; i < listHidenObj.size(); i++)
	{
		CHidenObject* hidenObj = dynamic_cast<CHidenObject*>(listHidenObj.at(i));
		auto_x = hidenObj->GetAutoX();
		if (hidenObj->GetState() == HIDENOBJECT_TYPE_STAIR_ABOVE )
		{
			if (typeStairSimonTouchFirst==0)
			{
				typeStairSimonTouchFirst = HIDENOBJECT_TYPE_STAIR_ABOVE;
			}
			DirectionMoveOnStair = -1;	// go down
		}
		if (hidenObj->GetState() == HIDENOBJECT_TYPE_STAIR_BELOW)
		{
			if (typeStairSimonTouchFirst == 0)
			{
				typeStairSimonTouchFirst = HIDENOBJECT_TYPE_STAIR_BELOW;
			}
			DirectionMoveOnStair = 1;// go up
		}

		if (hidenObj->getNx() * hidenObj->getNy()>0)
		{
			_stairTrend = 1;	// stair right
		}
		else
		{
			_stairTrend = -1;	// stair left
		}
	}
}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = this->x;
	top = this->y;
	right = this->x + SIMON_WIDTH;
	bottom = this->y + SIMON_HEIGHT_STAND;
	if (state == STATE_SIMON_SIT 
		|| state == STATE_SIMON_SIT_ATTACK 
		||(animations[ANI_SIMON_JUMPING]->GetCurrentFrame() > 0)
		|| (state == STATE_SIMON_GO_UP && state == STATE_SIMON_GO_DOWN))
	{
		bottom = this->y + SIMON_HEIGHT_SIT;
	}
}

void CSimon::AutoGo()
{
	if (auto_x < x)
	{
		nx = -1;
	}
	else if (auto_x > x)
	{
		nx = 1;
	}
}

