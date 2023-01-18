#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineContents/SuperMarioCore.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	SuperMarioCore::GetInst().CoreStart(hInstance);
	return 1;
}