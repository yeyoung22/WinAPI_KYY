#include "OpeningLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "OpeningBack.h"

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
	}

	if (false == GameEngineInput::IsKey("LevelChange"))
	{
		GameEngineInput::CreateKey("LevelChange", 'P');
	}

	CreateActor<OpeningBack>();
}

void OpeningLevel::Update(float _DeltaTime)
{
	//if (true == GameEngineInput::IsDown("LevelChange"))
	//{
	//	GameEngineCore::GetInst()->ChangeLevel("PlayLevel");
	//}

	WaitTime -= _DeltaTime;

	if (WaitTime <= 0)
	{
		GameEngineCore::GetInst()->ChangeLevel("PlayLevel");
	}

	
}