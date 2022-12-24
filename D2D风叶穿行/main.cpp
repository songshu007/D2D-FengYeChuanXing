#include <iostream>
#include <vector>
#include "./GameEngine/GameEngine.h"
#include "./GameSrc/AnimationManage.h"
#include "./GameSrc/EmptyEntity.h"
#include "./GameSrc/Player.h"
#include "./GameSrc/Shamrock_lucky.h"
#include "./GameSrc/Shamrock_trap.h"
#include "./GameSrc/Shamrock1.h"
#include "./GameSrc/Shamrock2.h"
#include "./GameSrc/Shamrock3.h"
#include "./GameSrc/Shamrock4.h"
#include "./GameSrc/GameData.h"
#include "./GameSrc/BackGround.h"
#include "./GameSrc/Particle.h"
#include "./GameSrc/Wind.h"
#include "./GameSrc/Swallow.h"

enum class Game_Status { GetReady, Play, GameOver };

class MyGame : public shu::GameEngine
{
public:
	virtual bool OnUserCreate() override
	{
		am = std::make_unique<AnimationManage>(m_rt);	// 初始化动画管理类

		m_player = new Player(m_leaves);
		
		if (!m_bg.Init()) return false;
		if (!m_wind.Init()) return false;

		if (!m_count_animation.CreateAnimation(L"res\\img\\count.png", L"res\\json\\count.json", 1.0f)) return false;
		if (!m_swallow.Init()) return false;

		if (!Reset()) return false;
		return true;
	};

	virtual bool OnUserUpdata(float dt) override
	{
		m_all_time += dt;
		GameData::score = m_all_time;
		// 碰撞箱显示
		if (shu::InputKey::GetKeyStatus(shu::Key::H).isPress) HitboxComponent::isShowHitbox = !HitboxComponent::isShowHitbox;

		switch (m_status)
		{
		case Game_Status::GetReady:
		{
			m_player->Updata(0.0f);
			for (auto& it : m_leaves) it->Updata(0.0f);
			m_bg.Updata(0.0f);
			m_particle.Updata(0.0f);
			m_wind.Updata(0.0f);
			m_count_animation.Updata(dt);

			m_rt.BeginDraw();
			m_rt.Clear({ 159.0f / 255.0f, 225.0f / 255.0f, 221.0f / 255.0f, 1.0f });
			m_bg.Render(m_rt);
			m_particle.Render(m_rt);
			for (auto& it : m_leaves) it->Render(m_rt);
			m_player->Render(m_rt);
			m_wind.Render(m_rt);
			m_rt.DrawBitmap(m_count_animation.GetBitmap(), shu::vec2f(700.0f, 0.0f), shu::vec2f(100.0f, 100.0f));
			m_rt.EndDraw();

			if (m_count_animation.isEnd()) m_status = Game_Status::Play;

			break;
		}
		case Game_Status::Play:
		{
			// 删掉出窗口的叶子
			for (auto it = m_leaves.begin(); it != m_leaves.end();)
			{
				if (((LeaveObject*)(*it))->GetHitboxComponent()->GetPos().x <= GameData::camera.x - 200.0f)
				{
					it = m_leaves.erase(it);
				}
				else
				{
					it++;
				}
			}

			// 更新
			m_player->Updata(dt);
			for (auto& it : m_leaves) it->Updata(dt);
			m_bg.Updata(dt);
			m_particle.Updata(dt);
			m_wind.Updata(dt);
			m_swallow.Updata(dt);

			// 渲染
			m_rt.BeginDraw();
			m_rt.Clear({ 159.0f / 255.0f, 225.0f / 255.0f, 221.0f / 255.0f, 1.0f });

			m_bg.Render(m_rt);
			m_particle.Render(m_rt);
			m_swallow.Render(m_rt);
			for (auto& it : m_leaves) it->Render(m_rt);
			m_player->Render(m_rt);
			m_wind.Render(m_rt);

			GameData::camera.x += GameData::camera_speed * dt;
			if (m_player->GetHitboxComponent()->GetPos().y < 0.0f) GameData::camera.y = m_player->GetHitboxComponent()->GetPos().y;
			else GameData::camera.y = 0.0f;
			if (m_player->GetHitbox().pos.y > 600.0f) m_status = Game_Status::GameOver;
			if (m_player->GetHitbox().pos.x + m_player->GetHitbox().size.x < GameData::camera.x) m_status = Game_Status::GameOver;
			m_rt.GetDC().SetTransform(D2D1::Matrix3x2F::Translation(GameData::camera.x * -1, GameData::camera.y * -1));
			m_rt.EndDraw();

			// 每隔一段时间生成叶子
			if (m_all_time - m_last_time >= 1.0f)
			{
				m_last_time = m_all_time;
				CreateLeaves();
			}

			break;
		}
		case Game_Status::GameOver:
		{
			m_player->Updata(0.0f);
			for (auto& it : m_leaves) it->Updata(0.0f);
			m_bg.Updata(0.0f);
			m_particle.Updata(dt);
			m_wind.Updata(dt);

			m_rt.BeginDraw();
			m_rt.Clear({ 159.0f / 255.0f, 225.0f / 255.0f, 221.0f / 255.0f, 1.0f });
			m_bg.Render(m_rt);
			m_particle.Render(m_rt);
			for (auto& it : m_leaves) it->Render(m_rt);
			m_player->Render(m_rt);
			m_wind.Render(m_rt);
			m_rt.DrawTextCenter(L"按“Z”键重试", shu::vec2f(GameData::camera.x, 0.0f), shu::vec2f(1920.0f, 500.0f), shu::Color::Black, 50.0f);
			m_rt.EndDraw();

			if (shu::InputKey::GetKeyStatus(shu::Key::Z).isPress) this->Reset();

			break;
		}
		default:
			break;
		}

		
		return false;
	};

