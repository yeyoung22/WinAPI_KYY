#include "ContentsUI.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/NumberRenderObject.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Player.h"
#include "PlayLevel.h"

ContentsUI::ContentsUI() 
{
}

ContentsUI::~ContentsUI() 
{
}



void ContentsUI::Start()
{
	NumberSets.SetOwner(this);
	NumberSets.SetImage("Number.bmp", { 60, 64 }, 10, RGB(255, 0, 255));
	NumberSets.SetValue(static_cast<int>(Player::PlayTimer));
	NumberSets.SetAlign(Align::Right);
	float4 StartPos = GameEngineWindow::GetScreenSize();
	NumberSets.SetRenderPos({ StartPos.x - 256, StartPos.y - 64 });
	NumberSets.SetCameraEffect(false);

}

void ContentsUI::Update(float _DeltaTime)
{
	NumberSets.SetValue(static_cast<int>(Player::PlayTimer));
}