#include "Player.h"
#include "../GameEngine/InputKey.h"

Player::Player(std::vector<Entity*>& leaves)
	: m_leaves(leaves)
{
	this->InitHitboxComponent(HitBox{ {0.0f, 0.0f}, {40.0f, 80.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} });
	this->InitHitboxComponent2(HitBox{ {0.0f, 0.0f}, {120.0f, 110.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} });
	this->InitAnimationComponent(L"res/img/22.png", L"res/json/22.json", 0.1f);
	this->GetAnimationComponent()->SetAnimation("idle");

	this->GetHitboxComponent()->SetPos(shu::vec2f(700.0f, 0.0f));

	this->m_33animation = new AnimationComponent();
	this->m_33animation->CreateAnimation(L"res/img/33.png", L"res/json/33.json", 0.1f);
}

Player::~Player()
{
}

void Player::Updata(float dt)
{
	this->Updata33(dt);

	static shu::Key key{};

	if (shu::InputKey::GetKeyStatus(shu::Key::D).isPress)
		key = shu::Key::D;
	if (shu::InputKey::GetKeyStatus(shu::Key::A).isPress)
		key = shu::Key::A;

	this->UpdataAnimation(dt);

	switch (m_status)
	{
	case Player_Status::Ground:
	{
		m_hitbox->GetHitbox().acceleration.y = 1000.0f;
		this->UpdataMove(key);
		this->UpdataSpeed(dt);
		this->UpdataCollide(dt);

		if (shu::InputKey::GetKeyStatus(shu::Key::SPACE).isHold)
		{
			m_hitbox->GetHitbox().speed.y = -590.0f;
			this->SetStatus(Player_Status::Air);
		}
		if (shu::InputKey::GetKeyStatus(shu::Key::K).isPress)
		{
			for (auto& it : m_leaves)
			{
				if (!HitboxComponent::RectVsRect(this->GetHitbox2(), ((LeaveObject*)it)->GetHitbox2())) continue;
				it->OnEvent(Event::Grab);
			}
		}


		break;
	}
	case Player_Status::Air:
	{
		m_hitbox->GetHitbox().acceleration.y = 1000.0f;
		this->UpdataMove(key);
		this->UpdataSpeed(dt);
		this->UpdataCollide(dt);

		if (shu::InputKey::GetKeyStatus(shu::Key::K).isPress)
		{
			for (auto& it : m_leaves)
			{
				if (!HitboxComponent::RectVsRect(this->GetHitbox2(), ((LeaveObject*)it)->GetHitbox2())) continue;
				it->OnEvent(Event::Grab);
			}
		}

		break;
	}
	case Player_Status::Lock:
	{
		if (key == shu::Key::D)
		{
			m_animation->SetAnimation("idle");
		}
		if (key == shu::Key::A)
		{
			m_animation->SetAnimation("idle_left");
		}

		if (shu::InputKey::GetKeyStatus(shu::Key::SPACE).isPress)
		{
			m_hitbox->GetHitbox().speed.y = -590.0f;
			this->SetStatus(Player_Status::Air);
			for (auto& it : m_leaves) it->OnEvent(Event::Jump);
		}

		break;
	}
	case Player_Status::Climb:
	{
		if (m_animation->GetNowAnimation() != "climb")
			m_animation->SetAnimation("into_climb");
		if (m_animation->GetNowAnimation() == "into_climb" && m_animation->isEnd())
			m_animation->SetAnimation("climb");

		if (shu::InputKey::GetKeyStatus(shu::Key::SPACE).isHold)
		{
			m_hitbox->GetHitbox().speed.y = -590.0f;
			this->SetStatus(Player_Status::Air);
			for (auto& it : m_leaves) it->OnEvent(Event::Jump);
		}

		break;
	}
	default:
		break;
	}

	// 更新位置
	this->GetHitbox().pos += this->GetHitbox().speed * dt;
	this->GetHitbox2().pos = shu::vec2f(this->GetHitbox().pos.x - 40.0f, this->GetHitbox().pos.y - 30.0f);
}

