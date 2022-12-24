#pragma once
#include "../GameSrc/GameData.h"
#include "../GameSrc/AnimationComponent.h"

class Swallow
{
public:
	Swallow();
	~Swallow();

	bool Init();
	void Updata(float dt);
	void Render(shu::Direct2dRender& rt);
	void Reset();

private:
	AnimationComponent m_animation;
	ID2D1Bitmap1* m_bitmap = nullptr;

	shu::vec2f m_pos = shu::vec2f(-500.0f, 0.0f);

	int score = 0;
};

