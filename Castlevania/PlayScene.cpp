
#include <iostream>
#include <fstream>
#include "PlayScene.h"
#include"Game.h"

#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include"Knife.h"
#include"MapTexture.h"


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
#define SCENE_SECTION_MAP	6

#define OBJECT_TYPE_SIMON	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_TORCH	2


#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 4) return; // skip invalid lines - an object set must have at least id, x, y

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
		obj = new CSimon();
		obj->SetPosition(x, y);
		simon = (CSimon*)obj;
		//objects.push_back(obj);
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
		float map = atof(tokens[3].c_str());
		if (map == 1)
		{
			for (int i = 0; i < 96; i++)
			{
				obj = new CBrick();
				obj->SetPosition(i * 32, 360);
				objects.push_back(obj);
			}
		}
		if (map == 2)
		{
			for (int i = 0; i < 20; i++)
			{
				obj = new CBrick();
				obj->SetPosition(i * 32, 360);
				objects.push_back(obj);
			}
		}
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
	
	objects.push_back(CKnife::GetInstance());
}

void CPlayScene::_ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int IDMap = atoi(tokens[0].c_str());

	//map->SetMap(IDMap);
}


void CPlayScene::Load()
{
	//map = new CMap(CGame::GetInstance()->GetIdScene());
	HUD = new CBoard();
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

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
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
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_MAP:_ParseSection_MAP(line); break;
		}
	}

	
	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::UnLoad()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	simon = NULL;

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

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (simon == NULL) return;

	simon->Update(dt, &coObjects);
	// Update camera to follow mario
	float cx, cy;
	simon->GetPosition(cx, cy);

	CGame* game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2+220;
	cy -= game->GetScreenHeight() / 2;

	//if (cx < 0) cx = 0; if (cx > 966) cx = 966;
	CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
	HUD->Update(dt);
}

void CPlayScene::Render()
{
	//map->DrawMap();
	HUD->Render();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	simon->Render();
	
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