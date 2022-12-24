#include "GameData.h"

GameData* GameData::ptr = nullptr;
shu::vec2f GameData::camera = shu::vec2f(0.0f, 0.0f);
shu::vec2i GameData::screen_size = shu::vec2i(1920, 500);
float GameData::camera_speed = 0.0f;
int GameData::score = 0;

GameData::GameData()
{
	ptr = this;
}

GameData::~GameData()
{
}
