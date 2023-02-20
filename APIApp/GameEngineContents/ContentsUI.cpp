#include "ContentsUI.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/NumberRenderObject.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"
#include "PlayLevel.h"
#include "TextRenderObject.h"

ContentsUI::ContentsUI() 
{
}

ContentsUI::~ContentsUI() 
{
}



void ContentsUI::Start()
{
	//Timer
	{
		TimerSets.SetOwner(this);
		TimerSets.SetImage("Number.bmp", NumberScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		TimerSets.SetValue(static_cast<int>(Player::PlayTimer));
		TimerSets.SetAlign(Align::Right);

		TimerSets.SetRenderPos({ GetPos().x, GetPos().y });
		TimerSets.SetCameraEffect(false);
	}

	//Total Score
	{
		ScoreSets.SetOwner(this);
		ScoreSets.SetImage("Number.bmp", NumberScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		ScoreSets.SetValue(Player::TotalScore);
		ScoreSets.SetAlign(Align::Right);

		ScoreSets.SetRenderPos({ GetPos().x - 700, GetPos().y });
		ScoreSets.SetCameraEffect(false);
	}
	//Number Of Coin
	{
		NumCoinSets.SetOwner(this);
		NumCoinSets.SetImage("Number.bmp", NumberScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		NumCoinSets.SetValue(Player::NumOfCoin);
		NumCoinSets.SetAlign(Align::Right);

		NumCoinSets.SetRenderPos({ GetPos().x - 500, GetPos().y });
		NumCoinSets.SetCameraEffect(false);
	}
	//World Level
	{
		WorldLevelSets.SetOwner(this);
		WorldLevelSets.SetImage("Number.bmp", NumberScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		WorldLevelSets.SetValue(Player::WorldLevel);
		WorldLevelSets.SetAlign(Align::Right);

		WorldLevelSets.SetRenderPos({ GetPos().x - 300, GetPos().y });
		WorldLevelSets.SetCameraEffect(false);
	}

	{
		WTime.SetOwner(this);
		WTime.SetImage("Alphabet.bmp", WordScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		WTime.SetValue(Words = "Time");

		WTime.SetRenderPos({ GetPos().x - 100, GetPos().y - 38});
		WTime.SetCameraEffectOff();
	}


}

void ContentsUI::Update(float _DeltaTime)
{
	TimerSets.SetValue(static_cast<int>(Player::PlayTimer));
	ScoreSets.SetValue(Player::TotalScore);
	NumCoinSets.SetValue(Player::NumOfCoin);
	WorldLevelSets.SetValue(Player::WorldLevel);
	


	
}