#pragma once
#include "../GameEngine/Render.h"
#include "../GameEngine/Clock.h"
#include "AnimationManage.h"

class AnimationComponent
{
public:
	AnimationComponent();
	~AnimationComponent();

	bool CreateAnimation(const std::wstring& bitmapFile, const std::wstring& jsonFile, float duration);
	void Updata(float dt);
	ID2D1Bitmap1* GetBitmap();
	bool SetAnimation(const std::string& name);
	std::vector<std::string> GetAllAnimation();
	void SetAnimationLoop(bool flag);
	std::string GetNowAnimation();
	bool isEnd();
	void SetFrame(size_t frame);

	uint32_t GetNowFrame();

private:
	_Animation* m_animation;
	_Animation::iterator m_now_animation;
	Clock m_clock;
	uint32_t m_frame;
	//float dt;

	bool is_loop = true;
	bool is_end = false;
};

