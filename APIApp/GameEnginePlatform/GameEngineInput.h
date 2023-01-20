#pragma once
#include <Windows.h>
#include <map>
#include <string>

// 설명 : 키 입력과 관련한 기능
class GameEngineWindow;
class GameEngineInput
{
	friend GameEngineWindow;

public:
	class GameEngineKey
	{
		friend GameEngineInput;

		bool Down = false;		//키를 누른 순간
		bool Press = false;		//지속적으로 키 누름
		bool Up = false;		//키를 안 누르기 시작한 순간
		bool Free = true;		//키를 안 누름

		float PressTime;		//키를 누른 시간
		int Key = -1;

		bool KeyCheck()
		{
			//키 작동 여부
			return 0 != GetAsyncKeyState(Key);
		}

		void Update(float _DeltaTime);
	};
public:

	// delete Function
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;

	static void Update(float _DeltaTime);

	static void CreateKey(const std::string_view& _Name, int _Key);

	static bool IsKey(const std::string_view& _Name);

	static bool IsDown(const std::string_view& _Name);
	static bool IsUp(const std::string_view& _Name);
	static bool IsPress(const std::string_view& _Name);
	static bool IsFree(const std::string_view& _Name);
	static float GetPressTime(const std::string_view& _Name);

	//어떤 키라도 눌러졌는지
	static bool IsAnyKey()
	{
		return IsAnyKeyValue;
	}

protected:

private:
	// constrcuter destructer
	GameEngineInput();
	~GameEngineInput();

	static std::map<std::string, GameEngineKey> Keys;
	static bool IsAnyKeyValue;

	static void IsAnyKeyOn()
	{
		IsAnyKeyValue = true;
	}

	static void IsAnyKeyOff()
	{
		IsAnyKeyValue = false;
	}
};

