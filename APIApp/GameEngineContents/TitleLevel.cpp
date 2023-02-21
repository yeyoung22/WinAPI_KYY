#include "TitleLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>
#include "TitleBack.h"
#include "ContentsValue.h"
#include "ContentsUI.h"
#include "ContentsEnums.h"


TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Title");

	//이미지 로드
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TitleScreen.bmp"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CursurIcon.bmp"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ScoreCoin.bmp"));
	}
	//TextUI
	{
		Dir.Move("Text");

		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Number.bmp"));
		Image->Cut(10, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Alphabet.bmp"));
		Image->Cut(13, 2);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SpecialSymbol.bmp"));
		Image->Cut(7, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CoinUI.bmp"));
		Image->Cut(4, 1);
	}



	if (false == GameEngineInput::IsKey("LevelChange"))
	{
		GameEngineInput::CreateKey("LevelChange", 'P');
	}


	TitleBack* Actor =  CreateActor<TitleBack>();

	{
		ContentsUI* Actor = CreateActor<ContentsUI>(MarioRenderOrder::UI);
		float4 StartPos = GameEngineWindow::GetScreenSize().half();
		Actor->SetPos({ StartPos.x + 420, StartPos.y - 400 });
	}

}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("LevelChange"))
	{
		GameEngineCore::GetInst()->ChangeLevel("OpeningLevel");
	}

	if (true == GameEngineInput::IsDown("Select") && false == TitleBack::IsMultiMode)
	{
		GameEngineCore::GetInst()->ChangeLevel("OpeningLevel");
	}
}

void TitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	ContentsValue::CameraScale = { 1020, 960 };
}