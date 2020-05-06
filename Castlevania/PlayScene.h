#pragma once
#ifndef __PLAYSCENE_H_
#define __PLAYSCENE_H_
#include"Game.h"
#include"GameObject.h"
#include"Scene.h"
#include"Textures.h"
#include"Map.h"
#include"Board.h"

#include"Simon.h"
#include"Brick.h"
#include"Torch.h"

#define ID_SCENE_MAP_1	1
#define ID_SCENE_MAP_2	2
#define ID_SCENE_MAP_3	3
#define ID_SCENE_MAP_4	4
#define ID_SCENE_MAP_5	5
#define ID_SCENE_MAP_6	6

class CPlayScene:public CScene
{
protected:
	CSimon* simon;		
	//CMap* map;
	CBoard* HUD;

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	// Bỏ qua animation_set
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);

public:
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void UnLoad();
	virtual void Update(DWORD dt);
	virtual void Render();

	CSimon* GetPlayer() { return simon; }

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

