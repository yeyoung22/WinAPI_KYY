#include "TitleBack.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "ContentsEnums.h"



TitleBack::TitleBack() 
{
}

TitleBack::~TitleBack() 
{
}

void TitleBack::Start()
{
	float4 Size = GameEngineWindow::GetScreenSize();


	GameEngineRender* Render = CreateRender("TitleScreen.bmp", MarioRenderOrder::BackGround);
	Render->SetPosition(GameEngineWindow::GetScreenSize().half());
	Render->SetScale(GameEngineWindow::GetScreenSize());
}