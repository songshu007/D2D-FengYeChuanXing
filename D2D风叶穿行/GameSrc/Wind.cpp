#include "Wind.h"

Wind::Wind()
	: m_animation1(nullptr),
	m_animation2(nullptr),
	m_animation3(nullptr),
	m_animation4(nullptr),
	m_now_animation(nullptr),
	m_bitmap(nullptr)
{
	//srand(time(NULL));
}

Wind::~Wind()
{
	delete m_animation1;
	delete m_animation2;
	delete m_animation3;
	delete m_animation4;
}

bool Wind::Init()
{
	m_animation1 = new AnimationComponent();
	m_animation2 = new AnimationComponent();
	m_animation3 = new AnimationComponent();
	m_animation4 = new AnimationComponent();

	if (!m_animation1->CreateAnimation(L"res\\img\\wind1.png", L"res\\json\\wind1.json", 0.1f)) return false;
	if (!m_animation2->CreateAnimation(L"res\\img\\wind2.png", L"res\\json\\wind2.json", 0.1f)) return false;
	if (!m_animation3->CreateAnimation(L"res\\img\\wind3.png", L"res\\json\\wind3.json", 0.1f)) return false;
	if (!m_animation4->CreateAnimation(L"res\\img\\wind4.png", L"res\\json\\wind4.json", 0.1f)) return false;

	m_animation1->SetAnimationLoop(false);
	m_animation2->SetAnimationLoop(false);
	m_animation3->SetAnimationLoop(false);
	m_animation4->SetAnimationLoop(false);

	m_animation1->SetAnimation("idle");
	m_animation2->SetAnimation("idle");
	m_animation3->SetAnimation("idle");
	m_animation4->SetAnimation("idle");

	return true;
}

void Wind::Updata(float dt)
{
	static float last_time = 0.0f;
	m_all_time += dt;

	if (m_all_time - last_time >= 5.0f)
	{
		last_time = m_all_time;
		int r = rand() % 4;
		if (r == 0) m_now_animation = m_animation1;
		if (r == 1) m_now_animation = m_animation2;
		if (r == 2) m_now_animation = m_animation3;
		if (r == 3) m_now_animation = m_animation4;
		m_now_animation->SetFrame(0);
	}
	if (m_now_animation != nullptr)
	{
		m_now_animation->Updata(dt);
		m_bitmap = m_now_animation->GetBitmap();
	}
}

void Wind::Render(shu::Direct2dRender& rt)
{
	if (m_now_animation != nullptr)
	{
		if (!m_now_animation->isEnd())
			rt.DrawBitmap(m_bitmap, shu::vec2f(GameData::camera.x, 0.0f), rt.GetSize());
	}
}

