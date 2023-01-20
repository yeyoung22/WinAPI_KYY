#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "GameEngineLevel.h"
#include "GameEngineResources.h"

GameEngineCore* Core;

GameEngineCore* GameEngineCore::GetInst()
{
	return Core;
}

void GameEngineCore::GlobalStart()
{
	Core->Start();

	GameEngineTime::GlobalTime.Reset();
}

void GameEngineCore::GlobalUpdate()
{
	if (nullptr != Core->NextLevel)
	{
		GameEngineLevel* PrevLevel = Core->MainLevel;
		GameEngineLevel* NextLevel = Core->NextLevel;

		if (nullptr != PrevLevel)
		{
			PrevLevel->LevelChangeEnd(NextLevel);
		}

		Core->MainLevel = NextLevel;
		Core->NextLevel = nullptr;

		if (nullptr != NextLevel)
		{
			NextLevel->LevelChangeStart(PrevLevel);
		}
	}

	//프레임 시작할때 한번 델타타임 정함
	float TimeDeltaTime = GameEngineTime::GlobalTime.TimeCheck();
	GameEngineInput::Update(TimeDeltaTime);

	Core->Update();

	if (nullptr == Core->MainLevel)
	{
		MsgAssert("레벨을 지정해주지 않은 상태로 코어를 실행했습니다");
		return;
	}

	Core->MainLevel->Update(TimeDeltaTime);
	Core->MainLevel->ActorsUpdate(TimeDeltaTime);
	GameEngineWindow::DoubleBufferClear();
	Core->MainLevel->ActorsRender(TimeDeltaTime);
	GameEngineWindow::DoubleBufferRender();
}

void GameEngineCore::GlobalEnd()
{
	Core->End();

	GameEngineResources::GetInst().Release();
}


GameEngineCore::GameEngineCore() 
{
	GameEngineDebug::LeakCheck();


	//자식 중에 하나일 수 밖에 없음(자신은 절대 안 만들어짐)
	Core = this;
}

GameEngineCore::~GameEngineCore() 
{
	std::map<std::string, GameEngineLevel*>::iterator StartIter = Levels.begin();
	std::map<std::string, GameEngineLevel*>::iterator EndIter = Levels.end();

	for (size_t i = 0; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
		}
	}

	//map의 element 모두 삭제
	Levels.clear();
}

void GameEngineCore::CoreStart(HINSTANCE _instance)
{
	GameEngineWindow::WindowCreate(_instance, "MainWindow", { 1024.0f, (1024.0f / 16.0f) * 15.0f }, { 0, 0 });
	GameEngineWindow::WindowLoop(GameEngineCore::GlobalStart, GameEngineCore::GlobalUpdate, GameEngineCore::GlobalEnd);
}

void GameEngineCore::ChangeLevel(const std::string_view& _Name)
{
	std::map<std::string, GameEngineLevel*>::iterator FindIter = Levels.find(_Name.data());

	//찾고자 하는 레벨이 없는 경우
	if (FindIter == Levels.end())
	{
		std::string Name = _Name.data();
		MsgAssert(Name + "존재하지 않는 레벨을 실행시키려고 했습니다");
		return;
	}

	//일치하는 레벨이 있으면 MainLevel 교체
	MainLevel = FindIter->second;
}

void GameEngineCore::LevelLoading(GameEngineLevel* _Level)
{
	if (nullptr == _Level)
	{
		MsgAssert("nullptr 인 레벨을 로딩하려고 했습니다.");
		return;
	}

	_Level->Loading();
}