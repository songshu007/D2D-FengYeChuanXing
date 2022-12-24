#pragma once
#include <thread>
#include "Render.h"
#include "InputKey.h"
#include "Resource.h"

namespace shu
{
	class GameEngine
	{
	public:
		GameEngine();
		~GameEngine();

		bool Init(std::wstring className, std::wstring wndName, vec2i size, long style = WS_OVERLAPPEDWINDOW);
		void Start();

		virtual bool OnUserCreate() { return true; };
		virtual bool OnUserUpdata(float dt) { return true; };
		virtual bool OnDisCreate() { return true; };

		Direct2dRender& GetRT();

	protected:
		Direct2dRender m_rt;
		uint32_t GetFPS();
		vec2f& GetMousePos();


	private:
		static GameEngine* m_ptr;

		HWND m_hwnd;

		std::wstring m_ClassName;
		std::wstring m_WindowName;
		std::chrono::system_clock::time_point m_cp1, m_cp2;

		uint32_t m_lastFPS;
		float m_dt;
		std::atomic<bool> isClose;	// 使用原子操作避免两个线程相互干扰

		// 按键管理
		InputKey Key_;

		// 鼠标位置
		vec2f m_MousePos;

		// 资源管理类
		std::unique_ptr<Resource> m_res;

		// 日志
		Loger Log;

		// 以下是私有函数声明
		static LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void MessageLoop();
		HWND _CreateWindow(vec2i size, long style);
		void RenderLoop();
		void CoreUpdata();

	};

}

