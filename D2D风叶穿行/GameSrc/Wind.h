#pragma once
#include "AnimationComponent.h"
#include "./GameData.h"

class Wind
{
public:
	Wind();
	~Wind();

	bool Init();
	void Updata(float dt);
	void Render(shu::Direct2dRender& rt);

private:
	AnimationComponent* m_animation1;
	AnimationComponent* m_animation2;
	AnimationComponent* m_animation3;
	AnimationComponent* m_animation4;

	AnimationComponent* m_now_animation;
	ID2D1Bitmap1* m_bitmap;

	float m_all_time;
};

