#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineLevel::GameEngineLevel() 
{
}

GameEngineLevel::~GameEngineLevel()
{
	for (GameEngineActor* Actor : Actors)					//Range For
	{
		// Actors.erase()
		if (nullptr != Actor)
		{
			delete Actor;
			Actor = nullptr;
		}
	}

	Actors.clear();
}

void GameEngineLevel::ActorStart(GameEngineActor* _Actor)
{
	if (nullptr == _Actor)
	{
		MsgAssert("nullptr 액터를 Start하려고 했습니다.");
		return;
	}

	_Actor->Start();
}

void GameEngineLevel::ActorsUpdate()
{
	std::list<GameEngineActor*>::iterator StartIter = Actors.begin();
	std::list<GameEngineActor*>::iterator EndIter = Actors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter)->Update();
	}
}

void GameEngineLevel::ActorsRender()
{
	std::list<GameEngineActor*>::iterator StartIter = Actors.begin();
	std::list<GameEngineActor*>::iterator EndIter = Actors.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter)->Render();
	}
}