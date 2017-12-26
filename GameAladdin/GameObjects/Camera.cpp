#include "Camera.h"
#include "../GameComponents/Graphics.h"
#include "../GameComponents/Input.h"
#include "../GameComponents/SceneManager.h"
#include "../GameComponents/define.h"

Camera* Camera::_instance = NULL;

Camera::Camera(GameObject* follow)
{
	_follow = follow;
	_width = Graphics::GetInstance()->GetScreenWidth() / SCALE_FACTOR;
	_height = Graphics::GetInstance()->GetScreenHeight() / SCALE_FACTOR;

	_position = D3DXVECTOR2((_width*1.0) / 2, Graphics::GetInstance()->GetScreenHeight() - (_height / 2.0f));
	_position.x = _follow->GetPosition().x;
	_position.y = _follow->GetPosition().y;


	this->_instance = this;

	this->_indexCamera = -1;
	this->_indexCameraLeft = -1;
	this->_isPrKeyRight = false;
	this->_isPrKeyLeft = false;

	this->_countDownCameraUp = 10;
}

Camera::~Camera()
{
}

Camera * Camera::GetInstance()
{
	if (!_instance)
		_instance = new Camera();

	return _instance;
}

void Camera::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	GameMap *currentMap = SceneManager::GetInstance()->GetCurrentScene()->GetGameMap();

	if (_follow != NULL)
	{

		if (_input->IsKeyPressed(DIK_RIGHT))
		{
			if (_isPrKeyLeft && (!_isPrKeyRight))
			{
				_indexCamera = SPACE_CAMERA * 2;
				_isPrKeyLeft = false;
				_indexCameraLeft = -1;
				_position.x = _follow->GetPosition().x;

			}
			else
			{
				if (_isPrKeyRight)
				{
					_position.x = _follow->GetPosition().x + SPACE_CAMERA;
					_indexCameraLeft = -1;
					_isPrKeyLeft = false;
				}
				else
				{
					_indexCamera = SPACE_CAMERA;
					_position.x = _follow->GetPosition().x;
				}

			}
		}

		if (_indexCamera > 0)
		{
			_position.x++;
			_indexCamera--;
			_isPrKeyRight = false;
		}

		if (_indexCamera <= 0 && (_indexCamera != -1)) {
			_isPrKeyRight = true;
		}

		/////////////////////////////////////////////////////
		if (_input->IsKeyPressed(DIK_LEFT))
		{
			if (_isPrKeyRight && (!_isPrKeyLeft))
			{
				_indexCameraLeft = SPACE_CAMERA * 2;
				_isPrKeyRight = false;
				_indexCamera = -1;
				_position.x = _follow->GetPosition().x;

			}
			else
			{
				if (_isPrKeyLeft)
				{
					_position.x = _follow->GetPosition().x - SPACE_CAMERA;
					_isPrKeyRight = false;
					_indexCamera = -1;
				}
				else
				{
					_position.x = _follow->GetPosition().x;
					_indexCameraLeft = SPACE_CAMERA;
				}
			}
		}

		if (_indexCameraLeft > 0)
		{
			_position.x--;
			_indexCameraLeft--;
			_isPrKeyLeft = false;
		}

		if (_indexCameraLeft <= 0 && (_indexCameraLeft != -1)) {
			_isPrKeyLeft = true;
		}


		/*char buffer[100];
		sprintf_s(buffer, "check it out: %d - %d\n", _countDownCameraUp, _position.y);
		OutputDebugStringA(buffer);*/

		///////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

		if (currentMap->GetPlayer()->GetState()->GetName() == PlayerState::StateName::Up)
		{

			if (_countDownCameraUp > 0)
			{
				_position.y -= 3;
				_countDownCameraUp--;
			}

		}
		else
		{
			if (_countDownCameraUp < SPACE_ALADIN_UP)
			{
				_position.y += 3;
				_countDownCameraUp++;

				if (_countDownCameraUp > SPACE_ALADIN_UP)
				{
					_countDownCameraUp = SPACE_ALADIN_UP;
				}
			}
			else
			{
				_position.y = _follow->GetPosition().y;
				//OutputDebugStringA("Normal\n");
				_countDownCameraUp = SPACE_ALADIN_UP;
			}
		}


		//stop when at bound of map
		if (_position.x - _width / 2 < 0)
			_position.x = _width / 2;
		if (_position.x + _width / 2 > currentMap->GetWidth())
			_position.x = currentMap->GetWidth() - _width / 2;

		if (_position.y - _height / 2 < 0)
			_position.y = _height / 2;
		if (_position.y + _height / 2 > currentMap->GetHeight())
			_position.y = currentMap->GetHeight() - _height / 2;

	}
}

bool Camera::IsInCamera(D3DXVECTOR2 position, int width, int height)
{
	float _left, _right, _top, _bottom;
	GetBound(_top, _right, _bottom, _left);

	float left = position.x - ((float)width) / 2;
	float right = position.x + ((float)width) / 2;
	float top = position.y - ((float)height) / 2;
	float bottom = position.y + ((float)height) / 2;

	if (_left > right || _right<left || _top>bottom || _bottom < top)
		return false;
	return true;
}

D3DXVECTOR2 Camera::ConvertPosition(D3DXVECTOR2 position)
{
	return ConvertPosition(position.x, position.y);
}

D3DXVECTOR2 Camera::ConvertPosition(float x, float y)
{
	D3DXVECTOR2 newPosition;
	newPosition.x = x - (_position.x - _width / 2);
	newPosition.y = y - (_position.y - _height / 2);

	//scale
	newPosition.x *= Graphics::GetInstance()->GetScreenWidth() / _width;
	newPosition.y *= Graphics::GetInstance()->GetScreenHeight() / _height;

	return newPosition;
}
