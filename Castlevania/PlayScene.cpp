
#include <iostream>
#include <fstream>
#include "PlayScene.h"
#include"Game.h"
#include"Define.h"

#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include"Knife.h"
#include"Axe.h"
#include"Effect.h"
#include"Boomerang.h"
#include"HollyWater.h"
#include"Platform.h"
#include"Candle.h"
#include"BreakBrick.h"
#include"Board.h"
#include"BlackKnight.h"
#include"Bat.h"
#include"Zombie.h"
#include"Ghost.h"
#include"HunchBack.h"
#include"Raven.h"
#include"Skeleton.h"

#define X_CAM_WHEN_BOSS_ACTIVE	1025


CPlayScene::CPlayScene(int id, LPCWSTR filePath):CScene(id,filePath)
{
	key_handler = new CPlaySceneKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/



#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_SETUP_STATE	4
#define SCENE_SECTION_OBJECTS	5
#define SCENE_SECTION_CAMERA	6
#define SCENE_SECTION_MAP	7

#define OBJECT_TYPE_SIMON	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_TORCH	2
#define OBJECT_TYPE_STAIR	3
#define OBJECT_TYPE_PLATFORM	4
#define OBJECT_TYPE_CANDLE		5
#define OBJECT_TYPE_BREAK_BRICK	6

#define OBJECT_TYPE_ENEMY_BLACK_KNIGHT	7
#define OBJECT_TYPE_ENEMY_ZOMBIE		8
#define OBJECT_TYPE_ENEMY_BAT			9
#define OBJECT_TYPE_ENEMY_GHOST			10
#define OBJECT_TYPE_ENEMY_HUNCH_BACK	11
#define OBJECT_TYPE_ENEMY_SKELETON		12
#define OBJECT_TYPE_ENEMY_RAVEN			13
#define OBJECT_TYPE_BOSS				14
#define OBJECT_TYPE_ENEMYZONE			15
#define OBJECT_TYPE_HIDEN_ACTIVE		16

#define	SETUP_TYPE_SIMON_NEXT_MAP	0
#define	SETUP_TYPE_SIMON_BACK_MAP	1


#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024
/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int grid_row = atoi(tokens[3].c_str());
	int grid_column = atoi(tokens[4].c_str());

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_SIMON:

		obj = CSimon::GetInstance();
		
		for (int i = 5; i < tokens.size(); i += 1)
		{
			int animation_id = atoi(tokens[i].c_str());
			obj->AddAnimation(animation_id);
			DebugOut(L"[INFO] added animation for SIMON: %d\n",animation_id);
		}
		obj->SetPosition(x, y);
		simon = (CSimon*)obj;
		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_TORCH: 
	{
		float item = atoi(tokens[6].c_str());

		obj = new CTorch(item,x,y);

		int animation_id = atoi(tokens[5].c_str());
		obj->AddAnimation(animation_id);
		
		//objects.push_back(obj); 
		grid->PushObjectToCell(obj, grid_row, grid_column);
	}
		break;
	case OBJECT_TYPE_BRICK:
	{
		int width = atoi(tokens[5].c_str());
		int height = atoi(tokens[6].c_str());
		obj = new CBrick(width,height);
		for (int i = 7; i < tokens.size(); i += 1)
		{
			int animation_id = atoi(tokens[i].c_str());
			obj->AddAnimation(animation_id);
		}
		obj->SetPosition(x, y);
		//objects.push_back(obj);
		grid->PushObjectToCell(obj, grid_row, grid_column);
	}
		break;
	case OBJECT_TYPE_PORTAL:
	{
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal( scene_id);
		obj->SetPosition(x, y);
		//objects.push_back(obj);
		grid->PushObjectToCell(obj, grid_row, grid_column);
	}
		break;
	case OBJECT_TYPE_STAIR:
	{
		int width = atoi(tokens[5].c_str());
		int height = atoi(tokens[6].c_str());
		int state = atoi(tokens[7].c_str());
		int nx = atoi(tokens[8].c_str());
		int ny = atoi(tokens[9].c_str());
		obj = new CHidenObject(x, y, width,height,state, nx, ny);
		//objects.push_back(obj); 
		grid->PushObjectToCell(obj, grid_row, grid_column);
	}
		break;
	case OBJECT_TYPE_PLATFORM:
	{
		int ani_id = atoi(tokens[5].c_str());
		int x_left = atoi(tokens[6].c_str());
		int x_right = atoi(tokens[7].c_str());
		obj = new CPlatform(ani_id,x_left,x_right);
		obj->SetPosition(x, y);
		//objects.push_back(obj);
		grid->PushObjectToCell(obj, grid_row, grid_column);
	}
		break;
	case OBJECT_TYPE_BREAK_BRICK:
	{
		int ani_id = atoi(tokens[5].c_str());
		int type_item = atoi(tokens[6].c_str());
		int x_item= atoi(tokens[7].c_str());
		int y_item= atoi(tokens[8].c_str());
		obj = new CBreakBrick(x, y,x_item,y_item, ani_id,type_item);
		//objects.push_back(obj);
		grid->PushObjectToCell(obj, grid_row, grid_column);
	}
		break;
	case OBJECT_TYPE_CANDLE:
	{
		int item = atoi(tokens[6].c_str());

		obj = new CCandle(item, x, y);

		int animation_id = atoi(tokens[5].c_str());
		obj->AddAnimation(animation_id);
		//objects.push_back(obj);
		grid->PushObjectToCell(obj, grid_row, grid_column);
	}
		break;
	case OBJECT_TYPE_ENEMY_BLACK_KNIGHT:
	{
		int type_item= atoi(tokens[3].c_str());

		int x_left= atoi(tokens[4].c_str());
		int x_right= atoi(tokens[5].c_str());

		obj = new CBlackKnight(x, y, type_item,x_left, x_right,simon);

		listEnemy.push_back(obj);
	}
		break;
	case OBJECT_TYPE_ENEMY_BAT:
	{
		int type_item = atoi(tokens[3].c_str());

		obj = new CBat(x, y, type_item,simon);
		listEnemy.push_back(obj);
	}
		break;
	case OBJECT_TYPE_HIDEN_ACTIVE:
	{
		int width = atoi(tokens[5].c_str());
		int height = atoi(tokens[6].c_str());
		int state = atoi(tokens[7].c_str());
		obj = new CHidenObject(x, y, width, height, state);
		//objects.push_back(obj);
		grid->PushObjectToCell(obj, grid_row, grid_column);
	}
		break;
	case OBJECT_TYPE_ENEMY_GHOST:
	{
		int type_item = atoi(tokens[3].c_str());

		obj = new CGhost(x, y, type_item,simon);
		listEnemy.push_back(obj);
	}
		break;
	case OBJECT_TYPE_ENEMY_HUNCH_BACK:
	{
		int type_item = atoi(tokens[3].c_str());

		obj = new CHunchBack(x, y, type_item, simon);
		listEnemy.push_back(obj);
	}
		break;
	case OBJECT_TYPE_ENEMY_RAVEN:
	{
		int type_item = atoi(tokens[3].c_str());

		obj = new CRaven(x, y, type_item,simon);
		listEnemy.push_back(obj);
	}
		break;
	case OBJECT_TYPE_ENEMY_SKELETON:
	{
		int type_item = atoi(tokens[3].c_str());

		obj = new CSkeleton(x, y, type_item,simon);
		listEnemy.push_back(obj);
	}
		break;
	case OBJECT_TYPE_BOSS:
	{
		obj = new CBoss(x,y);
		HUD->SetBossToHUD(obj);
		listEnemy.push_back(obj);
	}
		break;
	case OBJECT_TYPE_ENEMYZONE:
	{
		int width = atoi(tokens[5].c_str());
		int height = atoi(tokens[6].c_str());
		int numberOfZombie = atoi(tokens[7].c_str());
		CEnemyZone *enemyzone=new CEnemyZone(x, y, width, height, numberOfZombie);
		listEnemyZone.push_back(enemyzone);
		//grid->PushObjectToCell(obj, grid_row, grid_column);
	}
		break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}
	
}

