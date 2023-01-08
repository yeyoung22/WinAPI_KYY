#pragma once
#include <string>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>


// 설명 :윈도우와 관련된 기능
class GameEngineWindow
{
public:
	// 윈도우를 만들어 주는 기능
	static void WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos);

	static void SettingWindowSize(float4 _Size);
	static void SettingWindowPos(float4 _Pos);

	//Window Handle값을 반환하는 함수
	static HWND GetHWnd()
	{
		return HWnd;
	}

	//그리기 권한을 반환하는 함수
	static HDC GetDrawHdc()
	{
		return DrawHdc;
	}

	//외부에서 오는 것을 실행시켜주기만 하면 됨
	//다른 클래스 or 컨텐츠와의 관련을 맺지 않음
	//Callback방식
	static int WindowLoop(void(*Start)(), void(*Loop)(), void(*End)());


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
	static float4 WindowSize;
	static float4 ScreenSize;
	static float4 WindowPos;

	static HWND HWnd;
	static HDC DrawHdc;			// 윈도우에 그림을 그릴수 있는 권한
};

