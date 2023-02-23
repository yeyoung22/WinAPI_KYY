#include "Block.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"

Block::Block() 
{
}

Block::~Block() 
{
}

void Block::Start()
{
	{
		BlockRender = CreateRender(MarioRenderOrder::Block);
		BlockRender->SetScale({ 128, 128 });

		BlockRender->CreateAnimation({ .AnimationName = "QuestionBlock",  .ImageName = "QuestionBlock.bmp", .Start = 0, .End = 3 });
		BlockRender->ChangeAnimation("QuestionBlock");
	}
	{
		BlockRender->CreateAnimation({ .AnimationName = "UsedBlock",  .ImageName = "UsedBlock.bmp", .Start = 0, .End = 0 });
	}
	{
		BlockCollision = CreateCollision(MarioCollisionOrder::Block);
		BlockCollision->SetScale({ 64, 10 });
		//BlockCollision->Off();
	}
}


void Block::Update(float _DeltaTime)
{
	if (nullptr != BlockCollision)
	{
		std::vector<GameEngineCollision*> Collision;
		if (true == BlockCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player) }, Collision))
		{
			for (size_t i = 0; i < Collision.size(); i++)
			{
				// Block* FindMonster = Collision[i]->GetOwner<Block>();

				GameEngineActor* ColActor = Collision[i]->GetActor();

				BlockRender->ChangeAnimation("UsedBlock");
			}
		}
	}
}