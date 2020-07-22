#pragma once
#ifndef __PLAYSCENE_H_
#define __PLAYSCENE_H_
#include"Game.h"
#include"GameObject.h"
#include"Scene.h"
#include"Textures.h"
#include"Map.h"
#include"Board.h"
#include"Grid.h"

#include"Simon.h"
#include"Brick.h"
#include"Torch.h"
#include"Boss.h"
#include"EnemyZone.h"

#define TIME_KILL_ALL_ENEMY 1000


class CPlayScene:public CScene
{
protected:
	CSimon* simon;		
	CMap* map;
	CBoss* boss;
	int _xLeft, _xRight;		// Set cứng cam cho mỗi scene

	CBoard* HUD;
	CGrid* grid;

	DWORD start_killAllEnemy;

	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> coObjects; // dùng cho việc xử lý va chạm và render

	vector<LPGAMEOBJECT> listEnemy;	// chứa những enemy như black night, bat ,bla bla... ngoại trừ zombie

	vector<LPENEMYZONE> listEnemyZone;

	void _ParseSection_OBJECTS(string line);
	void _ParseSection_SETUP(string line);
	void _ParseSection_MAP(string line);
	void _ParseSection_CAMERA(string line);

public:

	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void UnLoad();
	virtual void Update(DWORD dt);
	virtual void Render();

	void KillAllEnemy() { start_killAllEnemy = GetTickCount(); }

	void GetEnemyOnScreen(vector<LPGAMEOBJECT>& listObject);

	//friend class CPlayScenceKeyHandler;
};



class CPlaySceneKeyHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) ;
	CPlaySceneKeyHandler(CScene* s) :CSceneKeyHandler(s) {};
};

#endif

