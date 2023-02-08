#include "EndingBack.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

EndingBack::EndingBack() 
{
}

EndingBack::~EndingBack() 
{
}

void EndingBack::Start()
{
	float4 Size = GameEngineWindow::GetScreenSize();

	GameEngineRender* Render = CreateRender("Ending1.bmp", MarioRenderOrder::BackGround);
	Render->SetPosition(GameEngineWindow::GetScreenSize().half());
	Render->SetScale(GameEngineWindow::GetScreenSize());
	
	//float4 Size = GameEngineWindow::GetScreenSize();

	//GameEngineRender* Render = CreateRender("Ending2.bmp", MarioRenderOrder::BackGround);
	//Render->SetPosition(GameEngineWindow::GetScreenSize().half());
	//Render->SetScale(GameEngineWindow::GetScreenSize());

}

