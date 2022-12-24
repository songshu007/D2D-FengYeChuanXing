#include "LeaveFactory.h"

LeaveFactory::LeaveFactory()
{
}

LeaveFactory::~LeaveFactory()
{
}

Entity* LeaveFactory::GetLeave(LeaveType type)
{
	Entity* entity = nullptr;

	switch (type)
	{
	case LeaveType::Shamrock1:
	{
		entity = new Shamrock1();
		if (!entity->InitHitboxComponent(HitBox{ {0.0f, 0.0f}, {65.0f, 40.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} })) return nullptr;
		if (!entity->InitHitboxComponent2(HitBox{ {0.0f, 0.0f}, {5.0f, 5.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} })) return nullptr;
		if (!entity->InitAnimationComponent(L"res/img/shamrock1.png", L"res/json/shamrock1.json", 0.1f)) return nullptr;
		entity->GetAnimationComponent()->SetAnimation("idle");
		break;
	}
	case LeaveType::Shamrock2:
	{
		entity = new Shamrock2();
		if (!entity->InitHitboxComponent(HitBox{ {0.0f, 0.0f}, {80.0f, 40.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} })) return nullptr;
		if (!entity->InitHitboxComponent2(HitBox{ {0.0f, 0.0f}, {5.0f, 5.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} })) return nullptr;
		if (!entity->InitAnimationComponent(L"res/img/shamrock2.png", L"res/json/shamrock2.json", 0.1f)) return nullptr;
		entity->GetAnimationComponent()->SetAnimation("idle");
		break;
	}
	case LeaveType::Shamrock3:
	{
		entity = new Shamrock3();
		if (!entity->InitHitboxComponent(HitBox{ {0.0f, 0.0f}, {95.0f, 40.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} })) return nullptr;
		if (!entity->InitHitboxComponent2(HitBox{ {0.0f, 0.0f}, {5.0f, 5.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} })) return nullptr;
		if (!entity->InitAnimationComponent(L"res/img/shamrock3.png", L"res/json/shamrock3.json", 0.1f)) return nullptr;
		entity->GetAnimationComponent()->SetAnimation("idle");
		break;
	}
	case LeaveType::Shamrock4:
	{
		entity = new Shamrock4();
		if (!entity->InitHitboxComponent(HitBox{ {0.0f, 0.0f}, {65.0f, 40.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} })) return nullptr;
		if (!entity->InitHitboxComponent2(HitBox{ {0.0f, 0.0f}, {5.0f, 5.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} })) return nullptr;
		if (!entity->InitAnimationComponent(L"res/img/shamrock4.png", L"res/json/shamrock4.json", 0.1f)) return nullptr;
		entity->GetAnimationComponent()->SetAnimation("idle");
		break;
	}
	case LeaveType::Shamrock_trap:
	{
		entity = new Shamrock_trap();
		if (!entity->InitHitboxComponent(HitBox{ {0.0f, 0.0f}, {65.0f, 40.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} })) return nullptr;
		if (!entity->InitHitboxComponent2(HitBox{ {0.0f, 0.0f}, {5.0f, 5.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} })) return nullptr;
		if (!entity->InitAnimationComponent(L"res/img/shamrock_trap.png", L"res/json/shamrock_trap.json", 0.1f)) return nullptr;
		entity->GetAnimationComponent()->SetAnimation("idle");
		break;
	}
	case LeaveType::Shamrock_lucky:
	{
		entity = new Shamrock_lucky();
		if (!entity->InitHitboxComponent(HitBox{ {0.0f, 0.0f}, {65.0f, 40.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} })) return nullptr;
		if (!entity->InitHitboxComponent2(HitBox{ {0.0f, 0.0f}, {5.0f, 5.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} })) return nullptr;
		if (!entity->InitAnimationComponent(L"res/img/shamrock_lucky.png", L"res/json/shamrock_lucky.json", 0.1f)) return nullptr;
		entity->GetAnimationComponent()->SetAnimation("idle");
		break;
	}
	default:
		break;
	}


	return entity;
}
