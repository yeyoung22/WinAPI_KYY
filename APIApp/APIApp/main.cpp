#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineMath.h>

void TestGameStart()
{
	int a = 0;
}

int x = 0;

void TestGameLoop()
{
	// ȭ�鿡 �׸��� �׷��ִ� �Լ��Դϴ�.

	++x;

	Rectangle(GameEngineWindow::GetDrawHdc(), 0 + x, 0, 100 + x, 100);

	// ���Ͱ� �����̰� �����
	// �÷��̾ �����̰� ������ �Ѵ�.
	int a = 0;
}

void TestGameEnd()
{
	int a = 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineDebug::LeakCheck();

	GameEngineWindow::WindowCreate(hInstance, "MainWindow", { 1280, 720 }, { 0, 0 });

	GameEngineWindow::WindowLoop(TestGameStart, TestGameLoop, TestGameEnd);


	// main�� ������ ���α׷� �����
	// �ٷ� ������� �ʰ� ������ ��

	return 1;
}