void CPlayScene::_ParseSection_SETUP(string line)
{
	vector<string> tokens = split(line);
	CGame* game = CGame::GetInstance();

	if (tokens.size() < 2) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	int isBeingOnStair = atoi(tokens[1].c_str());
	int stairTrend = atoi(tokens[2].c_str());
	int nx = atoi(tokens[3].c_str());
	float x = atof(tokens[4].c_str());
	float y = atof(tokens[5].c_str());

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case SETUP_TYPE_SIMON_NEXT_MAP:
		CSimon::GetInstance()->SetBeingOnStair(isBeingOnStair);
		CSimon::GetInstance()->SetStairTrend(stairTrend);
		CSimon::GetInstance()->SetTrend(nx);
		CSimon::GetInstance()->SetPosition(x, y);
		break;
	case SETUP_TYPE_SIMON_BACK_MAP:
		if (game->tagGoBackScene)
		{
			CSimon::GetInstance()->SetBeingOnStair(isBeingOnStair);
			CSimon::GetInstance()->SetStairTrend(stairTrend);
			CSimon::GetInstance()->SetTrend(nx);
			CSimon::GetInstance()->SetPosition(x, y);
			game->tagGoBackScene = false;
		}
		break;
	}
}

void CPlayScene::_ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 4) return; // skip invalid lines
	wstring filePath = ToWSTR(tokens[0]);
	int row = atoi(tokens[2].c_str());
	int column = atoi(tokens[1].c_str());
	int index = atoi(tokens[3].c_str());
	int align = atoi(tokens[4].c_str());
	map->SetValueInMap(row, column, index, align);
	map->LoadMap(filePath);
}

