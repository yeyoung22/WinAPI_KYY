#include "Map.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

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
		BodyCollision->SetPosition({ MapSize.x-128, MapSize.y });

	}
}


void Map::Update(float _DeltaTime)
{


	if (false == IsStageClear)
	{
		return;
	}

	if (BodyCollision != 0)
	{
	
	}




	float4 StartPos = MapRender1->GetImage()->GetImageScale().half();				 //{ 6752, 960 }
	MapRender1->SetPosition(StartPos);
}