#include "Goomba.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"

#include <GameEnginePlatform/GameEngineWindow.h>

Goomba::Goomba() 
{
}

Goomba::~Goomba() 
{
}

void Goomba::Start()
{
	{
		AnimationRender = CreateRender(MarioRenderOrder::Monster);
		AnimationRender->SetScale({ 128, 128 });

		AnimationRender->CreateAnimation({ .AnimationName = "Goomba_Idle",  .ImageName = "Goomba.bmp", .Start = 0, .End = 1 });
		AnimationRender->CreateAnimation({ .AnimationName = "Goomba_Death",  .ImageName = "Goomba.bmp", .Start = 2, .End = 2 });
		AnimationRender->ChangeAnimation("Goomba_Idle");
	}
	{
		HeadCollision = CreateCollision(MarioCollisionOrder::Monster);
		HeadCollision->SetScale({ 30, 20 });
		HeadCollision->SetPosition({ GetPos().x, GetPos().y - 50 });
	}
	{
		LeftBodyCollision = CreateCollision(MarioCollisionOrder::Monster);
		LeftBodyCollision->SetScale({ 10, 45 });
		LeftBodyCollision->SetPosition({ GetPos().x - 20, GetPos().y - 22 });



		//ÀÏ´Ü ±À¹Ù ²¨µÒ
		//LeftBodyCollision->Off();
	}
	{
		RightBodyCollision = CreateCollision(MarioCollisionOrder::Monster);
		RightBodyCollision->SetScale({ 10, 45 });
		RightBodyCollision->SetPosition({ GetPos().x + 20, GetPos().y - 22 });
	}

}


void Goomba::Update(float _DeltaTime)
{
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos();
	ActorPos.x += ImgHalfWidth;

	//<µð¹ö±ë¿ë_¼¾ÅÍ º¸±âÀ§ÇÔ>
	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);



	float4 Dir = float4::Left * MoveSpeed * _DeltaTime;
	//SetMove(Dir);

	std::vector<GameEngineCollision*> PlayerCols = Player::MainPlayer->GetPlayerCollisions();

	std::vector<GameEngineCollision*> Collision;
	if (true == HeadCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect })
		&&
		true == PlayerCols[4]->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision)
		)
	{
		TimerStart = true;

		for (size_t i = 0; i < Collision.size(); i++)
		{
			Monster* FindMonster = Collision[i]->GetOwner<Monster>();

			//GameEngineActor* ColActor = Collision[i]->GetActor();

			SetEffectSound("stomp.wav");
			AnimationRender->ChangeAnimation("Goomba_Death");
			Player::TotalScore += Point;
			HeadCollision->Off();
			LeftBodyCollision->Off();
			RightBodyCollision->Off();

			
			DeathMon = FindMonster;

		}
	}

	if (true == RightBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision)
		|| true == LeftBodyCollision->Collision({ .TargetGroup = static_cast<int>(MarioCollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision)
		)
	{
		for (size_t i = 0; i < Collision.size(); i++)
		{
			Monster* FindMonster = Collision[i]->GetOwner<Monster>();
			HeadCollision->Off();
			LeftBodyCollision->Off();
			RightBodyCollision->Off();


		}


		if (Player::ModeValue == PlayerMode::SUPERMARIO)
		{
			Player::MainPlayer->SetIsShrinkOn();
			SetEffectSound("pipe.wav");

		}
		else
		{
			--Player::Life;

			Player::MainPlayer->ChangeState(PlayerState::DEATH);


			//GameEngineCore::GetInst()->ChangeLevel("EndingLevel");
		}
	}






	if (true == TimerStart)
	{
		WaitTime -= _DeltaTime;
		if (0.0f >= WaitTime)
		{
			DeathMon->Death();
			TimerStart = false;
			WaitTime = 0.3f;
		}
	}



	//<±À¹Ù°¡ Á×´Â Á¶°Ç_with Koopa>
	//¸ÊÀ» ¹þ¾î³µÀ¸¸é Á×¾î¾ß ÇÔ
	//±¸¸Û¿¡ ºüÁö¸é Á×À½
	//ºÒ²É¿¡ ¸Â¾Æµµ Á×À½
	//¸Ó¸®¸¦ ¹âÇôµµ Á×À½(¸¶¸®¿ÀÀÇ ¹Ù´Ú Ãæµ¹Ã¼¿Í ÀÌ ¾ÆÀÌÀÇ ÁÂ¿ì Ãæµ¹Ã¼°¡ ´êÀÌ¸é Á×À½


}




void Goomba::AccGravity(float _DeltaTime)
{
	MoveDir += float4::Down * Gravity * _DeltaTime;
}

void Goomba::InitGravity(bool _IsGround)
{
	if (true == _IsGround)
	{
		MoveDir.y = 0.0f;
	}
}

//ÁÂ¿ìÅ°°¡ ¾È ´­·¶À»¶§ ¸ØÃß°Ô ÇÒ ÀúÇ×
void  Goomba::Friction(float4& _Pos, float _DeltaTime)
{
	_Pos.x *= (FrictionPower * _DeltaTime);
}


bool  Goomba::LiftUp(float4 _Pos)
{
	while (true)
	{
		float4 NextPos = GetPos() + _Pos;

		int Color = Player::MainPlayer->ColImage->GetPixelColor(NextPos, Black);

		if (Black == Color)
		{
			SetMove(float4::Up);							//Underground(Black)-> 1 pixel Up
			continue;
		}

		break;
	}

	//¶¥ÀÎÁö ¾Æ´ÑÁö Ã¼Å©ÇÏ´Â ºÎºÐ
	//Ground: Player°¡ ¼­ÀÖÀ» °÷(Down)º¸´Ù ÇÑ Ä­ ¾Æ·¡ÂÊÀÌ BlackÀÌ¸é ¶¥À¸·Î ÆÇ´Ü_Player´Â BlackÀÌ ¾Æ´Ô
	float4 Down = GetPos() + _Pos;

	if (Black == Player::MainPlayer->ColImage->GetPixelColor(Down + float4::Down, Black))
	{
		return true;
	}
	return false;
}


bool Goomba::CheckWall(float4 _Pos, float4 _Pivot)
{
	float4 CheckPos = GetPos() + _Pos;
	CheckPos += _Pivot;


	if (Black == Player::MainPlayer->ColImage->GetPixelColor(CheckPos, Black))
	{
		return true;
	}

	return false;
}