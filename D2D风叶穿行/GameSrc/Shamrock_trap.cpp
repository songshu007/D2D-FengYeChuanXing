#include "Shamrock_trap.h"

Shamrock_trap::Shamrock_trap()
{
}

Shamrock_trap::~Shamrock_trap()
{
}

bool Shamrock_trap::Init()
{
	if (!this->InitHitboxComponent(HitBox{ {0.0f, 0.0f}, {65.0f, 40.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} }))
		return false;
	if (!this->InitHitboxComponent2(HitBox{ {0.0f, 0.0f}, {5.0f, 5.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} }))
		return false;
	if (!this->InitAnimationComponent(L"res/img/shamrock_trap.png", L"res/json/shamrock_trap.json", 0.1f))
		return false;

	this->GetAnimationComponent()->SetAnimation("idle");

	rand_num = rand() % 50 + 30;

	return true;
}

void Shamrock_trap::Updata(float dt)
{
	m_all_time += dt;

	switch (m_status)
	{
	case Trap_Status::Idle:
	{
		this->UpdataAnimation(dt);
		if (isGrep == true)
		{
			PlayerObject* player = ((PlayerObject*)m_player);
			player->GetHitbox().pos = shu::vec2f(this->GetHitbox2().pos.x - 30.0f, this->GetHitbox2().pos.y - 20.0f);
		}
		break;
	}
	case Trap_Status::Timeing:
	{
		this->UpdataAnimation(dt);
		if (isGrep == true)
		{
			PlayerObject* player = ((PlayerObject*)m_player);
			player->GetHitbox().pos = shu::vec2f(this->GetHitbox2().pos.x - 30.0f, this->GetHitbox2().pos.y - 20.0f);
		}
		if ((m_all_time - BeginTime) >= 0.3f)
		{
			this->SetStatus(Trap_Status::Goneing);
			this->GetAnimationComponent()->SetAnimation("vanish");
			this->GetHitbox().isWorks = false;
			this->GetHitbox2().isWorks = false;
		}
		break;
	}
	case Trap_Status::Goneing:
	{
		this->UpdataAnimation(dt);
		if (isGrep == true)
		{
			PlayerObject* player = ((PlayerObject*)m_player);
			player->SetStatus(Player_Status::Air);
			isGrep = false;
		}
		if (this->GetAnimationComponent()->isEnd())
		{
			this->SetStatus(Trap_Status::Gone);
		}
		break;
	}
	case Trap_Status::Gone:
	{

		break;
	}
	default:
		break;
	}

	// ¸üÐÂÎ»ÖÃ
	this->GetHitbox().pos += this->GetHitbox().speed * dt;
	this->GetHitbox2().pos = shu::vec2f(this->GetHitbox().pos.x + 40.0f, this->GetHitbox().pos.y + 85.0f);

	this->GetHitbox().speed.y = sin(m_all_time + rand_num) * rand_num * 0.5f;

}

void Shamrock_trap::Render(shu::Direct2dRender& rt)
{
	if (m_status != Trap_Status::Gone)
	{
		rt.DrawBitmap(
			m_bitmap,
			shu::vec2f(m_hitbox->GetPos().x - 170.0f, m_hitbox->GetPos().y - 180.0f),
			shu::vec2f(m_bitmap->GetSize().width * 2.0f, m_bitmap->GetSize().height * 2.0f)
		);
	}

	m_hitbox->Render(rt);
	m_hitbox2->Render(rt);
}

void Shamrock_trap::OnEvent(Event event)
{
	switch (event)
	{
	case Event::StepOn:
	{
		if (isUsed == true) break;
		isUsed = true;
		BeginTime = m_all_time;
		this->SetStatus(Trap_Status::Timeing);

		break;
	}
	case Event::Grab:
	{
		if (isUsed == false) BeginTime = m_all_time;
		if (isUsed == false) this->SetStatus(Trap_Status::Timeing);
		isUsed = true;
		isGrep = true;
		PlayerObject* player = ((PlayerObject*)m_player);
		player->SetStatus(Player_Status::Climb);
		player->GetHitbox().acceleration = shu::vec2f(0.0f, 0.0f);
		player->GetHitbox().speed = shu::vec2f(0.0f, 0.0f);

		break;
	}
	case Event::Jump:
	{
		isGrep = false;
		break;
	}
	default:
		break;
	}
}

void Shamrock_trap::SetStatus(Trap_Status status)
{
	m_last_status = m_status;
	m_status = status;
}

void Shamrock_trap::UpdataAnimation(float dt)
{
	m_animation->Updata(dt);
	m_bitmap = m_animation->GetBitmap();
}