void CPlayScene::_ParseSection_CAMERA(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 2)return;	// skip invalid lines
	_xLeft = atoi(tokens[0].c_str());
	_xRight = atoi(tokens[1].c_str());
}


void CPlayScene::Load()
{
	_xLeft = _xRight = -1;
	map = CMap::GetInstance();
	HUD = CBoard::GetInstance();
	grid = new CGrid();

	CGame::GetInstance()->tagSwitchScene = -1;

	DebugOut(L"[INFO] Start loading scene resources from : %s \n",sceneFilePath );

	ifstream f;
	f.open(sceneFilePath);
	
	// current resource section flag
	
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line=="[SETUP]")
		{
			section = SCENE_SECTION_SETUP_STATE; continue;
		}
		if (line == "[CAMERA]")
		{
			section = SCENE_SECTION_CAMERA; continue;
		}
		if (line == "[MAP]")
		{
			section = SCENE_SECTION_MAP; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{

		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_SETUP_STATE:_ParseSection_SETUP(line); break;
		case SCENE_SECTION_CAMERA:_ParseSection_CAMERA(line); break;
		case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
		}
	}

	

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::UnLoad()
{
	//for (int i = 0; i < objects.size(); i++)
	//	delete objects[i];
	
	for (int i = 0; i < listEnemy.size(); i++)
		delete listEnemy[i];

	for (int i = 0; i < listEnemyZone.size(); i++)
		delete listEnemyZone[i];

	//objects.clear();

	coObjects.clear();

	listEnemyZone.clear();

	listEnemy.clear();

	simon = NULL;		//  obj này không delete vì là singleton

	delete grid;
	grid = NULL;
	
	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{

	// ==> update simon riêng

	coObjects.clear();

	float cx, cy;

	//grid->ResetOnCamera(objects);

	CGame::GetInstance()->GetCamPos(cx, cy);

	grid->GetListObject(coObjects,cx,cy);	// Lấy những obj ở trong cam

	for (UINT i = 0; i < listEnemyZone.size(); i++)
	{
		listEnemyZone[i]->Update(dt);
		listEnemyZone[i]->GetEnemy(coObjects);
	}

	GetEnemyOnScreen(coObjects);

	if (start_freeze == 0)
	{
		for (size_t i = 0; i < coObjects.size(); i++)
		{
			coObjects[i]->Update(dt, &coObjects);
		}
	}

	// những enemy khác zombie được ghét từ trong này
	

	simon->Update(dt, &coObjects);

	CSimon::GetInstance()->GetPosition(cx, cy);

	cx -= SCREEN_WIDTH / 2 - 40;
	cy = 0;

	if (cx < _xLeft) cx = _xLeft; if (cx >_xRight ) cx = _xRight;
	// K có scene ngầm dưới lòng đất nên k cần xây dựng limit cam Y

	if (CBoss::IsActive())
		cx = X_CAM_WHEN_BOSS_ACTIVE;

	CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);

	//DebugOut(L"Cam pos : %f\n", cx);
	HUD->Update(dt);

	if (HUD->GetTime() == 0)
	{
		simon->blood = 0;
	}

	if (simon != NULL && start_reload == 0)
	{
		if (simon->GetState() == STATE_SIMON_DIE)
			start_reload = GetTickCount();
	}
	else//if (start_reload > 0)
	{
		if (GetTickCount() - start_reload > TIME_RELOAD)
		{
			CGame::GetInstance()->tagSwitchScene = CGame::GetInstance()->GetIDCurrentScene();
			simon->blood = MAX_BLOOD;
			simon->SetState(STATE_SIMON_IDLE);
			simon->isSimonOnAir = false;
			start_reload = 0;
			HUD->SetTime(TIME_MAX);
		}
	}

	// freeze	- item clock
	if (simon->is_freeze_enemy == true)
	{
		start_freeze = GetTickCount();
		simon->is_freeze_enemy = false;
	}
	if (start_freeze > 0)
	{
		if (GetTickCount() - start_freeze > TIME_FREEZE_ENEMY)
		{
			start_freeze = 0;
		}
	}

	// Cross

	if (CGame::GetInstance()->tagSwitchScene != -1)
	{
		CGame::GetInstance()->SwitchScene(CGame::GetInstance()->tagSwitchScene);
	}
	
	if (CSimon::GetInstance()->isKillAllEnemy == true)
	{
		KillAllEnemy();
		for (UINT i = 0; i < coObjects.size(); i++)
		{
			if (dynamic_cast<CEnemy*>(coObjects.at(i)))
			{
				coObjects.at(i)->blood = 0;
			}
		}
		CSimon::GetInstance()->isKillAllEnemy = false;
	}

	if (start_killAllEnemy > 0)
	{
		if (GetTickCount() - start_killAllEnemy > TIME_KILL_ALL_ENEMY)
		{
			start_killAllEnemy = 0;
			CGame::GetInstance()->BACKGROUND_COLOR = BACKGROUND_COLOR_DEFAULT;
		}
		else
		{
			if ((GetTickCount() - start_killAllEnemy) % 4 == 0)
			{
				if (CGame::GetInstance()->BACKGROUND_COLOR == BACKGROUND_COLOR_DEFAULT)
				{
					CGame::GetInstance()->BACKGROUND_COLOR = BACKGROUND_COLOR_CROSS;
				}
				else
				{
					CGame::GetInstance()->BACKGROUND_COLOR = BACKGROUND_COLOR_DEFAULT;
				}
			}
		}
	}

}

