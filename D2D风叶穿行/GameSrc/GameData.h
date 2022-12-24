#pragma once
#include "../GameEngine/GameEngine.h"

class GameData
{
public:
	GameData();
	~GameData();
	static shu::vec2f camera;
	static float camera_speed;
	static int score;
	static shu::vec2i screen_size;

	static GameData* ptr;
};
