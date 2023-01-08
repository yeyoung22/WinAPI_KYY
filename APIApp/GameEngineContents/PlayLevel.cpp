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
	//Loading 시점: 만들어야할 것들을 만드는 시점
	CreateActor<Player>();
}

void PlayLevel::Update()
{

}
