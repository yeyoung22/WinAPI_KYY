#include "ContentsUI.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"
#include "PlayLevel.h"
#include "WordRenderObject.h"
#include "SPSymbolRenderObject.h"
#include "NumberRenderObjectEX.h"

ContentsUI::ContentsUI() 
{
}

ContentsUI::~ContentsUI() 
{
}

std::string_view Symbols = "";


void ContentsUI::Start()
{
	LevelNames.push_back("TitleLevel");
	LevelNames.push_back("OpeningLevel");
	LevelNames.push_back("PlayLevel");
	LevelNames.push_back("EndingLevel");

	

	//Timer
	{
		TimerSets.SetOwner(this);
		TimerSets.SetImage("Number.bmp", NumberScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		TimerSets.SetValue(static_cast<int>(Player::PlayTimer));
		TimerSets.SetAlign(Align::Right);

		TimerSets.SetRenderPos({ GetPos().x - 34, GetPos().y+ 36 });
		TimerSets.SetCameraEffect(false);
	}
	//Total Score
	{
		ScoreSets.SetOwner(this);
		ScoreSets.SetImage("Number.bmp", NumberScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		ScoreSets.SetNumOfDigits(6);
		ScoreSets.SetValue(Player::TotalScore);
		ScoreSets.SetAlign(Align::Right);
		ScoreSets.SetRenderPos({ GetPos().x - 680, GetPos().y + 36 });
		ScoreSets.SetCameraEffect(false);
	}
	//Number Of Coin
	{
		NumCoinSets.SetOwner(this);
		NumCoinSets.SetImage("Number.bmp", NumberScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		NumCoinSets.SetNumOfDigits(2);
		NumCoinSets.SetValue(Player::NumOfCoin);
		NumCoinSets.SetAlign(Align::Right);

		NumCoinSets.SetRenderPos({ GetPos().x - 470, GetPos().y + 36 });
		NumCoinSets.SetCameraEffect(false);
	}
	//World Level
	{
		WorldLevelSets.SetOwner(this);
		WorldLevelSets.SetImage("Number.bmp", NumberScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		WorldLevelSets.SetValue(Player::WorldLevel);
		WorldLevelSets.SetAlign(Align::Right);

		WorldLevelSets.SetRenderPos({ GetPos().x - 308, GetPos().y + 36 });
		WorldLevelSets.SetCameraEffect(false);
	}
	//Map Level
	{
		MapLevelSets.SetOwner(this);
		MapLevelSets.SetImage("Number.bmp", NumberScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		MapLevelSets.SetValue(Player::MapLevel);
		MapLevelSets.SetAlign(Align::Right);

		MapLevelSets.SetRenderPos({ GetPos().x - 244, GetPos().y + 36 });
		MapLevelSets.SetCameraEffect(false);
	}
	//World Level2
	{
		WorldLevelSets2.SetOwner(this);
		WorldLevelSets2.SetImage("Number.bmp", NumberScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		WorldLevelSets2.SetValue(Player::WorldLevel);
		WorldLevelSets2.SetAlign(Align::Right);

		WorldLevelSets2.SetRenderPos({ GetPos().x - 372, GetPos().y + 264 });
		WorldLevelSets2.SetCameraEffect(false);
	}
	//Map Level2
	{
		MapLevelSets2.SetOwner(this);
		MapLevelSets2.SetImage("Number.bmp", NumberScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		MapLevelSets2.SetValue(Player::MapLevel);
		MapLevelSets2.SetAlign(Align::Right);
					
		MapLevelSets2.SetRenderPos({ GetPos().x - 308, GetPos().y + 264 });
		MapLevelSets2.SetCameraEffect(false);
	}
	//TopScore
	{
		TopScoreSets.SetOwner(this);
		TopScoreSets.SetImage("Number.bmp", NumberScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		TopScoreSets.SetNumOfDigits(6);
		TopScoreSets.SetValue(Player::TotalScore);
		TopScoreSets.SetAlign(Align::Right);
		TopScoreSets.SetRenderPos({ GetPos().x - 244, GetPos().y + 680 });
		TopScoreSets.SetCameraEffect(false);
	}
	//Life
	{
		LifeSets.SetOwner(this);
		LifeSets.SetImage("Number.bmp", NumberScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		LifeSets.SetValue(Player::Life);
		LifeSets.SetAlign(Align::Right);
		LifeSets.SetRenderPos({ GetPos().x - 342, GetPos().y + 390 });
		LifeSets.SetCameraEffect(false);
	}

	//Word
	{
		W_Nickname.SetOwner(this);
		W_Nickname.SetImage("Alphabet.bmp", WordScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		W_Nickname.SetValue(Words = "Mario");
		W_Nickname.SetRenderPos({ GetPos().x - 827, GetPos().y + 5 });
		W_Nickname.SetCameraEffectOff();
	}
	{
		W_Time.SetOwner(this);
		W_Time.SetImage("Alphabet.bmp", WordScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		W_Time.SetValue(Words = "Time");
		W_Time.SetRenderPos({ GetPos().x - 116, GetPos().y +5});
		W_Time.SetCameraEffectOff();
	}
	{
		W_World.SetOwner(this);
		W_World.SetImage("Alphabet.bmp", WordScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		W_World.SetValue(Words = "world");
		W_World.SetRenderPos({ GetPos().x - 341, GetPos().y +5});
		W_World.SetCameraEffectOff();
	}
	//Symbol
	{
		S_Hyphen.SetOwner(this);
		S_Hyphen.SetImage("SpecialSymbol.bmp", SymbolScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		S_Hyphen.SetValue(Symbols = "-");
		S_Hyphen.SetRenderPos({ GetPos().x - 273, GetPos().y + 32});
		S_Hyphen.SetCameraEffectOff();
	}
	{
		S_Asterisk.SetOwner(this);
		S_Asterisk.SetImage("SpecialSymbol.bmp", SymbolScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		S_Asterisk.SetValue(Symbols = "*");
		S_Asterisk.SetRenderPos({ GetPos().x - 534, GetPos().y + 37 });				//+36
		S_Asterisk.SetCameraEffectOff();
	}
	//코인 애니메이션용 랜더
	{
		AnimationRender = CreateRender("CoinUI.bmp", MarioRenderOrder::UI);
		AnimationRender->SetPosition({ GetPos().x - 574, GetPos().y + 42 });
		AnimationRender->SetScale({128, 128});
		AnimationRender->CreateAnimation({ .AnimationName = "CoinUI",  .ImageName = "CoinUI.bmp", .Start = 0, .End = 3, .Loop = true });
		AnimationRender->EffectCameraOff();
	}
	AnimationRender->ChangeAnimation("CoinUI");
}

void ContentsUI::Update(float _DeltaTime)
{
	std::string CurLevelName = GetLevel()->GetName();


	if (LevelNames[0] == CurLevelName)
	{
		TimerSets.Off();
		LifeSets.Off();
		WorldLevelSets2.Off();
		MapLevelSets2.Off();
		TopScoreSets.SetValue(Player::TotalScore);
	}
	else if (LevelNames[1] == CurLevelName)
	{
		TimerSets.Off();
		TopScoreSets.Off();

		WorldLevelSets2.SetValue(Player::WorldLevel);
		MapLevelSets2.SetValue(Player::MapLevel);
	}
	else if (LevelNames[2] == CurLevelName)
	{
		TopScoreSets.Off();
		LifeSets.Off();
		WorldLevelSets2.Off();
		MapLevelSets2.Off();
	}
	else if ((LevelNames[3] == CurLevelName))
	{
		TopScoreSets.Off();
		LifeSets.Off();
		WorldLevelSets2.Off();
		MapLevelSets2.Off();
	}

	ScoreSets.SetValue(Player::TotalScore);
	NumCoinSets.SetValue(Player::NumOfCoin);
	WorldLevelSets.SetValue(Player::WorldLevel);
	MapLevelSets.SetValue(Player::MapLevel);


	TimerSets.SetValue(static_cast<int>(Player::PlayTimer));
}