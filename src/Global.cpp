#include "Global.h"

Global* Global::_instance = nullptr;

Global::Global()
{
}

Global::~Global()
{
}

void Global::SetDirectDevice(LPDIRECT3DDEVICE9 device)
{
	_DirectDevice = device;
}

LPDIRECT3DDEVICE9 Global::GetDirectDevice()
{
	return _DirectDevice;
}

Global * Global::GetInstance()
{
	if (_instance == nullptr)
		_instance = new Global();

	return _instance;
}
