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

SPSymbolRenderObject SymbolSets;
std::string_view Symbols = "";


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
		ScoreSets.SetNumOfDigits(6);
		ScoreSets.SetValue(Player::TotalScore);
		ScoreSets.SetAlign(Align::Right);
		ScoreSets.SetRenderPos({ GetPos().x - 680, GetPos().y });
		ScoreSets.SetCameraEffect(false);
	}
	//Number Of Coin
	{
		NumCoinSets.SetOwner(this);
		NumCoinSets.SetImage("Number.bmp", NumberScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		NumCoinSets.SetNumOfDigits(2);
		NumCoinSets.SetValue(Player::NumOfCoin);
		NumCoinSets.SetAlign(Align::Right);

		NumCoinSets.SetRenderPos({ GetPos().x - 470, GetPos().y });
		NumCoinSets.SetCameraEffect(false);
	}
	//World Level
	{
		WorldLevelSets.SetOwner(this);
		WorldLevelSets.SetImage("Number.bmp", NumberScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		WorldLevelSets.SetValue(Player::WorldLevel);
		WorldLevelSets.SetAlign(Align::Right);

		WorldLevelSets.SetRenderPos({ GetPos().x - 370, GetPos().y });
		WorldLevelSets.SetCameraEffect(false);
	}
	//Map Level
	{
		MapLevelSets.SetOwner(this);
		MapLevelSets.SetImage("Number.bmp", NumberScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		MapLevelSets.SetValue(Player::MapLevel);
		MapLevelSets.SetAlign(Align::Right);

		MapLevelSets.SetRenderPos({ GetPos().x - 280, GetPos().y });
		MapLevelSets.SetCameraEffect(false);
	}
	//Word
	{
		W_Nickname.SetOwner(this);
		W_Nickname.SetImage("Alphabet.bmp", WordScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		W_Nickname.SetValue(Words = "Mario");
		W_Nickname.SetRenderPos({ GetPos().x - 850, GetPos().y - 38 });
		W_Nickname.SetCameraEffectOff();
	}
	{
		W_Time.SetOwner(this);
		W_Time.SetImage("Alphabet.bmp", WordScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		W_Time.SetValue(Words = "Time");
		W_Time.SetRenderPos({ GetPos().x - 100, GetPos().y - 38});
		W_Time.SetCameraEffectOff();
	}
	{
		W_World.SetOwner(this);
		W_World.SetImage("Alphabet.bmp", WordScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		W_World.SetValue(Words = "world");
		W_World.SetRenderPos({ GetPos().x - 400, GetPos().y - 38 });
		W_World.SetCameraEffectOff();
	}
	//Symbol
	{
		S_Hyphen.SetOwner(this);
		S_Hyphen.SetImage("SpecialSymbol.bmp", SymbolScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		S_Hyphen.SetValue(Symbols = "-");
		S_Hyphen.SetRenderPos({ GetPos().x - 324, GetPos().y - 9});
		S_Hyphen.SetCameraEffectOff();
	}
	{
		S_Asterisk.SetOwner(this);
		S_Asterisk.SetImage("SpecialSymbol.bmp", SymbolScale, static_cast<int>(MarioRenderOrder::UI), RGB(255, 0, 255));
		S_Asterisk.SetValue(Symbols = "*");
		S_Asterisk.SetRenderPos({ GetPos().x - 560, GetPos().y });
		S_Asterisk.SetCameraEffectOff();
	}
	//코인 애니메이션용 랜더
	{
		AnimationRender = CreateRender("CoinUI.bmp", MarioRenderOrder::UI);
		AnimationRender->SetPosition({ GetPos().x - 600, GetPos().y });
		AnimationRender->SetScale({ AnimationRender->GetImage()->GetImageScale().x, AnimationRender->GetImage()->GetImageScale().y+20 });
		AnimationRender->CreateAnimation({ .AnimationName = "CoinUI",  .ImageName = "CoinUI.bmp", .Start = 2, .End = 3, .Loop = true });
		AnimationRender->EffectCameraOff();
	}


}

void ContentsUI::Update(float _DeltaTime)
{
	TimerSets.SetValue(static_cast<int>(Player::PlayTimer));
	ScoreSets.SetValue(Player::TotalScore);
	NumCoinSets.SetValue(Player::NumOfCoin);
	WorldLevelSets.SetValue(Player::WorldLevel);
	MapLevelSets.SetValue(Player::MapLevel);
	AnimationRender->ChangeAnimation("CoinUI");

	
}