#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineLevel.h"
#include "GameEngineResources.h"

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
		MsgAssert("������ ���������� ���� ���·� �ھ �����߽��ϴ�");
		return;
	}

	Core->MainLevel->ActorsUpdate();
	GameEngineWindow::DoubleBufferClear();
	Core->MainLevel->ActorsRender();
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


	//�ڽ� �߿� �ϳ��� �� �ۿ� ����
	//�ڽ��� ���� ������� �� ���⶧��
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

	//map�� element ��� ����
	Levels.clear();
}

void GameEngineCore::CoreStart(HINSTANCE _instance)
{
	GameEngineWindow::WindowCreate(_instance, "MainWindow", { 720, 630 }, { 0, 0 });
	GameEngineWindow::WindowLoop(GameEngineCore::GlobalStart, GameEngineCore::GlobalUpdate, GameEngineCore::GlobalEnd);
}

void GameEngineCore::ChangeLevel(const std::string_view& _Name)
{
	std::map<std::string, GameEngineLevel*>::iterator FindIter = Levels.find(_Name.data());

	//ã���� �ϴ� ������ ���� ���
	if (FindIter == Levels.end())
	{
		std::string Name = _Name.data();
		MsgAssert(Name + "�������� �ʴ� ������ �����Ű���� �߽��ϴ�");
		return;
	}

	//��ġ�ϴ� ������ ������ MainLevel ��ü
	MainLevel = FindIter->second;
}

void GameEngineCore::LevelLoading(GameEngineLevel* _Level)
{
	if (nullptr == _Level)
	{
		MsgAssert("nullptr �� ������ �ε��Ϸ��� �߽��ϴ�.");
		return;
	}

	_Level->Loading();
}