#pragma once
#include <string>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>

// 설명 :
class GameEngineWindow
{
public:
	// 윈도우를 만들어 주는 기능
	static void WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName);

	static void WindowSize(float4 _Size);
	static void WindowPos(float4 _Pos);

	static int WindowLoop();





	// constrcuter destructer
	GameEngineWindow();
	~GameEngineWindow();

	// delete Function
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

protected:

private:
	static HWND hWnd;
};

