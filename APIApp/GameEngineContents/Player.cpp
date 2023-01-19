#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

 Player* Player::MainPlayer;

Player::Player() 
{
}

Player::~Player() 
{
}

void Player::Start()
{
	MainPlayer = this;

	SetMove(GameEngineWindow::GetScreenSize().half());

	{
		GameEngineRender* Render = CreateRender("Mario.bmp", MarioRenderOrder::BackGround);
		Render->SetScale({ 100, 100 });
		Render->SetFrame(4);
	}
}

void Player::Update(float _DeltaTime)
{
	//SetMove(float4::Left * 0.0001f);
}

void Player::Render(float _DeltaTime)
{
	float4 PlayerPos = GetPos();

	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("Mario.bmp");

	// 프레임 애니메이션
//	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, 0, {0, 0}, { 100, 200 });

	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, PlayerPos - float4{ 50, 50 }, { 100, 100 }, float4::Left, Image->GetImageScale());

	// 비율이 어긋날수록 더 느려진다.
	//GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, PlayerPos, { 30, 50 }, { 41, 56 }, {150, 18});
}