#include "SuperMarioCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "TitleLevel.h"
#include "OpeningLevel.h"
#include "PlayLevel.h"
#include "OptionLevel.h"

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

	//The pixel aspect ratio of both consoles is 8:7
	GameEngineWindow::SettingWindowSize({ 1200.0f, (1200.0f / 800.0f) * 700.0f });

	new int();

	CreateLevel<TitleLevel>("Title");
	CreateLevel<OpeningLevel>("Opening");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<OptionLevel>("Option");

	//static_assert
	//CreateLevel<Player>("Title1");

	//�켱 ���� ���̴°� �����Ƿ� Start���� title�� �ƴ� play ���
	ChangeLevel("Play");
}

void SuperMarioCore::Update()
{

}
void SuperMarioCore::End()
{

}