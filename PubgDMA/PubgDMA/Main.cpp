#include "pch.h"
#include "Memory.h"
#include "CheatFunction.h"
#include "Globals.h"
#include "Init.h"
#include "GUI.h"
#include "Engine.h"
#include "WebRadar.h"
#include <random>
std::shared_ptr<Engine> EngineInstance;
std::unique_ptr<WebRadar> WebRadarInstance;
std::string ProcessName;

// Generates a random alphanumeric wide string — different each run
static std::wstring RandName(size_t len = 12)
{
	static const wchar_t pool[] = L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	std::mt19937_64 rng(GetCurrentProcessId() ^ GetTickCount64());
	std::uniform_int_distribution<size_t> dist(0, 61);
	std::wstring s(len, L'\0');
	for (auto& c : s) c = pool[dist(rng)];
	return s;
}

#ifdef _DEBUG
static LONG WINAPI CrashHandler(EXCEPTION_POINTERS* ep)
{
	printf("\n[CRASH] Exception 0x%08X at 0x%llx\n",
		ep->ExceptionRecord->ExceptionCode,
		(uint64_t)ep->ExceptionRecord->ExceptionAddress);
	if (ep->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
		printf("[CRASH] Access violation %s address 0x%llx\n",
			ep->ExceptionRecord->ExceptionInformation[0] ? "writing" : "reading",
			ep->ExceptionRecord->ExceptionInformation[1]);
	fflush(stdout);
	printf("Press ENTER to exit...\n");
	getchar();
	return EXCEPTION_CONTINUE_SEARCH;
}
#endif

void main()
{
	bool gamefound = true;
	ProcessName = "TslGame.exe";
	if (TargetProcess.Init("TslGame.exe", true, false))
	{
		ProcessName = "TslGame.exe";
	}
	else if (TargetProcess.Init("TslGame.exe", true, false))
	{
		ProcessName = "TslGame.exe";

	}
	else
	{
		printf("Failed to find game\n");
		return;
	}
	TargetProcess.FixCr3();

	uint64_t base = TargetProcess.GetBaseAddress(ProcessName);
	uint64_t size = TargetProcess.GetBaseSize(ProcessName);
	EngineInstance = std::make_shared<Engine>();
	EngineInstance->Cache();

	WebRadarInstance = std::make_unique<WebRadar>();
	WebRadarInstance->Start();
}
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	InputWndProc(hWnd, message, wParam, lParam);
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wc;

#ifdef _DEBUG
	AllocConsole();
	FILE* fDummy;
	freopen_s(&fDummy, LIT("CONIN$"), LIT("r"), stdin);
	freopen_s(&fDummy, LIT("CONOUT$"), LIT("w"), stderr);
	freopen_s(&fDummy, LIT("CONOUT$"), LIT("w"), stdout);
	printf(LIT("Debugging Window:\ninizializing...\n"));
	AddVectoredExceptionHandler(1, CrashHandler);
#endif

	main();

	// Random class and window names — different each launch
	std::wstring wndClass = RandName();
	std::wstring wndTitle = RandName();

	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = wndClass.c_str();
	RegisterClassEx(&wc);

	// WS_EX_TOOLWINDOW hides from taskbar and Alt+Tab
	// WS_EX_LAYERED required for SetLayeredWindowAttributes
	hWnd = CreateWindowEx(
		WS_EX_TOOLWINDOW | WS_EX_LAYERED,
		wndClass.c_str(), wndTitle.c_str(),
		WS_POPUP,
		0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
		NULL, NULL, hInstance, NULL);

	if (!hWnd)
		return -1;

	SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 255, LWA_ALPHA);
	ShowWindow(hWnd, nCmdShow);

#ifdef _DEBUG
	// Keep console visible but behind overlay in debug
	ShowWindow(GetConsoleWindow(), SW_SHOW);
#else
	// Hide console in release — no visible window besides the overlay
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

	InitD2D(hWnd);
	CreateGUI();
	MSG msg;
	SetProcessDPIAware();
	SetInput();
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		RenderFrame();
	}
	CleanD2D();
	return msg.wParam;
}