void Player::Render(shu::Direct2dRender& rt)
{
	this->Draw33(rt);

	rt.DrawBitmap(
		m_bitmap,
		shu::vec2f(m_hitbox->GetPos().x - 45.0f, m_hitbox->GetPos().y - 23.0f),
		shu::vec2f(m_bitmap->GetSize().width * 2.0f, m_bitmap->GetSize().height * 2.0f)
	);

	m_hitbox->Render(rt);
	m_hitbox2->Render(rt);
	if (HitboxComponent::isShowHitbox)
	{
		auto center = m_hitbox->GetHitbox().pos + m_hitbox->GetHitbox().size / 2.0f;
		rt.DrawLine(center, center + m_hitbox->GetHitbox().acceleration.norm() * 50.0f, shu::Color::Green, 5.0f);
	}
}

void Player::OnEvent(Event event)
{
	switch (event)
	{
	case Event::StepOn:
		break;
	case Event::Grab:
		break;
	case Event::Jump:
		break;
	case Event::BeginPlay33Animation:
	{
		m_33status = status_33::Fly;
		break;
	}
	case Event::EndPlay33Animation:
	{
		m_33status = status_33::Into_dizzy;
		break;
	}
	default:
		break;
	}

}

void Player::Updata33(float dt)
{
	static shu::vec2f off_33_pos = shu::vec2f(0.0f, 0.0f);
	m_33animation->Updata(dt);
	m_33bitmap = m_33animation->GetBitmap();

	switch (m_33status)
	{
	case status_33::None:
		break;
	case status_33::Fly:
	{
		m_33animation->SetAnimation("fly");

		if (off_33_pos.x < this->GetHitbox().pos.x - GameData::camera.x - 200.0f) off_33_pos.x += 200.0f * dt;
		else m_33status = status_33::Blow;
		off_33_pos.y = this->GetHitbox().pos.y;

		m_33pos.x = GameData::camera.x + off_33_pos.x;
		m_33pos.y = off_33_pos.y;

		break;
	}
	case status_33::Blow:
	{
		m_33animation->SetAnimation("blow");
		m_33pos = shu::vec2f(this->GetHitbox().pos.x - 200.0f, this->GetHitbox().pos.y);

		break;
	}
	case status_33::Into_dizzy:
	{
		m_33animation->SetAnimation("into_dizzy");

		if (m_33animation->isEnd())
			m_33status = status_33::Dizzy;

		break;
	}
	case status_33::Dizzy:
	{
		m_33animation->SetAnimation("dizzy");

		m_33pos.x -= 200.0f * dt;

		if (m_33pos.x <= GameData::camera.x)
		{
			m_33status = status_33::None;
			off_33_pos = shu::vec2f(0.0f, 0.0f);
		}

		break;
	}
	default:
		break;
	}
}

void Player::Draw33(shu::Direct2dRender& rt)
{
	if (m_33status != status_33::None && m_33bitmap != nullptr)
	{
		rt.DrawBitmap(
			m_33bitmap,
			shu::vec2f(m_33pos.x, m_33pos.y),
			shu::vec2f(m_33bitmap->GetSize().width * 2.0f, m_33bitmap->GetSize().height * 2.0f)
		);
	}
}

