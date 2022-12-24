#include "Shamrock2.h"

Shamrock2::Shamrock2()
{
}

Shamrock2::~Shamrock2()
{
}

bool Shamrock2::Init()
{
	if (!this->InitHitboxComponent(HitBox{ {0.0f, 0.0f}, {80.0f, 40.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} }))
		return false;
	if (!this->InitHitboxComponent2(HitBox{ {0.0f, 0.0f}, {5.0f, 5.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} }))
		return false;
	if (!this->InitAnimationComponent(L"res/img/shamrock2.png", L"res/json/shamrock2.json", 0.1f))
		return false;

	this->GetAnimationComponent()->SetAnimation("idle");

	rand_num = rand() % 50 + 30;

	return true;
}

void Shamrock2::Updata(float dt)
{
	m_all_time += dt;

	m_hitbox->GetHitbox().speed += m_hitbox->GetHitbox().acceleration * dt;

	this->UpdataAnimation(dt);

	if (isGrab == true)
	{
		PlayerObject* player = ((PlayerObject*)m_player);
		player->GetHitbox().pos = shu::vec2f(this->GetHitbox2().pos.x - 30.0f, this->GetHitbox2().pos.y - 20.0f);
	}

	// ¸üÐÂÎ»ÖÃ
	this->GetHitbox().pos += this->GetHitbox().speed * dt;
	this->GetHitbox2().pos = shu::vec2f(this->GetHitbox().pos.x + 40.0f, this->GetHitbox().pos.y + 90.0f);

	this->GetHitbox().speed.y = sin(m_all_time + rand_num) * rand_num * 0.5f;

}

void Shamrock2::Render(shu::Direct2dRender& rt)
{
	rt.DrawBitmap(
		m_bitmap,
		shu::vec2f(m_hitbox->GetPos().x - 13.0f, m_hitbox->GetPos().y - 20.0f),
		shu::vec2f(m_bitmap->GetSize().width * 2.0f, m_bitmap->GetSize().height * 2.0f)
	);

	m_hitbox->Render(rt);
	m_hitbox2->Render(rt);
}

void Shamrock2::OnEvent(Event event)
{
	switch (event)
	{
	case Event::StepOn:
	{

		break;
	}
	case Event::Grab:
	{
		isGrab = true;
		PlayerObject* player = ((PlayerObject*)m_player);
		player->SetStatus(Player_Status::Climb);
		player->GetHitbox().acceleration = shu::vec2f(0.0f, 0.0f);
		player->GetHitbox().speed = shu::vec2f(0.0f, 0.0f);

		break;
	}
	case Event::Jump:
	{
		isGrab = false;
		break;
	}
	default:
		break;
	}
}

void Shamrock2::UpdataAnimation(float dt)
{
	m_animation->Updata(dt);
	m_bitmap = m_animation->GetBitmap();
}
