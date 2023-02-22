#include "TitleBack.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "ContentsEnums.h"
#include "ContentsUI.h"

bool TitleBack::IsMultiMode = false;

TitleBack::TitleBack() 
{
}

TitleBack::~TitleBack() 
{
}

void TitleBack::Start()
{
	if (false == GameEngineInput::IsKey("DownMove"))
	{
		GameEngineInput::CreateKey("Select", VK_SPACE);
		GameEngineInput::CreateKey("DownMove", 'S');
		GameEngineInput::CreateKey("UpMove", 'W');
	}

	{	float4 Size = GameEngineWindow::GetScreenSize();
	GameEngineRender* Render = CreateRender("TitleScreen.bmp", MarioRenderOrder::BackGround);
	Render->SetPosition(Size.half());
	Render->SetScale(GameEngineWindow::GetScreenSize());
	}

	IconRender = CreateRender("CursurIcon.bmp", MarioRenderOrder::UI);
	IconRender->SetPosition({ 302, 590 });
	IconRender->SetScale(IconRender->GetImage()->GetImageScale());


	{
		GameEngineRender* Render = CreateRender("ScoreCoin.bmp", MarioRenderOrder::UI);
		Render->SetPosition({ 362, 108 });
		Render->SetScale(Render->GetImage()->GetImageScale());
	}
}

void TitleBack::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("Select") && false == TitleBack::IsMultiMode)
	{
		return;
	}

	if (true == GameEngineInput::IsDown("DownMove"))
	{
		IconRender->SetPosition({ 302, 655 });

		IsMultiMode = true;
	}
	else if(true == GameEngineInput::IsDown("UpMove"))
	{
		IconRender->SetPosition({ 302, 590 });

		IsMultiMode = false;
	}
}