void Player::UpdataAnimation(float dt)
{
	static shu::Key key{};

	m_animation->Updata(dt);
	m_bitmap = m_animation->GetBitmap();
	if (m_status == Player_Status::Ground)
	{
		// 这里 key 变量其实是上一次的值，因为更新 key 值的代码在下面呢！=w=
		// 我们可以利用这个特性获得玩家正确的面向方向
		if (key == shu::Key::A)
		{
			if (m_hitbox->GetSpeed().x == 0.0f)  m_animation->SetAnimation("idle_left");
			if (m_hitbox->GetSpeed().x < 0.0f)  m_animation->SetAnimation("run_left");
		}
		else if (key == shu::Key::D)
		{
			if (m_hitbox->GetSpeed().x == 0.0f)  m_animation->SetAnimation("idle");
			if (m_hitbox->GetSpeed().x > 0.0f)  m_animation->SetAnimation("run");
		}
	}
	if (m_status == Player_Status::Air)
	{
		if (key == shu::Key::A)
		{
			if (m_hitbox->GetSpeed().y < 0.0f)  m_animation->SetAnimation("jump_left");
			if (m_hitbox->GetSpeed().y > 0.0f)  m_animation->SetAnimation("fall_left");
		}
		else if (key == shu::Key::D)
		{
			if (m_hitbox->GetSpeed().y < 0.0f)  m_animation->SetAnimation("jump");
			if (m_hitbox->GetSpeed().y > 0.0f)  m_animation->SetAnimation("fall");
		}
	}

	if (shu::InputKey::GetKeyStatus(shu::Key::D).isPress)
		key = shu::Key::D;
	if (shu::InputKey::GetKeyStatus(shu::Key::A).isPress)
		key = shu::Key::A;

	if (m_status == Player_Status::Climb)
	{
		if (m_animation->GetNowAnimation() == "into_climb" && m_animation->GetNowFrame() == 8)
		{
			m_animation->SetAnimation("climb");
		}
	}
}

void Player::UpdataMove(shu::Key& key)
{
	// 更新加速度
	float moveAcc = 1800.0f;	// 移动加速度
	float fricAcc = 1000.0f;	// 地面摩擦力加速度
	float airfAcc = 100.0f;		// 空气阻力加速度
	switch (key)
	{
	case shu::Key::D:
	{
		if (shu::InputKey::GetKeyStatus(shu::Key::D).isHold)
		{
			m_hitbox->GetHitbox().acceleration.x = moveAcc;	// 移动加速度
		}
		else
		{
			if (m_hitbox->GetHitbox().speed.x > 0.0f)
			{
				if (m_status == Player_Status::Ground)
					m_hitbox->GetHitbox().acceleration.x = -fricAcc;	// 地面摩擦力加速度
				else
					m_hitbox->GetHitbox().acceleration.x = -airfAcc;	// 空气阻力加速度
			}
			else
			{
				m_hitbox->GetHitbox().acceleration.x = 0.0f;
				m_hitbox->GetHitbox().speed.x = 0.0f;
			}
		}
		break;
	}
	case shu::Key::A:
	{
		if (shu::InputKey::GetKeyStatus(shu::Key::A).isHold)
		{
			m_hitbox->GetHitbox().acceleration.x = -moveAcc;
		}
		else
		{
			if (m_hitbox->GetHitbox().speed.x < 0.0f)
			{
				if (m_status == Player_Status::Ground)
					m_hitbox->GetHitbox().acceleration.x = fricAcc;
				else if (m_status == Player_Status::Air)
					m_hitbox->GetHitbox().acceleration.x = airfAcc;
			}
			else
			{
				m_hitbox->GetHitbox().acceleration.x = 0.0f;
				m_hitbox->GetHitbox().speed.x = 0.0f;
			}
		}
		break;
	}
	}

}

void Player::UpdataCollide(float dt)
{
	shu::vec2f coll_pos, coll_normal;
	float coll_time;

	bool flag = false;
	for (auto& it : m_leaves)
	{
		if (((LeaveObject*)it)->GetHitbox().pos.y >= this->GetHitbox().pos.y + this->GetHitbox().size.y)
		{
			if (HitboxComponent::CollideRectVsMoveRect(this->GetHitbox(), ((LeaveObject*)it)->GetHitbox(),
				coll_pos, coll_normal, coll_time, dt))
			{
				flag = true;
				this->SetStatus(Player_Status::Ground);
				((LeaveObject*)it)->OnEvent(Event::StepOn);
			}
		}
	}
	if (flag == false) this->SetStatus(Player_Status::Air);
}

void Player::UpdataSpeed(float dt)
{
	// 更新速度
	m_hitbox->GetHitbox().speed += m_hitbox->GetHitbox().acceleration * dt;
	// 限制一下玩家的速度
	if (m_hitbox->GetHitbox().speed.x >= 250.0f) m_hitbox->GetHitbox().speed.x = 250.0f;
	if (m_hitbox->GetHitbox().speed.x <= -250.0f) m_hitbox->GetHitbox().speed.x = -250.0f;
}


