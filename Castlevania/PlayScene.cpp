
#include <iostream>
#include <fstream>
#include "PlayScene.h"
#include"Game.h"

#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include"Knife.h"


CPlayScene::CPlayScene(int id, LPCWSTR filePath):CScene(id,filePath)
{
	key_handler = new CPlaySceneKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/



#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_OBJECTS	5

#define SCENE_SECTION_MAP	7

#define OBJECT_TYPE_SIMON	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_TORCH	2


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
	

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_SIMON:
		if (simon != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = CSimon::GetInstance();
		obj->SetPosition(x, y);
		simon = (CSimon*)obj;
		singleToneObjects.push_back(obj);
		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_TORCH: 
	{
		float item = atof(tokens[3].c_str());
		obj = new CTorch(item);
		obj->SetPosition(x, y);
		objects.push_back(obj); 
	}
		break;
	case OBJECT_TYPE_BRICK:
	{
		obj = new CBrick();
		obj->SetPosition(x,y);
		objects.push_back(obj);
			
	}
		break;
	case OBJECT_TYPE_PORTAL:
	{
		int scene_id = atoi(tokens[3].c_str());
		obj = new CPortal(x, y,  scene_id);
		objects.push_back(obj);
	}
		break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}
	
	singleToneObjects.push_back(CKnife::GetInstance());
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


void CPlayScene::Load()
{
	map = CMap::GetInstance();
	HUD = new CBoard();
	CSimon::GetInstance()->tagSwitchScene = -1;
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
		case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
		}
	}

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::UnLoad()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];
	// Không delete những obj singleton
	objects.clear();
	
	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that SIMON is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	// ==> update simon riêng

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	for (size_t i = 0; i < singleToneObjects.size(); i++)
	{
		singleToneObjects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (simon == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	simon->GetPosition(cx, cy);

	CGame* game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2+220;
	cy -= game->GetScreenHeight() / 2;

	//if (cx < 0) cx = 0; if (cx > 966) cx = 966;
	CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);

	HUD->Update(dt);

	if (simon->tagSwitchScene != -1)
	{
		CGame::GetInstance()->SwitchScene(simon->tagSwitchScene);
	}
}

void CPlayScene::Render()
{
	map->DrawMap();
	HUD->Render();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	for (int i = 0; i < singleToneObjects.size(); i++)
		singleToneObjects[i]->Render();
}

void CPlayScene::CameraDependMap(float& cx, float& cy)
{
	if (cx < 0) cx = 0; if (cx > 966) cx = 966;
}




#pragma region KeyHandler

void CPlaySceneKeyHandler::OnKeyUp(int KeyCode)
{
	CGame* game = CGame::GetInstance();
	CSimon* simon = ((CPlayScene*)scene)->GetPlayer();
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_DOWN:
		simon->SetState(STATE_SIMON_UP);
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
	CSimon* simon = ((CPlayScene*)scene)->GetPlayer();
	CGame* game = CGame::GetInstance();
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_Z:
		if (game->IsKeyDown(DIK_DOWN))
			simon->SetState(STATE_SIMON_SIT_ATTACK);
		else if (game->IsKeyDown(DIK_UP))
		{
			simon->SetState(STATE_SIMON_ATTACK_KNIFE);
		}
		else
			simon->SetState(STATE_SIMON_STAND_ATTACK);
		break;
	case DIK_X:
		break;
	case DIK_DOWN:
		break;
	}
}

void CPlaySceneKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CSimon* simon = ((CPlayScene*)scene)->GetPlayer();
	if (game->IsKeyDown(DIK_DOWN))
	{
		if (game->IsKeyDown(DIK_Z))
			simon->SetState(STATE_SIMON_SIT_ATTACK);
		else
			simon->SetState(STATE_SIMON_SIT);
	}
	//else if (game->IsKeyDown(DIK_Z))
	//{
	//	if (simon->GetState() == STATE_SIMON_SIT || simon->GetState() == STATE_SIMON_SIT_ATTACK)
	//		simon->SetState(STATE_SIMON_UP);
	//}
	else if (game->IsKeyDown(DIK_Z)&&game->IsKeyDown(DIK_DOWN))
	{
		simon->SetState(STATE_SIMON_SIT_ATTACK);
	}
	else if (game->IsKeyDown(DIK_X))
		simon->SetState(STATE_SIMON_JUMP);
	else if (game->IsKeyDown(DIK_RIGHT))
		simon->SetState(STATE_SIMON_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		simon->SetState(STATE_SIMON_WALKING_LEFT);
	else if (!game->IsKeyDown(DIK_DOWN) && !game->IsKeyDown(DIK_Z))
		simon->SetState(STATE_SIMON_IDLE);
}
#pragma endregion