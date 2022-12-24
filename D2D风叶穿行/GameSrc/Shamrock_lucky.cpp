#include "Shamrock_lucky.h"

Shamrock_lucky::Shamrock_lucky()
{
}

Shamrock_lucky::~Shamrock_lucky()
{
}

bool Shamrock_lucky::Init()
{
	if (!this->InitHitboxComponent(HitBox{ {0.0f, 0.0f}, {65.0f, 40.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} }))
		return false;
	if (!this->InitHitboxComponent2(HitBox{ {0.0f, 0.0f}, {5.0f, 5.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} }))
		return false;
	if (!this->InitAnimationComponent(L"res/img/shamrock_lucky.png", L"res/json/shamrock_lucky.json", 0.1f))
		return false;

	this->GetAnimationComponent()->SetAnimation("idle");

	rand_num = rand() % 50 + 30;

	return true;
}

void Shamrock_lucky::Updata(float dt)
{
	m_all_time += dt;

	this->UpdataAnimation(dt);

	switch (m_status)
	{
	case Lucky_Status::Idle:
	{
		if (m_player_status == Status::Grab)
		{
			PlayerObject* player = ((PlayerObject*)m_player);
			player->GetHitbox().pos = shu::vec2f(this->GetHitbox2().pos.x - 30.0f, this->GetHitbox2().pos.y - 20.0f);
		}

		break;
	}
	case Lucky_Status::Move:
	{
		isUsed = true;
		PlayerObject* player = ((PlayerObject*)m_player);

		// 延时停止叶子
		if ((m_all_time - BeginMoveTime) >= 20.0f)
		{
			m_hitbox->GetHitbox().speed.x = 0.0f;
			this->SetStatus(Lucky_Status::Idle);

			if (m_player_status == Status::Step)
			{
				player->SetStatus(Player_Status::Air);
				player->GetHitbox().pos.y =
					this->GetHitbox().pos.y - player->GetHitbox().size.y - 0.1f;
				player->OnEvent(Event::EndPlay33Animation);
			}
			if (m_player_status == Status::Grab)
			{
				player->OnEvent(Event::EndPlay33Animation);
			}
			return;
		}
		
		if (m_player_status == Status::Step)
		{
			player->GetHitbox().pos = shu::vec2f(
				this->GetHitbox().pos.x + (this->GetHitbox().size.x - player->GetHitbox().size.x) * 0.5f,
				this->GetHitbox().pos.y - player->GetHitbox().size.y
			);
		}
		if (m_player_status == Status::Grab)
		{
			player->GetHitbox().pos = shu::vec2f(this->GetHitbox2().pos.x - 30.0f, this->GetHitbox2().pos.y - 20.0f);
		}
		if (this->GetHitbox().pos.x >= GameData::camera.x + 1600)
		{
			this->GetHitbox().speed.x = GameData::camera_speed;
		}

		player->GetHitbox().speed = shu::vec2f(0.0f, 0.0f);
		player->GetHitbox().acceleration = shu::vec2f(0.0f, 0.0f);
		break;
	}
	default:
		break;
	}

	// 更新位置
	this->GetHitbox().pos += this->GetHitbox().speed * dt;
	this->GetHitbox2().pos = shu::vec2f(this->GetHitbox().pos.x + 25.0f, this->GetHitbox().pos.y + 85.0f);

	this->GetHitbox().speed.y = sin(m_all_time + rand_num) * rand_num * 0.5f;

}

void Shamrock_lucky::Render(shu::Direct2dRender& rt)
{
	rt.DrawBitmap(
		m_bitmap,
		shu::vec2f(m_hitbox->GetPos().x - 28.0f, m_hitbox->GetPos().y - 50.0f),
		shu::vec2f(m_bitmap->GetSize().width * 2.0f, m_bitmap->GetSize().height * 2.0f)
	);

	m_hitbox->Render(rt);
	m_hitbox2->Render(rt);
}

void Shamrock_lucky::OnEvent(Event event)
{
	switch (event)
	{
	case Event::StepOn: 
	{
		if (isUsed == true) break;
		isUsed = true;

		m_player_status = Status::Step;

		BeginMoveTime = m_all_time;
		this->GetHitbox().speed.x = GameData::camera_speed + 50.0f;
		PlayerObject* player = ((PlayerObject*)m_player);
		player->SetStatus(Player_Status::Lock);
		player->OnEvent(Event::BeginPlay33Animation);
		this->SetStatus(Lucky_Status::Move);

		break;
	}
	case Event::Grab:
	{
		if (isUsed == false)
		{
			// 只在第一次被抓住时执行一次
			isUsed = true;
			m_player_status = Status::Grab;
			BeginMoveTime = m_all_time;
			this->GetHitbox().speed.x = GameData::camera_speed + 50.0f;
			this->SetStatus(Lucky_Status::Move);
			PlayerObject* player = ((PlayerObject*)m_player);
			player->SetStatus(Player_Status::Climb);
			player->GetHitbox().acceleration = shu::vec2f(0.0f, 0.0f);
			player->GetHitbox().speed = shu::vec2f(0.0f, 0.0f);
			player->OnEvent(Event::BeginPlay33Animation);
		}
		else
		{
			m_player_status = Status::Grab;
			PlayerObject* player = ((PlayerObject*)m_player);
			player->SetStatus(Player_Status::Climb);
			player->GetHitbox().acceleration = shu::vec2f(0.0f, 0.0f);
			player->GetHitbox().speed = shu::vec2f(0.0f, 0.0f);
		}

		break;
	}
	case Event::Jump:
	{
		m_player_status = Status::None;
		this->SetStatus(Lucky_Status::Idle);
		m_hitbox->GetHitbox().speed.x = 0.0f;
		((PlayerObject*)m_player)->OnEvent(Event::EndPlay33Animation);

		break;
	}
	default:
		break;
	}

}

void Shamrock_lucky::SetStatus(Lucky_Status status)
{
	m_last_status = m_status;
	m_status = status;
}

void Shamrock_lucky::UpdataAnimation(float dt)
{
	m_animation->Updata(dt);
	m_bitmap = m_animation->GetBitmap();
}
