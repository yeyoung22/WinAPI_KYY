#include "PlayLevel.h"
#include <vector>
#include <string>
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
#include "QuestionBlock.h"
#include "Pipe.h"
#include "EndingBack.h"



std::vector<std::vector<int>> PlayLevel::MapNames;
PlayLevel* PlayLevel::MainPlayLevel;

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
	MapNames.clear();
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
	}
	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("RunningAbout_Hurry.mp3"));
	}
	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Underground.mp3"));
	}
	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Underground_Hurry.mp3"));
	}
	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Miss.mp3"));

		Dir.MoveParent();
	}
	//Sound Effect Load
	{
		Dir.Move("SoundEffect");
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("jump.wav"));
	}
	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("jump_superMario.wav"));
	}
	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("pipe.wav"));
	}
	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("bump.wav"));
	}
	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("coin.wav"));
	}
	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("stomp.wav"));
	}
	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("growup.wav"));

		Dir.MoveParent();
	}


}

void PlayLevel::ImageLoad()
{
	//��� ���
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");

	//�̹��� �ε�
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

		std::vector<int> SubMapNames;
		SubMapNames.push_back(1);
		SubMapNames.push_back(1);
		MapNames.push_back(SubMapNames);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("World1_4.bmp"));
		GameEngineImage* ColImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ColWorld1_4.bmp"));

		std::vector<int> SubMapNames;
		SubMapNames.push_back(1);
		SubMapNames.push_back(4);
		MapNames.push_back(SubMapNames);

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
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_1UPMushroom.bmp"));
		Image->Cut(4, 1);
	} 
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_1UPMushroom.bmp"));
		Image->Cut(4, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Coin.bmp"));
		Image->Cut(4, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FireFlower.bmp"));
		Image->Cut(4, 1);

		Dir.MoveParent();
	}
	//Block
	{
		Dir.Move("Block");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("QuestionBlock.bmp"));
		Image->Cut(4, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UsedBlock.bmp"));
		Image->Cut(1, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Brick.bmp"));
		Image->Cut(1, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Smithereens.bmp"));
		Image->Cut(2, 1);

		Dir.MoveParent();
	}
	{
		Dir.Move("Pipe");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Pipe.bmp"));
		Image->Cut(2, 1);
	}
}

//Loading ����: �������� �͵��� ����� ����
void PlayLevel::Loading()
{
	SoundLoad();
	ImageLoad();

	//���� ����
	{
		Map* Actor = CreateActor<Map>();
	}
	//MainPlayer
	{
		Player* Actor = CreateActor<Player>();
		Actor->SetPos({ 160, GameEngineWindow::GetScreenSize().y - 128});					// x = 128+mario.half

		//Actor->SetPos({ 1000, GameEngineWindow::GetScreenSize().y - 128 });
	}
	//Goomba1
	{
		Monster* Actor = CreateActor<Monster>(MarioRenderOrder::Monster);
		float4 StartPos = GameEngineWindow::GetScreenSize();
		Actor->SetPos({1400, StartPos.y - 128});

		//�ϴ� ���� ��=-------------------------------------------------------------------------------------------
		//Actor->Off();
	}
	//1_1_GrowMushroom
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		float4 StartPos = GameEngineWindow::GetScreenSize();
		Actor->SetPos({ 1376, StartPos.y - 128});


		//�ϴ� ���� ��=------------------------------------------------------------------------------------------
		Actor->Off();
	}
	//1_1_2ndItem
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		float4 StartPos = GameEngineWindow::GetScreenSize();
		Actor->SetPos({ 5024, StartPos.y - 128 });

		Actor->SetItemMode(ItemType::LIFEMUSHROOM);
	}
	//UI
	{
		ContentsUI* Actor = CreateActor<ContentsUI>(MarioRenderOrder::UI);
		float4 StartPos = GameEngineWindow::GetScreenSize().half();
		Actor->SetPos({ StartPos.x + 420, StartPos.y-400 });
	}
	{
		ContentsUI* Actor = CreateActor<ContentsUI>(MarioRenderOrder::UI);
		float4 StartPos = GameEngineWindow::GetScreenSize().half();
		Actor->SetPos({ StartPos.x + 420, StartPos.y - 400 });
	}

	//1_1_QBlock1
	{
		QuestionBlock* Actor = CreateActor<QuestionBlock>(MarioRenderOrder::Block);
		Actor->SetPos({1060, 640});
	}
	//1_1_QBlock2
	{
		QuestionBlock* Actor = CreateActor<QuestionBlock>(MarioRenderOrder::Block);
		Actor->SetPos({ 1376, 640 });									//block �ٷ� �� 64 ����
	}
	//1_1_QBlock3
	{
		QuestionBlock* Actor = CreateActor<QuestionBlock>(MarioRenderOrder::Block);
		Actor->SetPos({ 1504, 640 });
	}
	//1_1_QBlock4
	{
		QuestionBlock* Actor = CreateActor<QuestionBlock>(MarioRenderOrder::Block);
		Actor->SetPos({1440, 384 });
	}
	//1_1_QBlock5
	{
		QuestionBlock* Actor = CreateActor<QuestionBlock>(MarioRenderOrder::Block);
		Actor->SetPos({ 5024, 640 });
	}
	//1_1_QBlock6
	{
		QuestionBlock* Actor = CreateActor<QuestionBlock>(MarioRenderOrder::Block);
		Actor->SetPos({ 6047, 384 });
	}
	//1_1_QBlock7
	{
		QuestionBlock* Actor = CreateActor<QuestionBlock>(MarioRenderOrder::Block);
		Actor->SetPos({ 6815, 640 });
	}
	//1_1_QBlock8
	{
		QuestionBlock* Actor = CreateActor<QuestionBlock>(MarioRenderOrder::Block);
		Actor->SetPos({ 7007, 640 });
	}
	//1_1_QBlock9
	{
		QuestionBlock* Actor = CreateActor<QuestionBlock>(MarioRenderOrder::Block);
		Actor->SetPos({ 7199, 640 });
	}
	//1_1_QBlock10
	{
		QuestionBlock* Actor = CreateActor<QuestionBlock>(MarioRenderOrder::Block);
		Actor->SetPos({ 7007, 384 });
	}
	//1_1_QBlock11
	{
		QuestionBlock* Actor = CreateActor<QuestionBlock>(MarioRenderOrder::Block);
		Actor->SetPos({ 8289, 384 });
	}	
	//1_1_QBlock12
	{
		QuestionBlock* Actor = CreateActor<QuestionBlock>(MarioRenderOrder::Block);
		Actor->SetPos({ 8353, 384 });
	}
	//1_1_QBlock9
	{
		QuestionBlock* Actor = CreateActor<QuestionBlock>(MarioRenderOrder::Block);
		Actor->SetPos({ 10913, 640 });
	}

	//Pipe1
	{
		Pipe* Actor = CreateActor<Pipe>(MarioRenderOrder::Pipe);
		Actor->SetPos({ 3712, 710 });			
	}
	//Pipe2
	{
		Pipe* Actor = CreateActor<Pipe>(MarioRenderOrder::Pipe);
		Actor->SetPos({ 7022, 1790 });
		Actor->SetPipeMode(PipeType::LEFT);
	}
	//Pipe3
	{
		Pipe* Actor = CreateActor<Pipe>(MarioRenderOrder::Pipe);
		Actor->SetPos({ 7712, 710 });
	}

	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		//VK: ���Ĺ�� ���ڸ� ������ Ű
		GameEngineInput::CreateKey("CameraLeftMove", VK_LEFT);			//����Ű
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

	if (GameEngineInput::IsDown("StageClear"))
	{
		//ó������ �ٽ� ���
	}

	

	if (0 >= Player::PlayTimer)
	{
		EndingBack::Ending->SetEndingScene(EndingScene::TimeOver);
	}
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPlayLevel = this;

	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("RunningAbout.mp3");
	BGMPlayer.LoopCount(MaxLoop);
	BGMPlayer.Volume(BGMVolume);

}

void PlayLevel::SetBGMPlayer(const std::string_view& _String, int _loop, float _BasicVolume)
{
	BGMPlayer.Stop();
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl(_String.data());
	BGMPlayer.LoopCount(_loop);
	BGMPlayer.Volume(_BasicVolume);
}