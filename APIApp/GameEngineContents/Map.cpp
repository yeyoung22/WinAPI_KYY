#include "Map.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsEnums.h"
#include "Player.h"





float Map::SumMapWidth = 0.0f;
Map* Map::MainMap = nullptr;

Map::Map() 
{
	MainMap = this;
}

Map::~Map() 
{
}

void Map::Start()
{
	{
		MapRender0 = CreateRender(MarioRenderOrder::Map);
		MapRender0->SetImage("World1_1.bmp");
		float4 StartPos = MapRender0->GetImage()->GetImageScale().half();				 //{ 6752, 960 }
		MapRender0->SetPosition(StartPos);
		MapRender0->SetScaleToImage();

		SumMapWidth = MapRender0->GetImage()->GetImageScale().x;
	}

	{
		MapRender1 = CreateRender(MarioRenderOrder::Map);
		MapRender1->SetImage("World1_4.Bmp");

		float4 StartPos = MapRender0->GetImage()->GetImageScale();
		StartPos.x += MapRender1->GetImage()->GetImageScale().half().x;
		MapRender1->SetPosition({StartPos.x, MapRender1->GetImage()->GetImageScale().half().y});
		MapRender1->SetScaleToImage();
	}

	{
		BodyCollision = CreateCollision(MarioCollisionOrder::Door);
		BodyCollision->SetScale({ 40, 40 });
		float4 MapSize = MapRender0->GetImage()->GetImageScale();
		BodyCollision->SetPosition({ MapSize.x-420, MapSize.hy()-192});

	}
}


void Map::Update(float _DeltaTime)
{
	//if (true == IsStageClear)
	//{
	//	SumMapWidth += MapRender1->GetImage()->GetImageScale().x;

	//	IsStageClear = false;
	//}

	if (true == Player::IsDebugMode)
	{
		MapRender0->SetImage("ColWorld1_1.bmp");
		float4 StartPos = MapRender0->GetImage()->GetImageScale().half();				 //{ 6752, 960 }
		MapRender0->SetPosition(StartPos);
		MapRender0->SetScaleToImage();
	}
	else
	{
		MapRender0->SetImage("World1_1.bmp");
		float4 StartPos = MapRender0->GetImage()->GetImageScale().half();				 //{ 6752, 960 }
		MapRender0->SetPosition(StartPos);
		MapRender0->SetScaleToImage();
	}

	if (true == IsStageClear)
	{
		float4 RenPos = MapRender1->GetImage()->GetImageScale().half();
		MapRender1->SetPosition({ RenPos.x, RenPos.y });

		IsStageClear = false;
	}
}