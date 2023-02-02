#include "PlayLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "Player.h"
#include "Map.h"
#include "Monster.h"
#include "ContentsEnums.h"


PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

//Loading ����: �������� �͵��� ����� ����
void PlayLevel::Loading()
{
	//��� ���
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");

	//�̹��� �ε�
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
	}
	{
	
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("World1_4.bmp"));
		GameEngineImage* ColImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ColWorld1_4.bmp"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Goomba.bmp"));
		Image->Cut(3, 1);
	}
	//���� ����
	{
		Map* Actor = CreateActor<Map>();
	}
	{
		Monster* Actor = CreateActor<Monster>();
		float4 StartPos = GameEngineWindow::GetScreenSize();
		Actor->SetPos({ StartPos.x * 2- StartPos.half().x , StartPos.y - 128});
	}
	{
		Player* Actor = CreateActor<Player>();
		Actor->SetPos({ 160, GameEngineWindow::GetScreenSize().y - 128});					// x = 128+mario.half
	
	}

	if (false == GameEngineInput::IsKey("PlayerOff"))
	{
		GameEngineInput::CreateKey("PlayerOff", 'R');
	}


	if (false == GameEngineInput::IsKey("CameraLeftMove"))
	{
		//VK: ���Ĺ�� ���ڸ� ������ Ű
		GameEngineInput::CreateKey("CameraLeftMove", VK_LEFT);			//����Ű
		GameEngineInput::CreateKey("CameraRightMove", VK_RIGHT);
		GameEngineInput::CreateKey("CameraDownMove", VK_DOWN);
		GameEngineInput::CreateKey("CameraUpMove", VK_UP);
	}


}

void PlayLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("PlayerOff"))
	{
		Player::MainPlayer->OnOffSwtich();
	}
}