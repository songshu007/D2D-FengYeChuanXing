#pragma once
#include "Entity.h"

class Shamrock3 : public LeaveObject
{
public:
	Shamrock3();
	virtual ~Shamrock3();

	virtual bool Init() override;
	virtual void Updata(float dt) override;
	virtual void Render(shu::Direct2dRender& rt) override;
	virtual void OnEvent(Event event) override;

private:
	void UpdataAnimation(float dt);

	bool isGrab = false;
};

