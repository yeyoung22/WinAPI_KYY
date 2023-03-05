#include "EndingLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "EndingBack.h"
#include "ContentsUI.h"



EndingLevel::EndingLevel() 
{
}

EndingLevel::~EndingLevel() 
{
}

void EndingLevel::SoundLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	Dir.Move("BGM");

	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("SavedthePrincess.mp3"));
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("GameOver.mp3"));
	}
}

void EndingLevel::ImageLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Screen");

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Ending2.bmp"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GameOver.bmp"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TimeUp.bmp"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("txt1.bmp"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("txt2.bmp"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("txt3.bmp"));
	}
	

	CreateActor<EndingBack>();

	{
		ContentsUI* Actor = CreateActor<ContentsUI>(MarioRenderOrder::UI);
		float4 StartPos = GameEngineWindow::GetScreenSize().half();
		Actor->SetPos({ StartPos.x + 420, StartPos.y - 400 });
	}
}

void EndingLevel::Loading()
{

	SoundLoad();
	ImageLoad();

}

void EndingLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("Select"))
	{
		GameEngineCore::GetInst()->ChangeLevel("TitleLevel");
	}
}

void EndingLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (EndingScene::Clear == EndingBack::Ending->GetEndingScene())
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("SavedthePrincess.mp3");
	}
	else
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("GameOver.mp3");
	}

	BGMPlayer.LoopCount(1);
	BGMPlayer.Volume(BGMVolume);
}

void EndingLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}