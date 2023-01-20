#include "SuperMarioCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "TitleLevel.h"
#include "OpeningLevel.h"
#include "PlayLevel.h"

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
	//정수의 연산 결과값: 무조건 정수
	//실수를 원한다면 실수를 넣어야 함

	//The pixel aspect ratio of both consoles is 16:15
	GameEngineWindow::SettingWindowSize({1024.0f, (1024.0f / 16.0f) * 15.0f });

	new int();

	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<OpeningLevel>("OpeningLevel");
	CreateLevel<PlayLevel>("PlayLevel");

	//우선 눈에 보이는게 좋으므로 Start지만 title이 아닌 play 사용
	ChangeLevel("TitleLevel");
}

void SuperMarioCore::Update()
{

}
void SuperMarioCore::End()
{

}