	virtual bool OnDisCreate() override
	{
		delete m_player;
		for (auto& it : m_leaves) delete it;
		return true;
	}

	bool Reset()
	{
		m_all_time = 0.0f;
		m_last_time = 0.0f;
		GameData::camera = shu::vec2f(0.0f, 0.0f);
		GameData::camera_speed = 150.0f;

		for (auto& it : m_leaves) delete it;
		m_leaves.clear();

		m_leaves.push_back(new Shamrock1());
		m_leaves.push_back(new Shamrock2());
		m_leaves.push_back(new Shamrock_trap());
		m_leaves.push_back(new Shamrock3());
		m_leaves.push_back(new Shamrock4());
		m_leaves.push_back(new Shamrock3());
		m_leaves.push_back(new Shamrock1());
		m_leaves.push_back(new Shamrock4());
		m_leaves.push_back(new Shamrock1());
		m_leaves.push_back(new Shamrock3());
		m_leaves.push_back(new Shamrock2());

		for (auto& it : m_leaves)
		{
			((LeaveObject*)it)->SetPlayerPtr(m_player);
			if (!it->Init()) return false;
		}

		float b = 700.0f;
		for (size_t i = 0; i != m_leaves.size(); ++i)
		{
			((LeaveObject*)m_leaves[i])->GetHitboxComponent()->SetPos(shu::vec2f(b, 200.0f));
			b += 150.0f;
		}

		m_player->GetHitboxComponent()->SetPos(shu::vec2f(700.0f, 0.0f));
		m_player->GetHitbox().speed = shu::vec2f(0.0f, 0.0f);
		m_player->GetHitbox().acceleration = shu::vec2f(0.0f, 0.0f);

		m_rt.GetDC().SetTransform(D2D1::Matrix3x2F::Translation(0.0f, 0.0f));
		m_swallow.Reset();

		m_count_animation.SetFrame(0);

		m_status = Game_Status::GetReady;

		return true;
	}

	bool CreateLeaves()
	{
		int num = rand() % 101;

		Entity* entity = nullptr;

		if (num >= 0 && num <= 5)
			entity = new Shamrock_lucky();
		if (num >= 6 && num <= 20)
			entity = new Shamrock_trap();
		if (num >= 21 && num <= 40)
			entity = new Shamrock1();
		if (num >= 41 && num <= 60)
			entity = new Shamrock2();
		if (num >= 61 && num <= 80)
			entity = new Shamrock3();
		if (num >= 81 && num <= 100)
			entity = new Shamrock4();

		if (!entity->Init()) return false;
		((LeaveObject*)entity)->SetPlayerPtr(m_player);
		((LeaveObject*)entity)->GetHitboxComponent()->SetPos(shu::vec2f(
			GameData::camera.x + GameData::screen_size.x + 200.0f + (rand() % 100) - 50,
			rand() % 200 + 100
			));

		m_leaves.push_back(entity);
		return true;
	}

private:
	// 玩家
	Player* m_player;
	// 叶子
	std::vector<Entity*> m_leaves;
	// 背景
	BackGround m_bg;
	// 下落树叶
	Particle m_particle;
	// 风
	Wind m_wind;
	// 燕子
	Swallow m_swallow;

	AnimationComponent m_count_animation;

	Game_Status m_status = Game_Status::GetReady;

	std::unique_ptr<AnimationManage> am;

	float m_all_time = 0.0f;
	float m_last_time = 0.0f;
};

int main()
{
	srand(time(NULL));
	GameData data;

	MyGame Game;
	if (Game.Init(L"Game", L"风叶穿行", shu::vec2i(GameData::screen_size.x, GameData::screen_size.y) ))
	{
		Game.Start();
	}
	else
	{
		::MessageBoxW(NULL, L"您的游戏好像并不想启动！请不要修改游戏的资源文件！", L"出大事了！", MB_OK | MB_ICONERROR);
	}

	return 0;
}
