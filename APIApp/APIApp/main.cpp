#include <Windows.h>
#include <GameEngineContents/SuperMarioCore.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	SuperMarioCore::GetInst().CoreStart(hInstance);

	// main이 끝나면 프로그램 종료됨
	// 바로 종료되지 않게 잡아줘야 함
	return 1;
}