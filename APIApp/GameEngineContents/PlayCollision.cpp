#include "PlayCollision.h"
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"
#include "Player.h"
#include "Goomba.h"
#include "Troopa.h"
#include "Item.h"

PlayCollision::PlayCollision() 
{
}

PlayCollision::~PlayCollision() 
{
}



void PlayCollision::Start()
{
	{
		DeadLineCol1 = CreateCollision(MarioCollisionOrder::DeadLine);
		DeadLineCol1->SetScale({ 128, 10 });
		DeadLineCol1->SetPosition({ 1100, GetPos().y - 800});
		DeadLineCol1->SetDebugRenderType(CT_Rect);
	}
	{
		DeadLineCol1 = CreateCollision(MarioCollisionOrder::DeadLine);
		DeadLineCol1->SetScale({ 192, 10 });
		DeadLineCol1->SetPosition({ 1400, GetPos().y - 800 });
		DeadLineCol1->SetDebugRenderType(CT_Rect);
	}
	{
		DeadLineCol1 = CreateCollision(MarioCollisionOrder::DeadLine);
		DeadLineCol1->SetScale({ 128, 10 });
		DeadLineCol1->SetPosition({ 2400, GetPos().y - 800 });
		DeadLineCol1->SetDebugRenderType(CT_Rect);
	}
	{
		FlagCollision = CreateCollision(MarioCollisionOrder::DeadLine);
		FlagCollision->SetScale({10, 576 });
		FlagCollision->SetPosition({ 8600, GetPos().y  });
		FlagCollision->SetDebugRenderType(CT_Rect);
	}
}


void PlayCollision::Update(float _DeltaTime) 
{

}