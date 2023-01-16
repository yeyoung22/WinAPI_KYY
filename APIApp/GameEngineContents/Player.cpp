#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineResources.h>


Player::Player() 
{
}

Player::~Player() 
{
}

void Player::Start()
{
	SetMove(GameEngineWindow::GetScreenSize().half());
}

void Player::Update()
{
	SetMove(float4::Left * 0.0001f);
}

void Player::Render()
{
	float4 PlayerPos = GetPos();

	//GameEnginePath Path;

	//std::string PathText = Path.GetPathToString();

	// TextOutA(GameEngineWindow::GetDrawHdc(), 0, 0, PathText.c_str(), PathText.size());


	//Rectangle(
	//	GameEngineWindow::GetDoubleBufferImage()->GetImageDC(),
	//	PlayerPos.ix() - 50,
	//	PlayerPos.iy() - 50,
	//	PlayerPos.ix() + 50,
	//	PlayerPos.iy() + 50
	//);


	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("MarioCustoms.bmp");

	// 프레임 애니메이션이라고 합니다.
	//GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, 4, PlayerPos, { 100, 200 });

	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, /*PlayerPos - float4{ 50, 50 }*/{0, 0}, { 20, 20 }, float4::Left, Image->GetImageScale());

	// 비율이 어긋날수록 더 느려진다.
	//GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, PlayerPos, { 30, 50 }, { 41, 56 }, {150, 18});
}