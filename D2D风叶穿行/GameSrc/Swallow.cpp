#include "Swallow.h"

Swallow::Swallow()
{
}

Swallow::~Swallow()
{
}

bool Swallow::Init()
{
	if (!m_animation.CreateAnimation(L"res\\img\\swallow.png", L"res\\json\\swallow.json", 0.1f)) return false;
	return true;
}

void Swallow::Updata(float dt)
{
	if (int(GameData::score) % 30 == 0)
	{
		m_pos = shu::vec2f(GameData::camera.x + GameData::screen_size.x, 0.0f);
		score = int(GameData::score);
	}
	m_animation.Updata(dt);
	m_bitmap = m_animation.GetBitmap();
	m_pos.x -= 100.0f * dt;

}

void Swallow::Render(shu::Direct2dRender& rt)
{
	rt.DrawBitmap(m_bitmap, m_pos, shu::vec2f(m_bitmap->GetSize().width * 2.0f, m_bitmap->GetSize().height * 2.0f));
	rt.DrawTextCenter(
		std::to_wstring(score),
		shu::vec2f(m_pos.x, m_pos.y + 20.0f),
		shu::vec2f(m_bitmap->GetSize().width * 2.0f, m_bitmap->GetSize().height * 2.0f),
		shu::Color::Black, 40.0f);
}

void Swallow::Reset()
{
	m_pos = shu::vec2f(-500.0f, 0.0f);
	score = 0;
}
