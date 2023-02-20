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
	//BGM Load
	{
		Dir.Move("BGM");
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("RunningAbout.mp3"));

		Dir.MoveParent();
	}
	//Sound Effect Load
	{
		Dir.Move("SoundEffect");
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("jump.wav"));

		Dir.MoveParent();
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
	//Player
	{
		//test image(transparent)------------------------------------------------------------------------------
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Transparent.bmp"));
		Image->Cut(1, 1);
	}
	{
		Dir.Move("Player");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_Mario.bmp"));
		Image->Cut(4, 9);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_Mario.bmp"));
		Image->Cut(4, 9);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_FireMario.bmp"));
		Image->Cut(7, 3);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_FireMario.bmp"));
		Image->Cut(7, 3);
	} 
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_Bigger.bmp"));
		Image->Cut(7, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_Bigger.bmp"));
		Image->Cut(7, 1);

		Dir.MoveParent();
	}
	//{
	//	GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_InvincibleMario.bmp"));
	//	Image->Cut(4, 1);
	//}
	//{
	//	GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_InvincibleMario.bmp"));
	//	Image->Cut(4, 1);
	//}
	//{
	//	GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_InvincibleGrowth.bmp"));
	//	Image->Cut(4, 1);
	//}
	//{
	//	GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_InvincibleGrowth.bmp"));
	//	Image->Cut(4, 1);
	//}
	//{
	//	GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_InvincibleFireMario.bmp"));
	//	Image->Cut(4, 1);
	//}
	//{
	//	GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_InvincibleFireMario.bmp"));
	//	Image->Cut(4, 1);

	//	Dir.MoveParent();
	//}

	//Map
	{
		Dir.Move("Map");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("World1_1.bmp"));
		GameEngineImage* ColImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ColWorld1_1.bmp"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("World1_4.bmp"));
		GameEngineImage* ColImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ColWorld1_4.bmp"));

		Dir.MoveParent();
	}

	//Monster
	{
		Dir.Move("Monster");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Goomba.bmp"));
		Image->Cut(3, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ReverseGoomba.bmp"));
		Image->Cut(2, 1);

		Dir.MoveParent();
	}

	//Effect
	{
		Dir.Move("Effect");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_Fire.bmp"));
		Image->Cut(4, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_Fire.bmp"));
		Image->Cut(4, 1);

		Dir.MoveParent();
	}

	//Item
	{
		Dir.Move("Item");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_SuperMushroom.bmp"));
		Image->Cut(4, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_SuperMushroom.bmp"));
		Image->Cut(4, 1);

		Dir.MoveParent();
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

		Dir.MoveParent();
	}

}

//Loading 시점: 만들어야할 것들을 만드는 시점
void PlayLevel::Loading()
{
	SoundLoad();
	ImageLoad();

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
		float4 StartPos = GameEngineWindow::GetScreenSize().half();
		Actor->SetPos({ StartPos.x + 420, StartPos.y-400 });
	}

	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		//VK: 알파뱃과 숫자를 제외한 키
		GameEngineInput::CreateKey("CameraLeftMove", VK_LEFT);			//방향키
		GameEngineInput::CreateKey("CameraRightMove", VK_RIGHT);
		GameEngineInput::CreateKey("CameraDownMove", VK_DOWN);
		GameEngineInput::CreateKey("CameraUpMove", VK_UP);

		GameEngineInput::CreateKey("DebugRenderSwitch", 'R');
		GameEngineInput::CreateKey("BGMPause", 'P');
		GameEngineInput::CreateKey("FreeMoveSwitch", '1');
		GameEngineInput::CreateKey("StageClear", '2');
		GameEngineInput::CreateKey("GoToCastle", '3');
		GameEngineInput::CreateKey("DebuggingMode", '8');		//For Debug
	}

}

void PlayLevel::Update(float _DeltaTime)
{
	/*BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("RunningAbout.mp3");
	BGMPlayer.LoopCount(1);
	BGMPlayer.Volume(0.1f);*/

	if (GameEngineInput::IsDown("BGMPause"))
	{
		if (false == BGMPlayer.GetPause())
		{
			BGMPlayer.PauseOn();
		}
		else
		{
			BGMPlayer.PauseOff();
		}
	}

	if (GameEngineInput::IsDown("DebugRenderSwitch") || GameEngineInput::IsDown("DebuggingMode"))
	{
		DebugRenderSwitch();
	}
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("RunningAbout.mp3");
	BGMPlayer.LoopCount(1);

	ContentsValue::CameraScale = { 1020, 960 };
}