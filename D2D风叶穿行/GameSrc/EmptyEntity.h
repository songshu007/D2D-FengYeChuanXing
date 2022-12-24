#pragma once
#include "Entity.h"

class EmptyEntity : public LeaveObject
{
public:
	EmptyEntity();
	virtual ~EmptyEntity();

	virtual void Updata(float dt);
	virtual void Render(shu::Direct2dRender& rt);
	virtual void OnEvent(Event event);

private:

};

