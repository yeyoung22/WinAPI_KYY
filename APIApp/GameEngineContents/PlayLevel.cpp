#include "PlayLevel.h"
#include "Player.h"
#include <GameEngineBase/GameEngineDirectory.h>

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

//Loading ����: �������� �͵��� ����� ����
void PlayLevel::Loading()
{
	//���� ���
	//"D:\yeyoung\0_Academy\Portfolio\WinAPI_KYY\APIApp\ContentsResources\Image\Luigi_test.bmp";
	// std::string Text = "D:\yeyoung\0_Academy\Portfolio\WinAPI_KYY\APIApp\ContentsResources\Image\Luigi_test.bmp";

	GameEngineDirectory Dir;

	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");

	Dir.GetPlusFileName("Luigi_test.BMP");

	CreateActor<Player>();
}

void PlayLevel::Update()
{

}
