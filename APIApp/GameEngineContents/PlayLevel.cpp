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
	//Dir.Move("Luigi_test.BMP");


	//Dir.GetPlusFileName("Luigi_test.BMP");


	GameEngineDirectory TmpDir ;

	TmpDir.MoveParent();

	TmpDir.LeaveFile("\\Luigi_test.bmp");
	Dir.MoveParent();

	int a = 0;
	



	CreateActor<Player>();
}

void PlayLevel::Update()
{

}