void CPlayScene::Render()
{
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	map->DrawMap(cx,cy);
	HUD->Render();
	
	for (int i = 0; i < coObjects.size(); i++)
		coObjects[i]->Render();

	for (UINT i = 0; i < listEnemyZone.size(); i++)
	{
		listEnemyZone[i]->Render();
	}

	simon->Render();

}

void CPlayScene::GetEnemyOnScreen(vector<LPGAMEOBJECT>& listObject)
{
	float cam_x, cam_y;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	for (UINT i = 0; i < listEnemy.size(); i++)
	{
		if (listEnemy.at(i)->blood > 0 && listEnemy.at(i)->x >= cam_x - ENEMY_ZOMBIE_WIDTH && listEnemy.at(i)->x <= cam_x + SCREEN_WIDTH && listEnemy.at(i)->y <= SCREEN_HEIGHT)
		{
			listObject.push_back(listEnemy.at(i));
			if (dynamic_cast<CSkeleton*>(listEnemy.at(i)))
			{
				CSkeleton* skeleton = dynamic_cast<CSkeleton*>(listEnemy.at(i));
				skeleton->GetListBone(listObject);
			}
		}
		else if(listEnemy.at(i)->blood<=0|| listEnemy.at(i)->y > SCREEN_HEIGHT)
		{
			delete listEnemy.at(i);
			listEnemy.erase(listEnemy.begin() + i);
		}
		
	}
}


#pragma region KeyHandler

