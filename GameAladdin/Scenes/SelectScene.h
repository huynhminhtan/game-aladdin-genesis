#pragma once
#include "../GameObjects/Camera.h"
#include "../GameComponents/Animation.h"
#include "../GameComponents/Text.h"
#include "../GameComponents/SceneManager.h"
#include "../Scenes/MainScene.h"
#include "../Scenes/JafarScene.h"


class SelectScene :public Scene
{
private:
	Text* _title;
	Animation *_animationAladdin;
	Animation *_animationMonkey;
	Sprite *_bg;
	Sprite *_bg2;

	int Select, State;
	float Fade;

	vector<Text*> List;

public:
	SelectScene();
	~SelectScene();

	void LoadContent();
	void Update(float deltatime);
	void Draw();
};