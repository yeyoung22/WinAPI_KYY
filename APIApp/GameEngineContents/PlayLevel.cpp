#include "PlayLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "Player.h"
#include "Map.h"
#include "Monster.h"
#include "Item.h"
#include "ContentsUI.h"
#include "ContentsEnums.h"
#include "ContentsValue.h"


float4 PlayLevel::MapScale = float4::Zero;

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::SoundLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	Dir.Move("BGM");

	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("RunningAbout.mp3"));
	}


}

void PlayLevel::ImageLoad()
{
	//상대 경로
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");

	//이미지 로드
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_Mario.bmp"));
		Image->Cut(4, 9);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_Mario.bmp"));
		Image->Cut(4, 9);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("World1_1.bmp"));
		GameEngineImage* ColImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ColWorld1_1.bmp"));
		MapScale = ColImage->GetImageScale();
	}
	{

		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("World1_4.bmp"));
		//GameEngineImage* ColImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ColWorld1_4.bmp"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Goomba.bmp"));
		Image->Cut(3, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Item\\Left_SuperMushroom.bmp"));
		Image->Cut(4, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Item\\Right_SuperMushroom.bmp"));
		Image->Cut(4, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Number.bmp"));
		Image->Cut(10, 1);
	}
}

//Loading 시점: 만들어야할 것들을 만드는 시점
void PlayLevel::Loading()
{
	SoundLoad();
	ImageLoad();
	SetCameraScale({ 1020, 960 });

	//액터 생성
	{
		Map* Actor = CreateActor<Map>();
	}
	{
		Player* Actor = CreateActor<Player>();
		Actor->SetPos({ 160, GameEngineWindow::GetScreenSize().y - 128});					// x = 128+mario.half
	}
	{
		Monster* Actor = CreateActor<Monster>(MarioRenderOrder::Monster);
		float4 StartPos = GameEngineWindow::GetScreenSize();
		Actor->SetPos({ StartPos.x * 2- StartPos.half().x , StartPos.y - 128});
	}
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		//아이템 위치 수정해야 함
		float4 StartPos = GameEngineWindow::GetScreenSize();
		Actor->SetPos({ StartPos.hx(), StartPos.y - 128});
	}
	{
		ContentsUI* Actor = CreateActor<ContentsUI>(MarioRenderOrder::UI);
		float4 StartPos = GameEngineWindow::GetScreenSize();
		Actor->SetPos({ StartPos.x - 256, StartPos.y - 64 });
	}

	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		GameEngineInput::CreateKey("DebugRenderSwitch", 'R');
	}


	if (false == GameEngineInput::IsKey("CameraLeftMove"))
	{
		//VK: 알파뱃과 숫자를 제외한 키
		GameEngineInput::CreateKey("CameraLeftMove", VK_LEFT);			//방향키
		GameEngineInput::CreateKey("CameraRightMove", VK_RIGHT);
		GameEngineInput::CreateKey("CameraDownMove", VK_DOWN);
		GameEngineInput::CreateKey("CameraUpMove", VK_UP);
	}
}

void PlayLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("DebugRenderSwitch"))
	{
		if (false == BGMPlayer.GetPause())
		{
			BGMPlayer.PauseOn();
		}
		else
		{
			BGMPlayer.PauseOff();
		}


		DebugRenderSwitch();
	}

}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("RunningAbout.mp3");
	BGMPlayer.LoopCount(1);

	ContentsValue::CameraScale = { 1020, 960 };
}