#include "Map.h"
#include <GameEnginePlatform/GameEngineWindow.h>
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
	//{
	//	GameEngineRender* AnimationRender = CreateRender(
	// RenderOrder::Map);
	//	AnimationRender->SetPosition({ 3376*2, 960});
	//	//이미지 확대해야 함(setScaletoimage()함수로 이미지의 실제 크기를 가져옴)
	//	AnimationRender->SetScale({13504, 1920});


	//	AnimationRender->SetImage("World1_1.bmp");
	//
	//}

	{
		MapRender0 = CreateRender(MarioRenderOrder::Map);
		MapRender0->SetImage("World1_1.bmp");
		MapRender0->SetPosition(MapRender0->GetImage()->GetImageScale().half());
		MapRender0->SetScaleToImage();
	}

	{
		MapRender1 = CreateRender(MarioRenderOrder::Map);
		//1_4로 교체해야 함
		MapRender1->SetImage("World1_1.Bmp");

		float4 StartPos = MapRender0->GetImage()->GetImageScale().half();
		StartPos.x += GameEngineWindow::GetScreenSize().x;
		MapRender1->SetPosition(StartPos);
		MapRender1->SetScaleToImage();
	}

}


void Map::Update(float _DeltaTime)
{
	if (false == IsStageClear)
	{
		return;
	}

	//MapRender1->SetPosition({ 0, 0});
	


	//if (true == IsStageClear)
	//{
	//	MapRender1->SetMove(float4::Left * 200.0f * _DeltaTime);

	//}
}