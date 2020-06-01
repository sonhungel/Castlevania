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


class CPlayScene:public CScene
{
protected:
	CSimon* simon;		
	CMap* map;
	int _xLeft, _xRight;		// Set cứng cam cho mỗi scene
	CBoard* HUD;
	vector<LPGAMEOBJECT> singleToneObjects;
	vector<LPGAMEOBJECT> objects;
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

