#include "Map.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnums.h"

Map::Map() 
{
}

Map::~Map() 
{
}

void Map::Start()
{
	{
		GameEngineRender* AnimationRender = CreateRender(MarioRenderOrder::Map);
		AnimationRender->SetPosition({ 3376*2, 960});
	
		
		//이미지 확대해야 함
		AnimationRender->SetScale({3376*4, 480*4});


		AnimationRender->SetImage("World1_1.bmp");
	
	}

}