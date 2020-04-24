#pragma once
#ifndef __KEYEVENTHANDLER_H_
#define __KEYEVENTHANDLER_H_


#include <Windows.h>

/*
	Abstract class to define keyboard event handlers
*/
class CKeyEventHandler
{
public:
	virtual void KeyState(BYTE* state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
};
typedef CKeyEventHandler* LPKEYEVENTHANDLER;
#endif