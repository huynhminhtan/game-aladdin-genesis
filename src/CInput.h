#pragma once

#include "Header.h"

#define KEY_DOWN(code) ( IsKeyDown(code) )

#define KEYBOARD_BUFFER_SIZE	1024

class CInput
{
public:
	CInput();
	~CInput();

	bool Init(HWND);
	void Release();
	void ProcessKeyBoard();
	int IsKeyDown(int);

	static CInput* GetInstance();
private:
	LPDIRECTINPUT8			_dinput;							// The DirectInput object         
	LPDIRECTINPUTDEVICE8	_KeyboardDevice;					// The keyboard device 
	BYTE					_KeyStates[256];					// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA		_KeyEvents[KEYBOARD_BUFFER_SIZE];	// Buffered keyboard data

	HWND					_hWnd;

	static CInput*			_instance;
};