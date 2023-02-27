#include "Monster.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"

Monster::Monster() 
{
}

Monster::~Monster() 
{
}


void Monster::Start()
{
	{
		AnimationRender = CreateRender(MarioRenderOrder::Monster);
		AnimationRender->SetScale({ 128, 128 });

		AnimationRender->CreateAnimation({ .AnimationName = "Goomba_Idle",  .ImageName = "Goomba.bmp", .Start = 0, .End = 1 });
		AnimationRender->ChangeAnimation("Goomba_Idle");
	}
	{
		BodyCollision = CreateCollision(MarioCollisionOrder::Monster);
		BodyCollision->SetScale({ 50, 50 });
		BodyCollision->SetPosition({ GetPos() });
		
		
		
		//일단 굼바 꺼둠
		//BodyCollision->Off();
	}
}


void Monster::Update(float _DeltaTime)
{
	float4 Dir = float4::Left * MoveSpeed * _DeltaTime;
	SetMove(Dir);

	//<굼바가 죽는 조건_with Koopa>
	//맵을 벗어났으면 죽어야 함
	//구멍에 빠지면 죽음
	//불꽃에 맞아도 죽음
	//머리를 밟혀도 죽음(마리오의 바닥 충돌체와 이 아이의 좌우 충돌체가 닿이면 죽음

	//<트루파 죽는 조건>
	//굼바와 대부분 동일
	//밟으면 등껍질로 애니메이션 변경_안 죽음
	//한 번더 밟으면 정해진 방향으로 날아감(기본은 오른쪽)
	//일정시간동안 안 밟히면 다시 부활
	//날아가다가 구멍에 빠지면 죽음

	

}