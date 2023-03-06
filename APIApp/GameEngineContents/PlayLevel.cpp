#include "PlayLevel.h"
#include <vector>
#include <string>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "Player.h"
#include "Map.h"
#include "Goomba.h"
#include "Item.h"
#include "ContentsUI.h"
#include "ContentsEnums.h"
#include "QuestionBlock.h"
#include "Pipe.h"
#include "EndingBack.h"
#include "Brick.h"
#include "PlayCollision.h"
#include "Troopa.h"



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
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("fireball.wav"));
	}
	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("pipe.wav"));
	}
	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("1-up.wav"));
	}
	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("bump.wav"));
	}
	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("breakblock.wav"));
	}
	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("coin.wav"));
	}
	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("stomp.wav"));
	}
	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("vine.wav"));
	}
	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("growup.wav"));

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
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_Troopa.bmp"));
		Image->Cut(6, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_Troopa.bmp"));
		Image->Cut(6, 1);

		Dir.MoveParent();
	}

	//Effect
	{
		Dir.Move("Effect");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_Fire.bmp"));
		Image->Cut(7, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_Fire.bmp"));
		Image->Cut(7, 1);

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
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HiddenCoin.bmp"));
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
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Chip.bmp"));
		Image->Cut(2, 1);

		Dir.MoveParent();
	}
	{
		Dir.Move("Pipe");
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Pipe.bmp"));
		Image->Cut(2, 1);
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
	//액터 생성
	{
		PlayCollision* Actor = CreateActor<PlayCollision>();
	}
	//MainPlayer
	{
		Player* Actor = CreateActor<Player>();
		//Actor->SetPos({ 160, GameEngineWindow::GetScreenSize().y - 128});					// x = 128+mario.half

		//테스트용 위치 ------------------------------------------------------------지워야 함!!!!!!
		Actor->SetPos({ 800, GameEngineWindow::GetScreenSize().y - 128 } );
		SetCameraPos({ Actor->GetPos().x -200.0f, 0.0f});
	}
	//Goomba1
	{
		Goomba* Actor = CreateActor<Goomba>(MarioRenderOrder::Monster);
		float4 StartPos = GameEngineWindow::GetScreenSize();
		Actor->SetPos({1400, StartPos.y - 128});

		//일단 굼바 끔=-------------------------------------------------------------------------------------------
		//Actor->Off();
	}
	//Goomba2
	{
		Goomba* Actor = CreateActor<Goomba>(MarioRenderOrder::Monster);
		float4 StartPos = GameEngineWindow::GetScreenSize();
		Actor->SetPos({ 3200, StartPos.y - 128 });
	}
	//Troopa
	{
		Troopa* Actor = CreateActor<Troopa>(MarioRenderOrder::Monster);
		float4 StartPos = GameEngineWindow::GetScreenSize();
		Actor->SetPos({ 2200, StartPos.y - 128 });
	}
	//1_1_ITem1
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 1376, 640 });
		Actor->SetItemMode(ItemType::SUPERMUSHROOM);
		Actor->SetItemRenderOff();
		//일단 굼바 끔=------------------------------------------------------------------------------------------
	}
	//1_1_Item2
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 4128, 576 });
		Actor->SetItemMode(ItemType::LIFEMUSHROOM);
		Actor->SetItemRenderOff();
	}
	//1_1_Item3
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 5024, 640 });
		Actor->SetItemMode(ItemType::SUPERMUSHROOM);
		Actor->SetItemRenderOff();
	}
	//1_1_Item4
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 1060, 640 });
		Actor->SetItemRenderOff();
	}
	//1_1_Item5
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 1504, 640 });
		Actor->SetItemRenderOff();
	}
	//1_1_Item6
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 1440, 384 });
		Actor->SetItemRenderOff();
	}
	//1_1_Item7
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 6047, 384 });
		Actor->SetItemRenderOff();
	}
	//1_1_Item8
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 6815, 640 });
		Actor->SetItemRenderOff();
	}
	//1_1_Item9
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 7007, 640 });
		Actor->SetItemRenderOff();
	}
	//1_1_Item10
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 7199, 640 });
		Actor->SetItemRenderOff();
	}
	//1_1_Item11
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 7007, 384 });
		Actor->SetItemMode(ItemType::SUPERMUSHROOM);
		Actor->SetItemRenderOff();
	}
	//1_1_Item12
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 8289, 384 });
		Actor->SetItemRenderOff();
	}
	//1_1_Item13
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 8353, 384 });
		Actor->SetItemRenderOff();
	}
	//1_1_Item14
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 10913, 640 });
		Actor->SetItemRenderOff();
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
		Actor->SetPos({ 1376, 640 });									//block 바로 옆 64 차임
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
	//1_1_QBlock13
	{
		QuestionBlock* Actor = CreateActor<QuestionBlock>(MarioRenderOrder::Block);
		Actor->SetPos({ 10913, 640 });
	}
	//1_1_HiddenQBlock
	{
		QuestionBlock* Actor = CreateActor<QuestionBlock>(MarioRenderOrder::Block);
		Actor->SetPos({ 4128, 576 });
		Actor->SetQBlockRenOff();
	}

	//1_1_Brick1
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 1312, 640 });
	}
	//1_1_Brick2
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 1440, 640 });
	}
	//1_1_Brick3
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 1568, 640 });
	}
	//1_1_Brick4
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 4960, 640 });
	}
	//1_1_Brick5
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 5088, 640 });
	}
	//1_1_Brick6
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 5152, 384 });
	}
	//1_1_Brick7
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 5216, 384 });
	}
	//1_1_Brick8
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 5280, 384 });
	}
	//1_1_Brick9
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 5344, 384 });
	}
	//1_1_Brick10
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 5408, 384 });
	}
	//1_1_Brick11
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 5472, 384 });
	}
	//1_1_Brick12
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 5536, 384 });
	}
	//1_1_Brick13
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 5600, 384 });
	}
	//1_1_Brick14
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 5855, 384 });
	}
	//1_1_Brick15
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 5919, 384 });
	}
	//1_1_Brick16
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 5983, 384 });
	}
	//1_1_Brick17
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 6047, 640 });
	//	Actor->SetSpcBrick();                                            //에러남!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	//1_1_Brick18
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 6367, 640 });
	}
	//1_1_Brick19
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 6431, 640 });
	}
	//1_1_Brick20
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 7583, 640 });
	}
	//1_1_Brick21
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 7775, 384 });
	}
	//1_1_Brick22
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 7839, 384 });
	}
	//1_1_Brick23
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 7903, 384 });
	}
	//1_1_Brick24
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 8225, 384 });
	}
	//1_1_Brick25
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 8417, 384 });
	}
	//1_1_Brick26
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 8289, 640 });
	}
	//1_1_Brick27
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 8353, 640 });
	}
	//1_1_Brick28
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 10785, 640 });
	}
	//1_1_Brick29
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 10849, 640 });
	}
	//1_1_Brick30
	{
		Brick* Actor = CreateActor<Brick>(MarioRenderOrder::Block);
		Actor->SetPos({ 10977, 640 });
	}

	//Pipe1
	{
		Pipe* Actor = CreateActor<Pipe>(MarioRenderOrder::Pipe);
		Actor->SetPos({ 3712, 710 });
		Actor->SetExitColOff();
	}
	//Pipe2
	{
		Pipe* Actor = CreateActor<Pipe>(MarioRenderOrder::Pipe);
		Actor->SetPos({ 3978, 1790 });
		Actor->SetPipeMode(PipeType::LEFT);
		Actor->SetPipeRenScale({ 160, 308 });
		Actor->SetGateColOff();
	}
	//Pipe3
	{
		Pipe* Actor = CreateActor<Pipe>(MarioRenderOrder::Pipe);
		Actor->SetPos({ 10496, 840 });
		Actor->SetAllColOff();
	}
	//Coin1(diff = 64)
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 3424,1344 });
		Actor->SetItemRenderScale(CoinRenScale);
		Actor->SetColScale(CoinColScale);
		Actor->SetItemMode(ItemType::COIN);
		Actor->SetCoinMode();
	}
	//Coin2
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 3488,1344 });
		Actor->SetItemRenderScale(CoinRenScale);
		Actor->SetColScale(CoinColScale);
		Actor->SetItemMode(ItemType::COIN);
		Actor->SetCoinMode();
	}
	//Coin3
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 3552,1344 });
		Actor->SetItemRenderScale(CoinRenScale);
		Actor->SetColScale(CoinColScale);
		Actor->SetItemMode(ItemType::COIN);
		Actor->SetCoinMode();
	}
	//Coin4
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 3616,1344 });
		Actor->SetItemRenderScale(CoinRenScale);
		Actor->SetColScale(CoinColScale);
		Actor->SetItemMode(ItemType::COIN);
		Actor->SetCoinMode();

	}
	//Coin5
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 3680,1344 });
		Actor->SetItemRenderScale(CoinRenScale);
		Actor->SetColScale(CoinColScale);
		Actor->SetItemMode(ItemType::COIN);
		Actor->SetCoinMode();
	
	}
	//Coin6
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 3360, 1472 });
		Actor->SetItemRenderScale(CoinRenScale);
		Actor->SetColScale(CoinColScale);
		Actor->SetItemMode(ItemType::COIN);
		Actor->SetCoinMode();
	}
	//Coin7
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 3424, 1472 });
		Actor->SetItemRenderScale(CoinRenScale);
		Actor->SetColScale(CoinColScale);
		Actor->SetItemMode(ItemType::COIN);
		Actor->SetCoinMode();
	}
	//Coin8
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 3488, 1472 });
		Actor->SetItemRenderScale(CoinRenScale);
		Actor->SetColScale(CoinColScale);
		Actor->SetItemMode(ItemType::COIN);
		Actor->SetCoinMode();
	}
	//Coin9
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 3552, 1472 });
		Actor->SetItemRenderScale(CoinRenScale);
		Actor->SetColScale(CoinColScale);
		Actor->SetItemMode(ItemType::COIN);
		Actor->SetCoinMode();
	}
	//Coin10
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 3616, 1472 });
		Actor->SetItemRenderScale(CoinRenScale);
		Actor->SetColScale(CoinColScale);
		Actor->SetItemMode(ItemType::COIN);
		Actor->SetCoinMode();
	}
	//Coin11
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 3680, 1472 });
		Actor->SetItemRenderScale(CoinRenScale);
		Actor->SetColScale(CoinColScale);
		Actor->SetItemMode(ItemType::COIN);
		Actor->SetCoinMode();
	}
	//Coin12
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 3744, 1472 });
		Actor->SetItemRenderScale(CoinRenScale);
		Actor->SetColScale(CoinColScale);
		Actor->SetItemMode(ItemType::COIN);
		Actor->SetCoinMode();
	}
	//Coin13
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 3360, 1600 });
		Actor->SetItemRenderScale(CoinRenScale);
		Actor->SetColScale(CoinColScale);
		Actor->SetItemMode(ItemType::COIN);
		Actor->SetCoinMode();
	}
	//Coin14
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 3424, 1600 });
		Actor->SetItemRenderScale(CoinRenScale);
		Actor->SetColScale(CoinColScale);
		Actor->SetItemMode(ItemType::COIN);
		Actor->SetCoinMode();
	}
	//Coin15
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 3488, 1600 });
		Actor->SetItemRenderScale(CoinRenScale);
		Actor->SetColScale(CoinColScale);
		Actor->SetItemMode(ItemType::COIN);
		Actor->SetCoinMode();
	}
	//Coin16
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 3552, 1600 });
		Actor->SetItemRenderScale(CoinRenScale);
		Actor->SetColScale(CoinColScale);
		Actor->SetItemMode(ItemType::COIN);
		Actor->SetCoinMode();
	}
	//Coin17
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 3616, 1600 });
		Actor->SetItemRenderScale(CoinRenScale);
		Actor->SetColScale(CoinColScale);
		Actor->SetItemMode(ItemType::COIN);
		Actor->SetCoinMode();
	}
	//Coin18
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 3680, 1600 });
		Actor->SetItemRenderScale(CoinRenScale);
		Actor->SetColScale(CoinColScale);
		Actor->SetItemMode(ItemType::COIN);
		Actor->SetCoinMode();
	}
	//Coin19
	{
		Item* Actor = CreateActor<Item>(MarioRenderOrder::Item);
		Actor->SetPos({ 3744, 1600 });
		Actor->SetItemRenderScale(CoinRenScale);
		Actor->SetColScale(CoinColScale);
		Actor->SetItemMode(ItemType::COIN);
		Actor->SetCoinMode();
	}

	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		//VK: 알파뱃과 숫자를 제외한 키
		GameEngineInput::CreateKey("CameraLeftMove", VK_LEFT);			//방향키
		GameEngineInput::CreateKey("CameraRightMove", VK_RIGHT);
		GameEngineInput::CreateKey("CameraDownMove", VK_DOWN);
		GameEngineInput::CreateKey("CameraUpMove", VK_UP);

		GameEngineInput::CreateKey("Attack", VK_LSHIFT);

		GameEngineInput::CreateKey("DebugRenderSwitch", 'R');
		GameEngineInput::CreateKey("BGMPause", 'P');
		GameEngineInput::CreateKey("FreeMoveSwitch", '1');
		GameEngineInput::CreateKey("StageClear", '2');
		GameEngineInput::CreateKey("GoToCastle", '3');
		GameEngineInput::CreateKey("InvincibleMode", '7');
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

	//if (GameEngineInput::IsDown("StageClear"))
	//{
	//	//처음부터 다시 재생
	//}

	

	if (0 >= Player::PlayTimer)
	{
		EndingBack::Ending->SetEndingScene(EndingScene::TimeOver);
	}
}

void PlayLevel::SetBGMPlayer(const std::string_view& _String, int _loop, float _BasicVolume)
{
	BGMPlayer.Stop();
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl(_String.data());
	BGMPlayer.LoopCount(_loop);
	BGMPlayer.Volume(_BasicVolume);
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPlayLevel = this;

	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("RunningAbout.mp3");
	BGMPlayer.LoopCount(MaxLoop);
	BGMPlayer.Volume(BGMVolume);

}

void PlayLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}


