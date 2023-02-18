#pragma once
#include <Windows.h>
#include <map>
#include <string_view>
#include <GameEngineBase/GameEngineDebug.h>

// 설명 : 게임을 구성하기 위한 기본 구조들
//엔진에서 응당 로드해야 할 필수적 리소스
//Core는 여러개 생성되지 않음

class GameEngineLevel;
class GameEngineCore									//추상클래스
{
private:
	static void GlobalStart();
	static void GlobalUpdate();
	static void GlobalEnd();

public:
	// constrcuter destructer
	GameEngineCore();
	~GameEngineCore();

	// delete Function
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

	void CoreStart(HINSTANCE _instance);				//HINSTANCE: exe파일을 메모리에 로드할 때 OS가 사용하는 값

	void ChangeLevel(const std::string_view& _Name);

	static GameEngineCore* GetInst();

	void DebugSwitch()
	{
		IsDebugValue = !IsDebugValue;
	}

	void SetDebugMode(bool _IsDebug)
	{
		IsDebugValue = _IsDebug;
	}

	bool IsDebug()
	{
		return IsDebugValue;
	}

protected:
	template<typename LevelType>
	void CreateLevel(const std::string_view& _Name)
	{
		//어떤 장면을 만들었는데, 또 중복된 이름으로 만들려는 상황
		if (Levels.end() != Levels.find(_Name.data()))
		{
			std::string Name = _Name.data();
			MsgAssert(Name + "이미 존재하는 이름의 레벨을 만들려고 했습니다");
			return;
		}

		GameEngineLevel* Level = new LevelType();		//UpCasting
		LevelLoading(Level, _Name);
		//insert()할 때마다 새로운 string이 생기면서
		//자신만의 메모리를 가지게 됨
		Levels.insert(std::make_pair(_Name.data(), Level));
	}

	virtual void Start() = 0;							//순수가상함수
	virtual void Update() = 0;
	virtual void End() = 0;

private:
	//GameEngineLevel을 "어떤 이름"으로 찾고 
	//이름으로 실행하기 위해 map 사용
	std::map<std::string, GameEngineLevel*> Levels;

	GameEngineLevel* NextLevel = nullptr;

	GameEngineLevel* MainLevel = nullptr;

	void LevelLoading(GameEngineLevel* _Level, const std::string_view& _Name);

	bool IsDebugValue = false;

};