void CPlaySceneKeyHandler::OnKeyUp(int KeyCode)
{
	CGame* game = CGame::GetInstance();
	CSimon* simon = CSimon::GetInstance();
	if (simon->GetState() == STATE_SIMON_DIE)
		return;
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	if (simon->IsAttacking())
		return;
	switch (KeyCode)
	{
	case DIK_DOWN:
		if (!simon->IsBeingOnStair())
			simon->SetState(STATE_SIMON_UP);
		break;
	case DIK_Z:
		if (simon->GetState() == STATE_SIMON_SIT_ATTACK)
	{
		if (game->IsKeyDown(DIK_DOWN))
			simon->SetState(STATE_SIMON_SIT);
		else 
			simon->SetState(STATE_SIMON_UP);
	}
	break;
	}
}


void CPlaySceneKeyHandler::OnKeyDown(int KeyCode)
{
	CSimon* simon = CSimon::GetInstance();
	CGame* game = CGame::GetInstance();
	CBoard* HUD = CBoard::GetInstance();

	if (simon->GetState() == STATE_SIMON_DIE)
		return;
	if (simon->GetIsAutoGo())
		return;
	//if (simon->isSimonOnAir)
		//return;
	//if (simon->GetState()==STATE_SIMON_SIT_ATTACK)
		//return;
	
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	if (simon->IsAttacking())
		return;

	switch (KeyCode)
	{
	case DIK_2:
		game->tagSwitchScene = 2;
		break;
	case DIK_3:
		game->tagSwitchScene = 3;
		break;
	case DIK_4:
		game->tagSwitchScene = 4;
		break;
	case DIK_5:
		game->tagSwitchScene = 5;
		break;
	case DIK_6:
		game->tagSwitchScene = 6;
		break;

	case DIK_X:
		break;
	case DIK_Q:
		HUD->ChangeWeapon();
		break;
	case DIK_W:
		CWhip::GetInstance()->setUpLevel();
		break;
	case DIK_A:
		HUD->SetBossDeadth();
		break;
	case DIK_S:
		simon->isKillAllEnemy = true;
		break;
	case DIK_F:
		simon->blood = MAX_BLOOD;
		break;
	case DIK_D:
		simon->blood = 0;
		break;
	case DIK_R:
		simon->is_freeze_enemy = true;
		break;
	case DIK_E:
		simon->SetSimonDisappear();
		break;
	case DIK_C:
		simon->PlusHeart();
		break;
	case DIK_Z:
	{
		CWhip::GetInstance()->GetAnimation()->ResetFrame();
		if (simon->IsBeingOnStair())
		{
			if (simon->GetStairTrend() == 1)
			{
				if (simon->GetTrend() == 1)
				{
					simon->SetState(STATE_SIMON_GO_DOWN_ATTACK);
				}
				else if (simon->GetTrend() == -1)
				{
					simon->SetState(STATE_SIMON_GO_UP_ATTACK);
				}
			}
			else if (simon->GetStairTrend() == -1)
			{
				if (simon->GetTrend() == 1)
				{
					simon->SetState(STATE_SIMON_GO_UP_ATTACK);
				}
				else if (simon->GetTrend() == -1)
				{
					simon->SetState(STATE_SIMON_GO_DOWN_ATTACK);
				}
			}
		}
		else
		{
			if (game->IsKeyDown(DIK_DOWN)||simon->isSimonOnAir)
			{
				if (!simon->IsAttacking())
					simon->SetState(STATE_SIMON_SIT_ATTACK);
			}
			else if (!game->IsKeyDown(DIK_DOWN))
			{
				if (simon->GetState() == STATE_SIMON_SIT || simon->GetState() == STATE_SIMON_SIT_ATTACK)
				{
					simon->SetState(STATE_SIMON_UP);
				}
				else if ((simon->GetState() == STATE_SIMON_IDLE || simon->GetState() == STATE_SIMON_WALKING_LEFT || simon->GetState() == STATE_SIMON_WALKING_RIGHT) && !simon->IsAttacking())
					simon->SetState(STATE_SIMON_STAND_ATTACK);
			}
		}
	}
		break;
	case DIK_DOWN:
	{
		if (simon->isSimonOnAir == false&&!game->IsKeyDown(DIK_Z))
		{
			//if (simon->GetState() == STATE_SIMON_SIT || simon->GetState() == STATE_SIMON_SIT_ATTACK)
			//{
				//simon->SetState(STATE_SIMON_UP);
			//}
			//else
				simon->SetState(STATE_SIMON_GO_DOWN);
			simon->isGoDown = true;
		}
	}
		break;
	case DIK_UP:
	{
		if (simon->isSimonOnAir == false && !game->IsKeyDown(DIK_Z))
		{
			simon->SetState(STATE_SIMON_GO_UP);
			simon->isGoUp = true;
		}
	}
		break;
	case DIK_LEFT:
		if(!simon->IsAttacking())
			simon->SetTrend(SIMON_TREND_LEFT);
		break;
	case DIK_RIGHT:
		if (!simon->IsAttacking())
			simon->SetTrend(SIMON_TREND_RIGHT);
		break;
	}

}

void CPlaySceneKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CSimon* simon = CSimon::GetInstance();

	if (simon->GetState() == STATE_SIMON_DIE)
		return;
	if (simon->GetIsAutoGo())
		return;
	if (simon->isSimonOnAir == true||simon->IsAttacking())
		return;
	

	if (game->IsKeyDown(DIK_Z) && game->IsKeyDown(DIK_UP) && simon->isCanAttack == true 
			&& !simon->IsBeingOnStair()&& simon->GetHeart()>0&&simon->subWeapon!=0)
	{
		if (simon->subWeapon != eType::WEAPON_CLOCK)
		{
			simon->SetState(STATE_SIMON_ATTACK_SUBWEAPON);
			simon->isUseSubWeapon += 1;
		}
		else
		{
			simon->is_freeze_enemy = true;
			simon->subWeapon = 0;
		}
	}
	else if (game->IsKeyDown(DIK_X) && simon->GetState() != STATE_SIMON_SIT&&simon->IsBeingOnStair()==false)
		simon->SetState(STATE_SIMON_JUMP);
	else if (game->IsKeyDown(DIK_RIGHT) && !game->IsKeyDown(DIK_DOWN)&&!game->IsKeyDown(DIK_Z))
	{
		if(simon->IsBeingOnStair())
		{
			if (simon->GetStairTrend() == 1)
			{
				simon->SetState(STATE_SIMON_GO_DOWN);
			}
			else
			{
				simon->SetState(STATE_SIMON_GO_UP);
			}
		}
		else if (!simon->IsAttacking())
		{
			if (simon->GetState() == STATE_SIMON_SIT||simon->GetState() == STATE_SIMON_SIT_ATTACK)
			{
				simon->SetState(STATE_SIMON_UP);
			}
			else 
				simon->SetState(STATE_SIMON_WALKING_RIGHT);
		}
	}
	else if (game->IsKeyDown(DIK_LEFT)&&!game->IsKeyDown(DIK_DOWN) && !game->IsKeyDown(DIK_Z))
	{
		if (simon->IsBeingOnStair())
		{
			if (simon->GetStairTrend() == -1)
			{
				simon->SetState(STATE_SIMON_GO_DOWN);
			}
			else
			{
				simon->SetState(STATE_SIMON_GO_UP);
			}
		}
		else if (!simon->IsAttacking())
		{
			if (simon->GetState() == STATE_SIMON_SIT || simon->GetState() == STATE_SIMON_SIT_ATTACK)
			{
				simon->SetState(STATE_SIMON_UP);
			}
			else 
				simon->SetState(STATE_SIMON_WALKING_LEFT);
		}
	}
	else if (game->IsKeyDown(DIK_UP))
	{
		simon->SetState(STATE_SIMON_GO_UP);
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		simon->SetState(STATE_SIMON_GO_DOWN);
	}
	else if (!game->IsKeyDown(DIK_DOWN) && !game->IsKeyDown(DIK_Z))
	{
		if (simon->IsBeingOnStair())
		{
			if ((simon->GetStairTrend() == -1 && simon->GetTrend() == 1) || (simon->GetStairTrend() == 1 && simon->GetTrend() == -1))
				simon->SetState(STATE_SIMON_IDLE_UP);
			else
				simon->SetState(STATE_SIMON_IDLE_DOWN);
		}
		else if (simon->GetState() == STATE_SIMON_SIT || simon->GetState() == STATE_SIMON_SIT_ATTACK)
			simon->SetState(STATE_SIMON_UP);
		else  
			simon->SetState(STATE_SIMON_IDLE);
	}
	
}
#pragma endregion