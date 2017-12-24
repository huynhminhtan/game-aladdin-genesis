#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <ctime>
#include "Input.h"
#include "Graphics.h"
#include "../GameObjects/Camera.h"
#include "Timer.h"
#include "GameTime.h"
#include "define.h"

class Game
{
private:
	LPCWSTR _applicationName;
	float _fps;
	bool _isFullScreen;

	HINSTANCE _hInstance;
	HWND _hWnd;

	Input* _input;
	Graphics* _graphics;
	Timer* _timer;
	GameTime* _gametime;
	float _oldTime;
	float _deltaTime;
	float _frameRate;

	bool Frame(float detaTime);
	bool InitializeWindows(int &screenWidth, int &screenHeight);
	void ShutdownWindows();
public:
	Game(LPCWSTR applicationName = LPCWSTR(), float fps = 60, bool isFullScreen = false);
	~Game();

	bool Initialize();
	void Release();
	void Run();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

