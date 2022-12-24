#pragma once
#include "../GameEngine/Resource.h"
#include "./GameData.h"

// Á£×Ó·¢ÉäÆ÷
class Particle
{
public:
	struct lizi
	{
		float life;
		shu::vec2f pos;
		shu::vec2f speed;
		ID2D1Bitmap1* bitmap;
	};


	Particle();
	~Particle();

	void Updata(float dt);
	void Render(shu::Direct2dRender& rt);


private:
	std::vector<lizi> m_lizi;
	float m_all_time;
};

