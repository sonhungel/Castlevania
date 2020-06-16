#include <algorithm>
#include"Utils.h"

#include "Simon.h"
#include "Game.h"
#include"Torch.h"
#include"Whip.h"
#include"Brick.h"
#include"Knife.h"
#include"Axe.h"
#include"Portal.h"
#include"ItemMoney.h"

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
	stair_start = 0;
	subWeapon = eType::WEAPON_AXE;

	isBeingOnStair = false;
	isCanOnStair = 0;
	isAutoGo = false;
	_stairTrend = -1;
	auto_x = -1;
	//isHave3Direction = false;

	idScene_current = 1;
	idScene_next = 2;

	this->blood = MAX_BLOOD;
	_heart = 0;
	_score = 0;
	_live = 5;
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
	if (isAutoGo)
	{
		CalculateAutoGo();
		if (abs(auto_x - x) > 0.5f)
		{
			x += nx;
		}
		else
		{
			isAutoGo = false;
			
			if (isCanOnStair == 1)
			{
				state = STATE_SIMON_GO_UP;
				y = y - SIMON_PER_STEP;
				if (_stairTrend == -1)
				{
					x = x + SIMON_PER_STEP;
					nx = 1;
				}
				else
				{
					nx = -1;
					x = x - SIMON_PER_STEP;
				}
			}
			else if(isCanOnStair==-1)
			{
				state = STATE_SIMON_GO_DOWN;
				y = y + SIMON_PER_STEP;
				if (_stairTrend == -1)
				{
					nx = -1;
					x = x - SIMON_PER_STEP;
				}
				else
				{
					nx = 1;
					x = x + SIMON_PER_STEP;
				}
			}
			animations[ANI_SIMON_GO_UP]->ResetFrame();
			animations[ANI_SIMON_GO_DOWN]->ResetFrame();
			
		}
		return;
	}
	if (stair_start > 0)
	{
		if (GetTickCount() - stair_start > TIME_FOR_ONE_STEP)
		{
			stair_start = 0;
			if (isBeingOnStair)
			{
				if ((_stairTrend == -1 && nx == 1) || (_stairTrend == 1 && nx == -1))
					SetState(STATE_SIMON_IDLE_UP);
				else
					SetState(STATE_SIMON_IDLE_DOWN);
			}
			animations[ANI_SIMON_GO_UP]->ResetFrame();
			animations[ANI_SIMON_GO_DOWN]->ResetFrame();
		}
	}
	else
	{ 
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
			if (dynamic_cast<CBrick*>(coObjects->at(i)))
			{
				CBrick* brick = dynamic_cast<CBrick*>(coObjects->at(i));
				listBrick.push_back(brick);
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
					dx = -SIMON_SPEED_ON_STAIR;
					dy = SIMON_SPEED_ON_STAIR;
				}
				else  // stair right
				{
					nx = 1;
					dx = SIMON_SPEED_ON_STAIR;
					dy = SIMON_SPEED_ON_STAIR;
				}
			}
			else if (state == STATE_SIMON_GO_UP)
			{
				if (_stairTrend == -1)	// stair left
				{
					nx = 1;
					dx = SIMON_SPEED_ON_STAIR;
					dy = -SIMON_SPEED_ON_STAIR;
				}
				else  // stair right
				{
					nx = -1;
					dx = -SIMON_SPEED_ON_STAIR;
					dy = -SIMON_SPEED_ON_STAIR;
				}
			}
			else
			{
				dx = 0;
				dy = 0;
			}
		
		}

		// simple fall down
		else
		{
			CGameObject::Update(dt);
			vy += SIMON_GRAVITY * dt;
		}

		if (listHideObject.size() > 0)
			IsCanOnStair(listHideObject); // dùng để bắt đầu thang, còn việc phát hiện va chạm AABB là để kết thúc thang
		listHideObject.clear();


		if (state == STATE_SIMON_SIT_ATTACK || 
			state == STATE_SIMON_STAND_ATTACK||
			state==STATE_SIMON_GO_DOWN_ATTACK||
			state==STATE_SIMON_GO_UP_ATTACK)
		{
			//whip->Update(dt, coObjects);
			whip->SetPosition(x, y);
			whip->SetTrend(nx);
			whip->CollisionWithObject(dt, *coObjects);
		}

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		coEventsResult.clear();

		// turn off collision when die 
		//if (state != STATE_SIMON_DIE)
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

		}
		else// Xử lý collision for simon
		{
			
			float min_tx, min_ty, nx = 0, ny=0;
			float rdx = 1;
			float rdy = 1;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			// Khi đang trên thang thì va chạm sẽ k được xét tới nên sẽ k - lại số đơn vị tương tự cho phù hợp
			if (isBeingOnStair == true)
			{
				if (nx != 0) x -= nx * 0.3f;
				if (ny != 0) y -= ny * 0.3f;
				x += dx;
				y += dy;
			}
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
					CGame::GetInstance()->tagSwitchScene = portal->GetSceneId();
					idScene_current = CGame::GetInstance()->GetIDCurrentScene();
					idScene_next = portal->GetSceneId();
					if (idScene_next < idScene_current)
					{
						CGame::GetInstance()->tagGoBackScene = true;
					}
				}
				else if (dynamic_cast<CBrick*>(e->obj))
				{
					//DebugOut(L"passed brick\n");
					if (isBeingOnStair==false)
					{
						//DebugOut(L"Set va cham brick\n");
						//CBrick* brick = dynamic_cast<CBrick*>(e->obj);
						//listBrick.push_back(brick);
						CollisionWithBrick(dt, listBrick, min_tx, min_ty, nx, ny, rdx, rdy);
						listBrick.clear();
					}
					//else
					//{
					//	x += dx;
					//	y += dy;
					//}
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
					//DebugOut(L"Va cham ket thuc thang\n");
					CHidenObject* hidenObj = dynamic_cast<CHidenObject*>(e->obj);
					listHideObject.push_back(hidenObj);
					CollisionWithHidenObject(dt,listHideObject, min_tx, min_ty, nx, ny, rdx, rdy);
					listHideObject.clear();
				}
			}
		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		//for (UINT i = 0; i < coEventsResult.size(); i++) delete coEventsResult[i];
	}
	//DebugOut(L"Vi tri simon : %d, %d\n",(int)this->x,(int)this->y);
	//if (isBeingOnStair)
	//	DebugOut(L"Dang tren thang\n");
	//if(isHave3Direction)
	//	DebugOut(L"Dang o thang dac biet\n");
}

