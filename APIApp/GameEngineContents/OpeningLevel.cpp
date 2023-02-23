#include "OpeningLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>
#include "OpeningBack.h"
#include "PlayLevel.h"
#include "ContentsUI.h"
#include "ContentsEnums.h"

OpeningLevel::OpeningLevel() 
{
}

OpeningLevel::~OpeningLevel() 
{
}

void OpeningLevel::Loading()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Screen");

	//이미지 로드
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Opening.bmp"));
		Dir.MoveParent();

	}

	CreateActor<OpeningBack>();

	{
		ContentsUI* Actor = CreateActor<ContentsUI>(MarioRenderOrder::UI);
		float4 StartPos = GameEngineWindow::GetScreenSize().half();
		Actor->SetPos({ StartPos.x + 420, StartPos.y - 400 });
	}
}

void OpeningLevel::Update(float _DeltaTime)
{
	WaitTime -= _DeltaTime;

	if ((true == GameEngineInput::IsDown("Select")) || WaitTime <= 0)
	{
		GameEngineCore::GetInst()->ChangeLevel("PlayLevel");
	}
}