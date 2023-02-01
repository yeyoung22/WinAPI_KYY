#pragma once
#include <string>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>


// ���� :������� ���õ� ���
class GameEngineImage;
class GameEngineWindow
{
	static LRESULT CALLBACK MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

public:
	// �����츦 ����� �ִ� ���
	static void WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos);

	//������ ũ��
	static void SettingWindowSize(float4 _Size);
	//������ ��ġ
	static void SettingWindowPos(float4 _Pos);

	static float4 GetScreenSize()
	{
		return ScreenSize;
	}

	//Window Handle���� ��ȯ�ϴ� �Լ�
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

	//�ܺο��� ���� ���� ��������ֱ⸸ �ϸ� ��
	//�ٸ� Ŭ���� or ���������� ������ ���� ����
	//Callback���
	//void(*Start)(), void(*Loop)(), void(*End)() �ܺο��� �Լ������͸� �ñ�� ���
	//=> �������� ����� �и��ϱ� ���ؼ�
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
	static HDC WindowBackBufferHdc;								//�����쿡 �׸��� �׸��� �ִ� ����
	static GameEngineImage* BackBufferImage;					//������ ������ ������ ���(�� ȭ��)
	static GameEngineImage* DoubleBufferImage;					//DoubleBuffer�� �̹��� ���� �� �׸��� BackBuffer������ DuobleBuffer�ɷ� �� �� �׷����� ��
	static bool IsWindowUpdate;
};

