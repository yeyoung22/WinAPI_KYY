#pragma once
#include <Windows.h>
#include <map>
#include <string>

// ���� : Ű �Է°� ������ ���
class GameEngineWindow;
class GameEngineInput
{
	friend GameEngineWindow;

private:						//Inner Class�鼭 ���ο����� ���
	class GameEngineKey			//�ۿ��� ����� ���� ����(����, ���� ���)
	{
		friend GameEngineInput;

		bool Down = false;		//Ű�� ���� ����
		bool Press = false;		//���������� Ű ����
		bool Up = false;		//Ű�� �� ������ ������ ����
		bool Free = true;		//Ű�� �� ����

		float PressTime;		//Ű�� ���� �ð�
		int Key = -1;

		bool KeyCheck()
		{
			//Ű �۵� ����
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

	//static�̹Ƿ� �ش� Ŭ���� �̸����� ���ϰ� ��밡��
	//��ü�� ���� ������ �ʿ䰡 ����

	static void Update(float _DeltaTime);

	static void CreateKey(const std::string_view& _Name, int _Key);

	static bool IsKey(const std::string_view& _Name);

	static bool IsDown(const std::string_view& _Name);
	static bool IsUp(const std::string_view& _Name);
	static bool IsPress(const std::string_view& _Name);
	static bool IsFree(const std::string_view& _Name);
	static float GetPressTime(const std::string_view& _Name);

	//� Ű�� ���������� üũ
	static bool IsAnyKey()
	{
		return IsAnyKeyValue;
	}

protected:

private:
	// constrcuter destructer
	GameEngineInput();
	~GameEngineInput();

	static std::map<std::string, GameEngineKey> Keys;		//GameEngineKey�� ���� ���� �����ϱ� ���� ������
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

