#pragma once
#include "Entity.h"

class Shamrock_lucky : public LeaveObject
{
public:
	// 这个枚举记录玩家是踩着叶子还是抓着叶子
	enum class Status { None, Step, Grab };

	Shamrock_lucky();
	virtual ~Shamrock_lucky();

	virtual bool Init() override;
	virtual void Updata(float dt) override;
	virtual void Render(shu::Direct2dRender& rt) override;
	virtual void OnEvent(Event event) override;

	void SetStatus(Lucky_Status status);

private:
	void UpdataAnimation(float dt);

	bool isUsed = false;
	float BeginMoveTime = 0.0f;

	Status m_player_status = Status::None;
	Lucky_Status m_status = Lucky_Status::Idle;
	Lucky_Status m_last_status = Lucky_Status::Idle;
};