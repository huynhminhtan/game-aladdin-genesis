#include <windows.h>
#include "CGame.h"
#include "CSceneOutside.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CGame game(hInstance, L"Keyboard sample", GAME_SCREEN_RESOLUTION_1024_640_24, 0, 60);

	game.Init();
	
	game.SetStartScene(new CSceneOutSide());

	game.Run();
	
	game.Terminate();
	
	return 0;
}


