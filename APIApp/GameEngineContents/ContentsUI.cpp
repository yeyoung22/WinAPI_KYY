#include "ContentsUI.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/NumberRenderObject.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
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
	ContentsUI::NumberSets.SetOwner(this);
	NumberSets.SetImage("Number.bmp", { 60, 64 }, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
	NumberSets.SetValue(static_cast<int>(Player::PlayTimer));
	NumberSets.SetAlign(Align::Right);

	
	NumberSets.SetRenderPos({ GetPos().x, GetPos().y });
	NumberSets.SetCameraEffect(true);

}

void ContentsUI::Update(float _DeltaTime)
{
	NumberSets.SetValue(static_cast<int>(Player::PlayTimer));
	
	
}