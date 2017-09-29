#pragma once
#include <windows.h>

class CGame
{
	CGame();
	~CGame();

private:


public:
	init(HINSTANCE hInstance, HWND hWnd);
	gameRun();
	gameEnd();
}