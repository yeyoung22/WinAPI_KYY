#include "Player.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"


void Player::ChangeMode(PlayerMode _Mode)
{
	ModeValue = _Mode;
}

//State 변경
void Player::ChangeState(PlayerState _State)
{
	PlayerState NextState = _State;
	PlayerState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case PlayerState::IDLE:
		IdleStart();
		break;
	case PlayerState::MOVE:
		MoveStart();
		break;
	case PlayerState::JUMP:
		JumpStart();
		break;
	case PlayerState::FALL:
		FallStart();
		break;
	case PlayerState::DEATH:
		DeathStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case PlayerState::IDLE:
		IdleEnd();
		break;
	case PlayerState::MOVE:
		MoveEnd();
		break;
	case PlayerState::JUMP:
		JumpEnd();
		break;
	case PlayerState::FALL:
		FallEnd();
		break;
	case PlayerState::DEATH:
		DeathEnd();
		break;
	default:
		break;
	}

}

void Player::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case PlayerState::IDLE:
		IdleUpdate(_Time);
		break;
	case PlayerState::MOVE:
		MoveUpdate(_Time);
		break;
	case PlayerState::JUMP:
		JumpUpdate(_Time);
		break;
	case PlayerState::FALL:
		FallUpdate(_Time);
		break;
	case PlayerState::DEATH:
		DeathUpdate(_Time);
		break;
	default:
		break;
	}

}


//<Idle>
void Player::IdleStart()
{
	if (ModeValue == PlayerMode::SUPERMARIO)											//Growth ver.Mario
	{
		DirCheck("GrowthIdle");
	}
	else
	{
		DirCheck("Idle");
	}
}
void Player::IdleUpdate(float _Time)
{
	if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove"))
	{
		ChangeState(PlayerState::MOVE);
		return; 
	}

	if (GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::JUMP);
		return;
	}
}
void Player::IdleEnd() {

}


//<Move>
void Player::MoveStart()
{
	if (ModeValue == PlayerMode::SUPERMARIO)											//Growth ver.Mario
	{
		DirCheck("GrowthMove");
	}
	else
	{
		DirCheck("Move");
	}
}
void Player::MoveUpdate(float _Time)
{
	//좌우키가 안 눌렀을때 멈추게 할 저항
	//가속도가 있어야 함
	if (
		false == GameEngineInput::IsPress("LeftMove") &&
		false == GameEngineInput::IsPress("RightMove")
		)
	{
		MoveDir.x *= (0.005f * _Time);
		ChangeState(PlayerState::IDLE);
		return;
	}


	/*if (false == GameEngineInput::IsPress("LeftMove") && false == GameEngineInput::IsPress("RightMove"))
{
	MoveDir.x *= (0.005f * _DeltaTime);
}*/

	if ((0 > MoveDir.x )&& (true == GameEngineInput::IsDown("RightMove")))
	{
		MoveDir.x *= (0.005f * _Time);
		if (0 >= MoveDir.x)
		{
			if (ModeValue == PlayerMode::SUPERMARIO)
			{
				DirCheck("GrowthTurn");
			}
			DirCheck("Turn");
			DirCheck("Move");
		}
	}
	else if ((0 < MoveDir.x) && (true == GameEngineInput::IsDown("LeftMove")))
	{
		MoveDir.x *= (0.005f * _Time);

		if (0 >= MoveDir.x)
		{
			if (ModeValue == PlayerMode::SUPERMARIO)
			{
				DirCheck("GrowthTurn");
			}
			DirCheck("Turn");
			DirCheck("Move");
		}
	}


	if (GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::JUMP);
		return;
	}



	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		MoveDir += float4::Left * MoveSpeed;
	}
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		MoveDir += float4::Right * MoveSpeed;
	}

}
void Player::MoveEnd() 
{
}

//Jump
void Player::JumpStart()
{
	JumpPower = 225.0f;													//점프를 하는 순간 큰 힘으로 빠르게 위로 올라가야 함
	if (ModeValue == PlayerMode::SUPERMARIO)
	{
		DirCheck("GrowthJump");
	}
	else
	{
		DirCheck("Jump");
	}
}

void Player::JumpUpdate(float _Time)
{

	MoveDir += float4::Up * JumpPower;

	JumpPower -= 100.0f * _Time;										//서서히 아래로 떨어지게 함

	if (false == GameEngineInput::IsPress("LeftMove") && false == GameEngineInput::IsPress("RightMove"))
	{
		MoveDir.x *= (0.005f * _Time);
	}

	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		MoveDir += float4::Left * MoveSpeed;
	}
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		MoveDir += float4::Right * MoveSpeed;
	}
	
	//<바닥에 닿으면 IDLE로 상태 변경>
	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind("ColWorld1_1.bmp");

	if (nullptr == ColImage)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}


	float4 NextPos = GetPos() + (MoveDir * _Time);						//옮겨 갈 위치

	if (RGB(0, 0, 0) == ColImage->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		if (ModeValue == PlayerMode::SUPERMARIO)
		{
  			DirCheck("GrowthIdle");
		}
		else
		{
			DirCheck("Idle");
		}
		ChangeState(PlayerState::IDLE);									
		return;															//다른 것에 영향을 안 받기 위해 상태를 바꾸면 return
	}

}
void Player::JumpEnd()
{
}


//Fall(떨어지면 Jump모션을 취하며 Y값은 계속 증가)
void Player::FallStart()
{
	if (ModeValue == PlayerMode::SUPERMARIO)
	{
		DirCheck("GrowthJump");
	}
	else
	{
		DirCheck("Jump");
	}
}
void Player::FallUpdate(float _Time)
{
	if (false == GameEngineInput::IsPress("LeftMove") && false == GameEngineInput::IsPress("RightMove"))
	{
		MoveDir.x *= (0.005f * _Time);
	}

	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		MoveDir += float4::Left * MoveSpeed;
	}
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		MoveDir += float4::Right * MoveSpeed;
	}
}
void Player::FallEnd()
{

}


//Death
void Player::DeathStart()
{
	JumpPower = 210.0f;
	AnimationRender->ChangeAnimation("Death");
}
void Player::DeathUpdate(float _Time)
{
	MoveDir += float4::Up * JumpPower;

	JumpPower -= 50.0f * _Time;

	if (false == GameEngineInput::IsPress("LeftMove") && false == GameEngineInput::IsPress("RightMove"))
	{
		MoveDir.x *= (0.005f * _Time);
	}

	AnimationRender->ChangeAnimation("Death");

}
void Player::DeathEnd()
{

}


