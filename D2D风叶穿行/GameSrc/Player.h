#pragma once
#include "Entity.h"
#include "./Shamrock_lucky.h"

enum class status_33 { None, Fly, Blow, Into_dizzy, Dizzy };

class Player : public PlayerObject
{
public:

	Player(std::vector<Entity*>& leaves);
	virtual ~Player();

	virtual void Updata(float dt);
	virtual void Render(shu::Direct2dRender& rt);
	virtual void OnEvent(Event event);


private:
	void UpdataAnimation(float dt);
	void UpdataMove(shu::Key& key);
	void UpdataCollide(float dt);
	void UpdataSpeed(float dt);

	void Updata33(float dt);
	void Draw33(shu::Direct2dRender& rt);

	AnimationComponent* m_33animation = nullptr;
	ID2D1Bitmap1* m_33bitmap = nullptr;
	shu::vec2f m_33pos = shu::vec2f(0.0f, 0.0f);
	status_33 m_33status = status_33::None;
	
	std::vector<Entity*>& m_leaves;
};

