#pragma once
#include "Entity.h"

class Shamrock_trap : public LeaveObject
{
public:
	Shamrock_trap();
	virtual ~Shamrock_trap();

	virtual bool Init() override;
	virtual void Updata(float dt) override;
	virtual void Render(shu::Direct2dRender& rt) override;
	virtual void OnEvent(Event event) override;

	void SetStatus(Trap_Status status);

private:
	void UpdataAnimation(float dt);

	bool isUsed = false;
	bool isGrep = false;
	float BeginTime = 0.0f;

	Trap_Status m_status = Trap_Status::Idle;
	Trap_Status m_last_status = Trap_Status::Idle;
};

