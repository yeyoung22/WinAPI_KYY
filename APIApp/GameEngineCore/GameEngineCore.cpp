#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineLevel.h"

GameEngineCore* Core;

void GameEngineCore::GlobalStart()
{
	Core->Start();
}

void GameEngineCore::GlobalUpdate()
{
	Core->Update();

	if (nullptr == Core->MainLevel)
	{
		MsgAssert("레벨을 지정해주지 않은 상태로 코어를 실행했습니다");
		return;
	}


}

void GameEngineCore::GlobalEnd()
{
	Core->End();
}


GameEngineCore::GameEngineCore() 
{
	GameEngineDebug::LeakCheck();


	//자식 중에 하나일 수 밖에 없음
	//자신은 절대 만들어질 수 없기때문
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
	//The pixel aspect ratio of both consoles is 8:7
	GameEngineWindow::WindowCreate(_instance, "MainWindow", { 720, 630 }, { 0, 0 });
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

	//_Level->Loading();
}