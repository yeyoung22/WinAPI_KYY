#pragma once
#include <string>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>


// 설명 :윈도우와 관련된 기능
class GameEngineImage;
class GameEngineWindow
{
	static LRESULT CALLBACK MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

public:
	// 윈도우를 만들어 주는 기능
	static void WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos);

	//윈도우 크기
	static void SettingWindowSize(float4 _Size);
	//윈도우 위치
	static void SettingWindowPos(float4 _Pos);

	static float4 GetScreenSize()
	{
		return ScreenSize;
	}

	//Window Handle값을 반환하는 함수
	static HWND GetHWnd()
	{
		return HWnd;
	}

	static HDC GetWindowBackBufferHdc()
	{
		return WindowBackBufferHdc;
	}

	static GameEngineImage* GetDoubleBufferImage()
	{
		return DoubleBufferImage;
	}

	static void AppOff()
	{
		IsWindowUpdate = false;
	}

	static void DoubleBufferClear();

	static void DoubleBufferRender();

	//외부에서 오는 것을 실행시켜주기만 하면 됨
	//다른 클래스 or 컨텐츠와의 관련을 맺지 않음
	//Callback방식
	//void(*Start)(), void(*Loop)(), void(*End)() 외부에서 함수포인터를 맡기는 방식
	//=> 컨텐츠와 기능을 분리하기 위해서
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
	static HDC WindowBackBufferHdc;								//윈도우에 그림을 그릴수 있는 권한
	static GameEngineImage* BackBufferImage;					//윈도우 생성시 나오는 배경(흰 화면)
	static GameEngineImage* DoubleBufferImage;					//DoubleBuffer에 이미지 여러 번 그리고 BackBuffer에서는 DuobleBuffer걸로 한 번 그려지게 함
	static bool IsWindowUpdate;
};

