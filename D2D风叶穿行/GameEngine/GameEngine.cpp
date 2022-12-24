#include "GameEngine.h"

shu::GameEngine* shu::GameEngine::m_ptr = nullptr;

shu::GameEngine::GameEngine()
	: m_hwnd(nullptr),
	isClose(false),
	m_lastFPS(0),
	m_dt(0.0f),
	m_res(nullptr)
{
	m_ptr = this;
}

shu::GameEngine::~GameEngine()
{

}

bool shu::GameEngine::Init(std::wstring className, std::wstring wndName, vec2i size, long style)
{
	SetProcessDPIAware();

	m_ClassName = className;
	m_WindowName = wndName;
	m_hwnd = _CreateWindow(size, style);
	if (m_hwnd == nullptr) return false;

	if (!m_rt.Init(m_hwnd)) return false;

	m_res = std::make_unique<Resource>(m_rt);	// 初始化资源管理类

	if (!OnUserCreate()) return false;

	m_cp1 = std::chrono::system_clock::now();
	m_cp2 = std::chrono::system_clock::now();

	return true;
}

void shu::GameEngine::Start()
{
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	std::thread t(&GameEngine::RenderLoop, this);
	MessageLoop();
	t.join();
	OnDisCreate();
}

shu::Direct2dRender& shu::GameEngine::GetRT()
{
	return m_rt;
}

uint32_t shu::GameEngine::GetFPS()
{
	return m_lastFPS;
}

shu::vec2f& shu::GameEngine::GetMousePos()
{
	return m_MousePos;
}

LRESULT shu::GameEngine::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	shu::GameEngine& ptr = *m_ptr;
	switch (uMsg)
	{
	case WM_CLOSE:
	{
		ptr.isClose = true;
		PostQuitMessage(0);
		break;
	}
	case WM_SIZE:
	{
		ptr.m_rt.ChangeSize(LOWORD(lParam), HIWORD(lParam));
		break;
	}
	case WM_KEYDOWN: 
	{
		InputKey::UpdataKeyStatus(static_cast<uint32_t>(wParam), true);
		break;
	}
	case WM_KEYUP:
	{
		InputKey::UpdataKeyStatus(static_cast<uint32_t>(wParam), false);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		InputKey::UpdataKeyStatus(static_cast<uint32_t>(Key::LBUTTON), true);
		break;
	}
	case WM_LBUTTONUP:
	{
		InputKey::UpdataKeyStatus(static_cast<uint32_t>(Key::LBUTTON), false);
		break;
	}
	case WM_MOUSEMOVE:
	{
		ptr.m_MousePos.x = LOWORD(lParam);
		ptr.m_MousePos.y = HIWORD(lParam);
		break;
	}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void shu::GameEngine::MessageLoop()
{
	MSG msg = { 0 };
	while (GetMessageW(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

HWND shu::GameEngine::_CreateWindow(vec2i size, long style)
{
	HWND hwnd = nullptr;
	WNDCLASSEXW wic;
	HINSTANCE hInstance = GetModuleHandleW(NULL);
	memset(&wic, 0, sizeof(wic));
	wic.cbSize = sizeof(WNDCLASSEX);
	wic.hCursor = LoadCursor(0, IDC_ARROW);
	wic.hInstance = hInstance;
	wic.lpszClassName = m_ClassName.c_str();
	wic.lpfnWndProc = WindowProc;
	wic.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wic))
		return nullptr;

	RECT rect;
	rect.right = size.x;
	rect.bottom = size.y;
	rect.left = 0;
	rect.top = 0;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	hwnd = CreateWindowEx(0, m_ClassName.c_str(), m_WindowName.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, NULL);
	return hwnd;
}

void shu::GameEngine::RenderLoop()
{
	srand((unsigned int)time(NULL));
	while (!isClose)
	{
		if (GetForegroundWindow() != m_hwnd)
		{
			// 防止最小化时CPU爆炸，你懂的
			Sleep(5);
		}
		CoreUpdata();

		OnUserUpdata(m_dt);
	}
}

void shu::GameEngine::CoreUpdata()
{
	static float FrameTimer = 0.0f;
	static uint32_t FrameCount = 0;

	// 更新帧间隔
	m_cp1 = std::chrono::system_clock::now();
	std::chrono::duration<float> t = m_cp1 - m_cp2;
	m_cp2 = m_cp1;
	m_dt = t.count();

	// 更新FPS
	FrameTimer += m_dt;
	FrameCount++;
	if (FrameTimer >= 1.0f)
	{
		FrameTimer -= 1.0f;
		m_lastFPS = FrameCount;
		FrameCount = 0;
	}
	std::wstring title = m_WindowName + L" FPS: " + std::to_wstring(m_lastFPS);
	::SetWindowTextW(m_hwnd, title.c_str());

	// 更新按键
	InputKey::Updata();

}
