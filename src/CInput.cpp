#include "CInput.h"

CInput* CInput::_instance = nullptr;

CInput::CInput()
{
	_dinput = nullptr;
	_KeyboardDevice = nullptr;
}

CInput::~CInput()
{
}

bool CInput::Init(HWND hwnd)
{
	_hWnd = hwnd;

	HRESULT hr;

	hr = DirectInput8Create
	(
		GetModuleHandle(NULL), // function get HINSTANCE current (_hInstance)
		DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&_dinput,
		NULL
	);

	// TO-DO: put in exception handling
	if (hr != DI_OK) return false;

	trace(L"DirectInput has been created");

	hr = _dinput->CreateDevice(GUID_SysKeyboard, &_KeyboardDevice, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK) return false;

	trace(L"DirectInput keyboard has been created");

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = _KeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

	trace(L"SetDataFormat for keyboard successfully");

	hr = _KeyboardDevice->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	trace(L"SetCooperativeLevel for keyboard successfully");

	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	trace(L"SetProperty for keyboard successfully");

	hr = _KeyboardDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hr != DI_OK) return false;

	hr = _KeyboardDevice->Acquire();
	if (hr != DI_OK) return false;

	trace(L"Keyboard has been acquired successfully");

	return true;
}

void CInput::Release()
{
	if (_KeyboardDevice)
	{
		_KeyboardDevice->Unacquire();
		_KeyboardDevice->Release();
	}

	if (_dinput) _dinput->Release();
}

void CInput::ProcessKeyBoard()
{
	// Collect all key states first
	// Is state 
	_KeyboardDevice->GetDeviceState(sizeof(_KeyStates), _KeyStates);

	//////////////////////////
	// Collect all buffered events
	// Is event
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT hr = _KeyboardDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0);

	// Scan through all data, check if the key is pressed or released
	// get event key
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = _KeyEvents[i].dwOfs;
		int KeyState = _KeyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			CManagerScene::GetInstance()->OnKeyDown(KeyCode);
		else
			CManagerScene::GetInstance()->OnKeyUp(KeyCode);

	}

}

int CInput::IsKeyDown(int KeyCode)
{
	return (_KeyStates[KeyCode] & 0x80) > 0;
}


CInput * CInput::GetInstance()
{
	if (_instance == nullptr)
		_instance = new CInput();

	return _instance;
}
