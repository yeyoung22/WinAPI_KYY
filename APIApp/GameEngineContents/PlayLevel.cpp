#include "PlayLevel.h"
#include "Player.h"
#include <GameEngineBase/GameEngineDirectory.h>

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

//Loading 시점: 만들어야할 것들을 만드는 시점
void PlayLevel::Loading()
{
	//절대 경로
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
