#pragma once
#include "Entity.h"

class Shamrock4 : public LeaveObject
{
public:
	Shamrock4();
	virtual ~Shamrock4();

	virtual bool Init() override;
	virtual void Updata(float dt) override;
	virtual void Render(shu::Direct2dRender& rt) override;
	virtual void OnEvent(Event event) override;

private:
	void UpdataAnimation(float dt);

	bool isGrab = false;
};

