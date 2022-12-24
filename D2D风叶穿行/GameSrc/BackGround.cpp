#include "BackGround.h"

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
	for (auto& it : m_BackGrounds) delete it;
}

bool BackGround::Init()
{
	back_ground_data* data = new back_ground_data{ 10.0f, 0.0f, nullptr };
	data->bitmap = shu::Resource::GetBitmap(L"res/img/sky.png");
	if (data->bitmap == nullptr) return false;
	m_BackGrounds.push_back(data);

	data = new back_ground_data{ 30.0f, 0.0f, nullptr };
	data->bitmap = shu::Resource::GetBitmap(L"res/img/cloud.png");
	if (data->bitmap == nullptr) return false;
	m_BackGrounds.push_back(data);

	data = new back_ground_data{ 100.0f, 0.0f, nullptr };
	data->bitmap = shu::Resource::GetBitmap(L"res/img/sand.png");
	if (data->bitmap == nullptr) return false;
	m_BackGrounds.push_back(data);

	data = new back_ground_data{ 160.0f, 0.0f, nullptr };
	data->bitmap = shu::Resource::GetBitmap(L"res/img/cactus.png");
	if (data->bitmap == nullptr) return false;
	m_BackGrounds.push_back(data);

	return true;
}

void BackGround::Updata(float dt)
{
	for (auto it : m_BackGrounds)
	{
		it->pos -= it->speed * dt;
		if (abs(it->pos) >= m_width) it->pos = it->pos + m_width;
	}
}

void BackGround::Render(shu::Direct2dRender& rt)
{
	for (auto it : m_BackGrounds)
	{
		rt.DrawBitmap(it->bitmap, shu::vec2f(it->pos + GameData::camera.x, 0.0f), shu::vec2f(m_width, m_height));
		rt.DrawBitmap(it->bitmap, shu::vec2f(it->pos + GameData::camera.x + m_width, 0.0f), shu::vec2f(m_width, m_height));
	}
}
