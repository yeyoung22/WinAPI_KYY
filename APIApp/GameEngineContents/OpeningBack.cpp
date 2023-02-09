#include "OpeningBack.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

OpeningBack::OpeningBack() 
{
}

OpeningBack::~OpeningBack() 
{
}

void OpeningBack::Start()
{

	{
		float4 Size = GameEngineWindow::GetScreenSize();
		GameEngineRender* Render = CreateRender("Opening.bmp", MarioRenderOrder::BackGround);
		Render->SetPosition(GameEngineWindow::GetScreenSize().half());
		Render->SetScale(GameEngineWindow::GetScreenSize());
	}

}