void CSimon::Render()
{
	int ani = 0;

	if (state == STATE_SIMON_DIE)
	{
		ani = ANI_SIMON_DIE;
	}
	else if (state == STATE_SIMON_IDLE)
	{
		if(isBeingOnStair==false)
			ani = ANI_SIMON_IDLE;
	}
	else if (state == STATE_SIMON_SIT)
	{
		ani = ANI_SIMON_SITTING;
	}
	else if (state == STATE_SIMON_JUMP)
	{
		if (isBeingOnStair == false)
		{
			if (vy < 0)
				ani = ANI_SIMON_JUMPING;
			else
				ani = ANI_SIMON_IDLE;
		}
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
	else if (state == STATE_SIMON_GO_DOWN_ATTACK)
	{
		if (isBeingOnStair)
		{
			ani = ANI_SIMON_GO_DOWN_ATTACK;
			whip->GetAnimation()->SetFrame(animations[ANI_SIMON_GO_DOWN_ATTACK]->GetCurrentFrame());
			whip->Render();
			
		}
	}
	else if (state == STATE_SIMON_GO_UP_ATTACK)
	{
		if (isBeingOnStair)
		{
			ani = ANI_SIMON_GO_UP_ATTACK;
			whip->GetAnimation()->SetFrame(animations[ANI_SIMON_GO_UP_ATTACK]->GetCurrentFrame());
			whip->Render();

		}
	}

	else if (state == STATE_SIMON_ATTACK_SUBWEAPON)
	{
		//if (subWeapon!=-1)
			ani = ANI_SIMON_STANDING_ATTACKING;
	}
	else if (trans_start > 0) {
		ani = ANI_SIMON_TRANS;
	}
	else if (isAutoGo)
	{
		ani = ANI_SIMON_WALKING;
	}
	else if (state == STATE_SIMON_IDLE_DOWN)
	{
		ani = ANI_SIMON_IDLE_DOWN;
	}
	else if (state == STATE_SIMON_IDLE_UP)
	{
		ani = ANI_SIMON_IDLE_UP;
	}
	else if (state == STATE_SIMON_GO_DOWN)
	{
		if (isBeingOnStair|| isCanOnStair == -1 )
			ani = ANI_SIMON_GO_DOWN;
		else
			ani = ANI_SIMON_SITTING;
	}
	else if (state = STATE_SIMON_GO_UP && isBeingOnStair)
	{
		//if(isCanOnStair == 1 )
		ani = ANI_SIMON_GO_UP;
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
	{}
	else if (animations[ANI_SIMON_SITTING_ATTACKING]->GetCurrentFrame() > 0)
	{}
	else if (animations[ANI_SIMON_GO_DOWN_ATTACK]->GetCurrentFrame() > 0)
	{}
	else if (animations[ANI_SIMON_GO_UP_ATTACK]->GetCurrentFrame() > 0)
	{}
	else if (trans_start > 0)
	{}
	else if(isAutoGo)
	{}
	else if (animations[ANI_SIMON_GO_UP]->GetCurrentFrame() > 1 && isBeingOnStair)
	{}
	else if (animations[ANI_SIMON_GO_DOWN]->GetCurrentFrame() > 1 && isBeingOnStair)
	{}
	//else if (animations[ANI_SIMON_JUMPING]->GetCurrentFrame() > 0)
	//{}
	else
	{
		CGameObject::SetState(state);
		switch (state)
		{
		case STATE_SIMON_WALKING_RIGHT:
			vx = SIMON_WALKING_SPEED;
			nx = SIMON_TREND_RIGHT;
			break;
		case STATE_SIMON_WALKING_LEFT:
			vx = -SIMON_WALKING_SPEED;
			nx = SIMON_TREND_LEFT;
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
		case STATE_SIMON_GO_UP_ATTACK:
			vx = 0;
			vy = 0;
			break;
		case STATE_SIMON_GO_DOWN_ATTACK:
			vx = 0;
			vy = 0;
			break;
		case STATE_SIMON_ATTACK_SUBWEAPON:
			vx = 0;
			if (subWeapon!=-1)
			{
				switch (subWeapon)
				{
				case eType::WEAPON_KNIFE:
				{
					CKnife* knife = CKnife::GetInstance();
					if (knife->GetState() == STATE_KNIFE_HIDE)
					{
						knife->SetState(STATE_KNIFE_APPEAR);
						knife->SetPosition(this->x, this->y);
						knife->SetTrend(nx);
					}
				}
					break;
				case eType::WEAPON_AXE:
				{
					CAxe* axe = CAxe::GetInstance();
					if (axe->GetState() == STATE_AXE_HIDE)
					{
						axe->SetTrend(nx);
						axe->SetPosition(this->x, this->y);
						axe->SetState(STATE_AXE_APPEAR);
					}
				}
				break;

				}
			}
			break;
		case STATE_SIMON_GO_UP:

			if (isBeingOnStair)
			{
				if (stair_start == 0)
				{
				}
				break;
			}
			if (isCanOnStair != 1)
			{
				vx = 0;
				this->state = STATE_SIMON_IDLE;
			}
			else
			{
				isBeingOnStair = true;
				if (abs(auto_x - x) > 0.5f)
					isAutoGo = true;
			}
			break;
		case STATE_SIMON_GO_DOWN:
			if (isBeingOnStair)
			{
				break;
			}
			if (isCanOnStair != -1)
			{
				vx = 0;
				this->state = STATE_SIMON_SIT;
			}
			else
			{
				isBeingOnStair = true;
				if (abs(auto_x - x) > 0.5f)
					isAutoGo = true;
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
			if (listObj.at(i)->getType() == eType::ITEM_HEARTBIG) // item heart Big
			{
				_heart += 10;
				trans_start = GetTickCount();
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
				
			}
			if (listObj.at(i)->getType() == eType::ITEM_WHIPUPGRADE)	// item whipUpgrade
			{
				trans_start = GetTickCount();
				whip->setUpLevel();
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
			}
			if (listObj.at(i)->getType() == eType::ITEM_KNIFE)	// item knife
			{
				trans_start = GetTickCount();
				//CKnife* knife = CKnife::GetInstance();
				subWeapon = eType::WEAPON_KNIFE;
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
			}
			if (listObj.at(i)->getType() == eType::ITEM_AXE)
			{
				trans_start = GetTickCount();
				subWeapon = eType::WEAPON_AXE;
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
			}
			if (listObj.at(i)->getType() == eType::ITEM_SMALLHEART)
			{
				trans_start = GetTickCount();
				//subWeapon = ID_WEAPON_AXE;
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
			}
			if (listObj.at(i)->getType() == eType::ITEM_RED_MONEY||
				listObj.at(i)->getType() == eType::ITEM_YELLOW_MONEY||
				listObj.at(i)->getType() == eType::ITEM_PURPLE_MONEY)
			{
				CItemMoney* item = dynamic_cast<CItemMoney*>(listObj.at(i));
				item->isEated = true;
				trans_start = GetTickCount();
				//subWeapon = ID_WEAPON_AXE;
				//listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
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

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	for (int i = 0; i < listHidenObj.size(); i++)
	{
		CHidenObject* hidenObj = dynamic_cast<CHidenObject*>(listHidenObj.at(i));// if e->obj is torch 
		
		if (hidenObj->GetState() == HIDENOBJECT_TYPE_STAIR_ABOVE 
			|| hidenObj->GetState() == HIDENOBJECT_TYPE_STAIR_BELOW
			|| hidenObj->GetState() == HIDENOBJECT_TYPE_SPECIAL)
		{
			if (isBeingOnStair)
			{
				isBeingOnStair = false;
				DebugOut(L"Ket thuc thang\n");
				state = ANI_SIMON_IDLE;
				
			}
			//IsCanOnStair(listHidenObj);
			auto_x = hidenObj->GetAutoX();
			if (hidenObj->GetState() == HIDENOBJECT_TYPE_STAIR_ABOVE)
			{
				isCanOnStair = -1;
			}
			if (hidenObj->GetState() == HIDENOBJECT_TYPE_STAIR_BELOW)
			{

				isCanOnStair = 1;
			}
			if (hidenObj->GetState() == HIDENOBJECT_TYPE_SPECIAL)
			{
				//isHave3Direction = true;
				//auto_x = hidenObj->GetAutoX();
				if (isGoDown)
				{
					_stairTrend = 1;
					isCanOnStair = -1;
				}
				if (isGoUp)
				{
					_stairTrend = -1;
					isCanOnStair = 1;
				}
				return;
			}
		}
		
		// xác định hướng của stair
		if (hidenObj->getNx() * hidenObj->getNy() > 0)
		{
			_stairTrend = 1;	// right
		}
		else
		{
			_stairTrend = -1;	// left
		}

	}
}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	//CGame *game = CGame::GetInstance();
	left = this->x;
	top = this->y;
	right = this->x + SIMON_WIDTH;
	bottom = this->y + SIMON_HEIGHT_STAND;
	if (state == STATE_SIMON_SIT 
		|| state == STATE_SIMON_SIT_ATTACK 
		||(animations[ANI_SIMON_JUMPING]->GetCurrentFrame() > 0))
		//|| (state == STATE_SIMON_GO_UP && state == STATE_SIMON_GO_DOWN))
	{
		bottom = this->y + SIMON_HEIGHT_SIT;
	}
}

void CSimon::IsCanOnStair(vector<LPGAMEOBJECT>& listObj)
{
	CGame* game = CGame::GetInstance();
	RECT rect, rect1;
	float l, t, r, b;
	float l1, t1, r1, b1;

	GetBoundingBox(l, t, r, b);
	rect.left = (int)l;
	rect.top = (int)t;
	rect.right = (int)r;
	rect.bottom = (int)b;

	for (int i = 0; i < listObj.size(); i++)
	{

		if (listObj.at(i)->GetState() == HIDENOBJECT_TYPE_STAIR_ABOVE 
			|| listObj.at(i)->GetState() == HIDENOBJECT_TYPE_STAIR_BELOW
			|| listObj.at(i)->GetState() == HIDENOBJECT_TYPE_SPECIAL)
		{
			listObj.at(i)->GetBoundingBox(l1, t1, r1, b1);
			rect1.left = (int)l1;
			rect1.top = (int)t1;
			rect1.right = (int)r1;
			rect1.bottom = (int)b1;
			if (CGame::GetInstance()->isCollision(rect, rect1)) // đụng độ
			{
				//DebugOut(L"Va cham doi tuong thang binh thuong\n");
				CHidenObject* hidenObj = dynamic_cast<CHidenObject*>(listObj.at(i));
				// xác định hướng của stair
				if (hidenObj->getNx() * hidenObj->getNy() > 0)
				{
					_stairTrend = 1;	// right
				}
				else
				{
					_stairTrend = -1;	// left
				}
				auto_x = hidenObj->GetAutoX();
				if (hidenObj->GetState() == HIDENOBJECT_TYPE_STAIR_ABOVE)
				{
					isCanOnStair = -1;
					return;
				}
				if (hidenObj->GetState() == HIDENOBJECT_TYPE_STAIR_BELOW)
				{
					isCanOnStair = 1;
					return;
				}
				if (hidenObj->GetState() == HIDENOBJECT_TYPE_SPECIAL)
				{
					if (isGoDown)
					{
						_stairTrend = 1;
						isCanOnStair = -1;
					}
					if (isGoUp)
					{
						_stairTrend = -1;
						isCanOnStair = 1;
					}
					//isHave3Direction = true;
					return;
				}
			}
		}
	}
	//isHave3Direction = false;
	isGoDown = false;
	isGoUp = false;
	auto_x = -1;
	isCanOnStair = 0;
	return;
}

void CSimon::CalculateAutoGo()
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


