#include "PlayLevel.h"
#include "Player.h"
//#include <GameEngineBase/GameEngineDirectory.h>

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{
	//Loading ����: �������� �͵��� ����� ����
	CreateActor<Player>();
}

void PlayLevel::Update()
{

}
