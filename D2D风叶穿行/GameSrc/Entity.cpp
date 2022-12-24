#include "Entity.h"

LeaveObject::~LeaveObject()
{
	if (m_hitbox != nullptr) delete m_hitbox;
	if (m_hitbox2 != nullptr) delete m_hitbox2;
	if (m_animation != nullptr) delete m_animation;
}

void LeaveObject::SetPlayerPtr(Entity* ptr)
{
	m_player = ptr;
}

HitBox& LeaveObject::GetHitbox()
{
	return m_hitbox->GetHitbox();
}

HitBox& LeaveObject::GetHitbox2()
{
	return m_hitbox2->GetHitbox();
}

HitboxComponent* LeaveObject::GetHitboxComponent()
{
	return m_hitbox;
}

HitboxComponent* LeaveObject::GetHitboxComponent2()
{
	return m_hitbox2;
}

AnimationComponent* LeaveObject::GetAnimationComponent()
{
	return m_animation;
}

Type LeaveObject::GetType()
{
	return m_type;
}

bool LeaveObject::InitHitboxComponent(HitBox hitbox)
{
	this->m_hitbox = new HitboxComponent(hitbox);
	return true;
}

bool LeaveObject::InitHitboxComponent2(HitBox hitbox)
{
	this->m_hitbox2 = new HitboxComponent(hitbox);
	return true;
}

bool LeaveObject::InitAnimationComponent(const std::wstring& bitmapFile, const std::wstring& jsonFile, float duration)
{
	this->m_animation = new AnimationComponent();
	return m_animation->CreateAnimation(bitmapFile, jsonFile, duration);
}


/////////////////////////////////////////////////////////////////////////////////////////

PlayerObject::~PlayerObject()
{
	if (m_hitbox != nullptr) delete m_hitbox;
	if (m_hitbox2 != nullptr) delete m_hitbox2;
	if (m_animation != nullptr) delete m_animation;
}

void PlayerObject::SetStatus(Player_Status status)
{
	m_last_status = m_status;
	m_status = status;
}

HitBox& PlayerObject::GetHitbox()
{
	return m_hitbox->GetHitbox();
}

HitBox& PlayerObject::GetHitbox2()
{
	return m_hitbox2->GetHitbox();
}

HitboxComponent* PlayerObject::GetHitboxComponent()
{
	return m_hitbox;
}

HitboxComponent* PlayerObject::GetHitboxComponent2()
{
	return m_hitbox2;
}

AnimationComponent* PlayerObject::GetAnimationComponent()
{
	return m_animation;
}

bool PlayerObject::InitHitboxComponent(HitBox hitbox)
{
	this->m_hitbox = new HitboxComponent(hitbox);
	return true;
}

bool PlayerObject::InitHitboxComponent2(HitBox hitbox)
{
	this->m_hitbox2 = new HitboxComponent(hitbox);
	return true;
}

bool PlayerObject::InitAnimationComponent(const std::wstring& bitmapFile, const std::wstring& jsonFile, float duration)
{
	this->m_animation = new AnimationComponent();
	return m_animation->CreateAnimation(bitmapFile, jsonFile, duration);
}
