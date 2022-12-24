#pragma once
#include "HitboxComponent.h"
#include "AnimationComponent.h"
#include "GameData.h"
#include "../GameEngine/GameEngine.h"

// 事件通知
enum class Event { StepOn/*被踩到*/, Grab/*被抓住*/, Jump/*跳跃*/, BeginPlay33Animation, EndPlay33Animation };

// 叶子的类型
enum class Type { Normal/*正常*/, Trap/*陷阱*/, Lucky/*幸运*/ };

// 玩家的状态
enum class Player_Status { Ground/*在地面*/, Air/*空中*/, Lock/*锁住*/, Climb/*抓攀*/ };

// 幸运叶子状态
enum class Lucky_Status { Idle/*静态*/, Move/*移动*/ };

// 陷阱叶子状态
enum class Trap_Status { Idle/*静态*/, Timeing/*计时*/, Goneing/*消失中*/, Gone/*彻底消失*/ };


/////////////////////////////////////////////////////////////////////////////////////////

// 基础类
class Entity
{
public:
	Entity() {};
	virtual ~Entity() {};

	virtual bool Init() { return true; };
	virtual void Updata(float dt) = 0;
	virtual void Render(shu::Direct2dRender& rt) = 0;
	virtual void OnEvent(Event event) = 0;

	bool isDelete = false;	// 是否销毁
	float m_all_time = 0.0f;
};


/////////////////////////////////////////////////////////////////////////////////////////

// 基础类叶子
class LeaveObject : public Entity
{
public:

	LeaveObject() {};
	virtual ~LeaveObject();

	virtual void Updata(float dt) = 0;
	virtual void Render(shu::Direct2dRender& rt) = 0;
	virtual void OnEvent(Event event) = 0;

	void SetPlayerPtr(Entity* ptr);

	HitBox& GetHitbox();
	HitBox& GetHitbox2();
	HitboxComponent* GetHitboxComponent();
	HitboxComponent* GetHitboxComponent2();
	AnimationComponent* GetAnimationComponent();
	Type GetType();

protected:
	bool InitHitboxComponent(HitBox hitbox);
	bool InitHitboxComponent2(HitBox hitbox);
	bool InitAnimationComponent(const std::wstring& bitmapFile, const std::wstring& jsonFile, float duration);

	float rand_num = 0.0f;

	Entity* m_player = nullptr;	// 指向玩家的指针

	HitboxComponent* m_hitbox = nullptr;
	HitboxComponent* m_hitbox2 = nullptr;
	AnimationComponent* m_animation = nullptr;
	ID2D1Bitmap1* m_bitmap = nullptr;

	Type m_type = Type::Normal;
};


/////////////////////////////////////////////////////////////////////////////////////////

// 基础类玩家
class PlayerObject : public Entity
{
public:
	PlayerObject() {};
	virtual ~PlayerObject();

	virtual void Updata(float dt) = 0;
	virtual void Render(shu::Direct2dRender& rt) = 0;
	virtual void OnEvent(Event event) = 0;

	void SetStatus(Player_Status status);

	HitBox& GetHitbox();
	HitBox& GetHitbox2();
	HitboxComponent* GetHitboxComponent();
	HitboxComponent* GetHitboxComponent2();
	AnimationComponent* GetAnimationComponent();

protected:
	bool InitHitboxComponent(HitBox hitbox);
	bool InitHitboxComponent2(HitBox hitbox);
	bool InitAnimationComponent(const std::wstring& bitmapFile, const std::wstring& jsonFile, float duration);

	HitboxComponent* m_hitbox = nullptr;
	HitboxComponent* m_hitbox2 = nullptr;
	AnimationComponent* m_animation = nullptr;
	ID2D1Bitmap1* m_bitmap = nullptr;

	Player_Status m_status = Player_Status::Air;
	Player_Status m_last_status = Player_Status::Air;
};


