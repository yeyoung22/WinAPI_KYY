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
	
		
		//�̹��� Ȯ���ؾ� ��(setScaletoimage()�Լ��� �̹����� ���� ũ�⸦ ������)
		AnimationRender->SetScale({13504, 1920});


		AnimationRender->SetImage("World1_1.bmp");
	
	}

}