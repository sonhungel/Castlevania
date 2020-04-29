#pragma once
#ifndef __SCENE_H_
#define __SCENE_H_

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include"Utils.h"
#include"KeyEventHandler.h"



class CScene
{
protected:
	CKeyEventHandler* key_handler;
	int id;	// scene id
	LPCWSTR sceneFilePath;
	//char* sceneFileNameXML;
	
public:
	CScene(int id, LPCWSTR filepath);

	CKeyEventHandler* GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void UnLoad() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};

typedef CScene* LPSCENE;

class CSceneKeyHandler:public CKeyEventHandler
{
protected:
	CScene* scene;
public:
	virtual void KeyState(BYTE* states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CSceneKeyHandler(CScene* s) :CKeyEventHandler() { scene = s; }

};

#endif