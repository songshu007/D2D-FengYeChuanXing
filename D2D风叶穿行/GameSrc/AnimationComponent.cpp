#include "AnimationComponent.h"

AnimationComponent::AnimationComponent()
	: m_frame(0), m_animation(nullptr)
{
	m_clock.Reset();
}

AnimationComponent::~AnimationComponent()
{

}

bool AnimationComponent::CreateAnimation(const std::wstring& bitmapFile, const std::wstring& jsonFile, float duration)
{
	m_animation = AnimationManage::GetAnimation(bitmapFile, jsonFile, duration);
	if (m_animation != nullptr)
	{
		m_now_animation = m_animation->begin();
		return true;
	}

	return false;
}

void AnimationComponent::Updata(float dt)
{
	if (m_clock.GetTime() > m_now_animation->second.second)
	{
		is_end = false;
		m_frame++;
		m_clock.Reset();
		if (m_frame >= m_now_animation->second.first.size())
		{
			if (is_loop)
			{
				m_frame = 0;
				is_end = true;
			}
			else
			{
				m_frame = m_now_animation->second.first.size() - 1;
				is_end = true;
			}
		}
	}
}

uint32_t AnimationComponent::GetNowFrame()
{
	return m_frame;
}

void AnimationComponent::SetAnimationLoop(bool flag)
{
	is_loop = flag;
}

std::string AnimationComponent::GetNowAnimation()
{
	return m_now_animation->first;
}

bool AnimationComponent::isEnd()
{
	return is_end;
}

void AnimationComponent::SetFrame(size_t frame)
{
	if (m_now_animation->second.first.size() < frame) return;
	m_frame = frame;
}

ID2D1Bitmap1* AnimationComponent::GetBitmap()
{
	return m_now_animation->second.first.at(m_frame);
}

bool AnimationComponent::SetAnimation(const std::string& name)
{
	if (name == m_now_animation->first) return false;
	is_end = false;
	m_frame = 0;
	auto it = m_animation->find(name);
	if (it == m_animation->end())
		return false;
	m_now_animation = it;
	return true;
}

std::vector<std::string> AnimationComponent::GetAllAnimation()
{
	std::vector<std::string> temp;

	for (auto it = m_animation->begin(); it != m_animation->end(); it++)
	{
		temp.push_back(it->first);
	}

	return temp;
}