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

		RenderPosSets.push_back(StartPos);
	}

	{
		MapRender1 = CreateRender(MarioRenderOrder::Map);
		MapRender1->SetImage("World1_4.Bmp");

		float4 StartPos = MapRender0->GetImage()->GetImageScale();
		StartPos.x += MapRender1->GetImage()->GetImageScale().half().x;
		MapRender1->SetPosition({StartPos.x, MapRender1->GetImage()->GetImageScale().half().y});
		MapRender1->SetScaleToImage();

		RenderPosSets.push_back({StartPos.x, MapRender1->GetImage()->GetImageScale().half().y });
	}

	{
		BodyCollision = CreateCollision(MarioCollisionOrder::Door);
		BodyCollision->SetScale({ 50, 50 });
		float4 MapSize = MapRender0->GetImage()->GetImageScale();
		BodyCollision->SetPosition({ MapSize.x-390, MapSize.hy()-192});

		BodyCollision->SetDebugRenderType(CT_Rect);

	}

	//0���� ¦��: ���� ��
	//0���� Ȧ��: �ȼ� �浹�� ��
	Maps.push_back("World1_1.bmp");
	Maps.push_back("World1_4.Bmp");
	ColMaps.push_back("ColWorld1_1.bmp");
	ColMaps.push_back("ColWorld1_4.bmp");

	MapRenders.push_back(MapRender0);
	MapRenders.push_back(MapRender1);

	

}


void Map::Update(float _DeltaTime)
{
	if (0 != Player::Round)
	{
		SumMapWidth += GetMapImgScale(1).x;
	}

	if (true == Player::IsDebugMode)
	{
		MapRenders[Player::Round]->SetImage(ColMaps[Player::Round]);
		MapRenders[Player::Round]->SetPosition(RenderPosSets[Player::Round]);
		MapRenders[Player::Round]->SetScaleToImage();

		for (int i = 0; i < MapRenders.size(); i++)
		{
			if (i != Player::Round)
			{
				MapRenders[i]->Off();
			}
			else
			{
				MapRenders[i]->On();
			}
		}
	}
	else if(false == Player::IsDebugMode)
	{
		MapRenders[Player::Round]->SetImage(Maps[Player::Round]);
		MapRenders[Player::Round]->SetPosition(RenderPosSets[Player::Round]);
		MapRenders[Player::Round]->SetScaleToImage();

		for (int i = 0; i < MapRenders.size(); i++)
		{
			if (i != Player::Round)
			{
				MapRenders[i]->Off();
			}
			else
			{
				MapRenders[i]->On();
			}
		}
	}

	if (true == IsStageClear)
	{
		IsStageClear = false;
	}
}

float4 Map::GetMapImgScale(int _Value)
{

	float4 CurScale = MapRenders[static_cast<int>(Player::Round) - _Value]->GetImage()->GetImageScale();
	return CurScale;
}