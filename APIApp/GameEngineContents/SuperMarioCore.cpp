#include "SuperMarioCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "TitleLevel.h"
#include "OpeningLevel.h"
#include "PlayLevel.h"
#include "EndingLevel.h"

//SuperMarioCore SuperMarioCore::Core = new SuperMarioCore();

SuperMarioCore SuperMarioCore::Core;

SuperMarioCore::SuperMarioCore() 
{
}

SuperMarioCore::~SuperMarioCore() 
{
}

void SuperMarioCore::Start()
{
	//������ ���� �����: ������ ����
	//�Ǽ��� ���Ѵٸ� �Ǽ��� �־�� ��

	//The pixel aspect ratio of both consoles is 16:15
	GameEngineWindow::SettingWindowSize({1024.0f, (1024.0f / 16.0f) * 15.0f });

	new int();

	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<OpeningLevel>("OpeningLevel");
	CreateLevel<PlayLevel>("PlayLevel");
	CreateLevel<EndingLevel>("EndingLevel");

	ChangeLevel("TitleLevel");
	//ChangeLevel("PlayLevel");					//���߿� ������ ��------------------------------
}

void SuperMarioCore::Update()
{

}
void SuperMarioCore::End()
{

}