#pragma once
#include <string>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>


// ���� :������� ���õ� ���
class GameEngineWindow
{
public:
	// �����츦 ����� �ִ� ���
	static void WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos);

	static void SettingWindowSize(float4 _Size);
	static void SettingWindowPos(float4 _Pos);

	//Window Handle���� ��ȯ�ϴ� �Լ�
	static HWND GetHWnd()
	{
		return HWnd;
	}

	//�׸��� ������ ��ȯ�ϴ� �Լ�
	static HDC GetDrawHdc()
	{
		return DrawHdc;
	}

	//�ܺο��� ���� ���� ��������ֱ⸸ �ϸ� ��
	//�ٸ� Ŭ���� or ���������� ������ ���� ����
	//Callback���
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
	static HDC DrawHdc;			// �����쿡 �׸��� �׸��� �ִ� ����
};

