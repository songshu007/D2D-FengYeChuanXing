#include "EmptyEntity.h"

EmptyEntity::EmptyEntity()
{
	this->InitHitboxComponent(HitBox{ {10.0f, 500.0f}, {1920.0f, 40.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} });
	this->InitHitboxComponent2(HitBox{ {0.0f, 0.0f}, {-100.0f, -100.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} });
}

EmptyEntity::~EmptyEntity()
{
}

void EmptyEntity::Updata(float dt)
{
	this->GetHitbox().pos.x = GameData::camera.x + 10.0f;
}

void EmptyEntity::Render(shu::Direct2dRender& rt)
{
	m_hitbox->Render(rt);
}

void EmptyEntity::OnEvent(Event event)
{
}
