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
	case PlayerState::BRAKE:
		BrakeStart();
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
	case PlayerState::BRAKE:
		BrakeEnd();
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
	case PlayerState::BRAKE:
		BrakeUpdate(_Time);
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

	float4 pos = GetPos();

	AccGravity(_Time);
	ActorMove(_Time);

	IsGround = LiftUp();
    InitGravity(IsGround);
	
}
void Player::IdleEnd() {

}



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
	if (
		false == GameEngineInput::IsPress("LeftMove") &&
		false == GameEngineInput::IsPress("RightMove")
		)
	{
		Friction(MoveDir, _Time);
		ChangeState(PlayerState::IDLE);
		return;
	}

	//Brake State로 넘김------------------------------------
	if (
		(0 > MoveDir.x) && 
		(true == GameEngineInput::IsDown("RightMove"))
		)
	{
		IsLeftBrake = true;
		ChangeState(PlayerState::BRAKE);
		return;
	}
	
	if (
		(0 < MoveDir.x) &&
		(true == GameEngineInput::IsDown("LeftMove")) 
		)
	{
		IsLeftBrake = false;
		ChangeState(PlayerState::BRAKE);
		return;
	}

 
	if (GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::JUMP);
		return;
	}

	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		MoveDir += float4::Left * MoveSpeed * _Time;
	}
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		MoveDir += float4::Right * MoveSpeed * _Time;
	}
	

	LimitSpeed(MoveDir);
	AccGravity(_Time);

	SetMove(MoveDir * _Time);
	Camera(MoveDir * _Time);

	IsGround = LiftUp();
	InitGravity(IsGround);
}
void Player::MoveEnd() 
{

}




//Brake State--------------------------------------------------------------------------------------------

void Player::BrakeStart()
{
	BrakePower = 200.0f;
	if (ModeValue == PlayerMode::SUPERMARIO)											//Growth ver.Mario
	{
		DirCheck("GrowthBrake");
	}
	else
	{
		DirCheck("Brake");
	}
}
void Player::BrakeUpdate(float _Time)
{


	LimitSpeed(MoveDir);
	AccGravity(_Time);

	//Brake
	if (true == IsLeftBrake)					//왼쪽으로 가던 중에 오른쪽으로 이동하는 경우
	{
		if (
			0 <= MoveDir.x 
			&& false == GameEngineInput::IsPress("LeftMove")
			&& false == GameEngineInput::IsPress("RightMove")
			)
		{
			ChangeState(PlayerState::IDLE);
			return;
		}

		if (0 <= MoveDir.x && true == GameEngineInput::IsPress("RightMove"))
		{
			ChangeState(PlayerState::MOVE);
			return;
		}
			
		MoveDir += float4::Left * _Time;
		MoveDir += float4::Right * BrakePower *_Time;

		SetMove(MoveDir * _Time);
		

	
	}
	else if (false == IsLeftBrake)					//오른쪽으로 가던 중에 왼쪽으로 이동하는 경우
	{
		if (
			0 >= MoveDir.x
			&& false == GameEngineInput::IsPress("LeftMove")
			&& false == GameEngineInput::IsPress("RightMove")
			)
		{
			ChangeState(PlayerState::IDLE);
			return;
		}

		if (0 >= MoveDir.x && true == GameEngineInput::IsPress("LeftMove"))
		{
			ChangeState(PlayerState::MOVE);
			return;
		}
	


		MoveDir += float4::Right * _Time;
		MoveDir += float4::Left * BrakePower * _Time;

		SetMove(MoveDir * _Time);
	}


	//if (GameEngineInput::IsDown("Jump"))
	//{
	//	ChangeState(PlayerState::JUMP);
	//	return;
	//}


	Camera(MoveDir * _Time);

	IsGround = LiftUp();
	InitGravity(IsGround);
}
void Player::BrakeEnd()
{
}






void Player::JumpStart()
{
	MoveDir.y = -500.0f;
	//JumpPower = 2000.0f;													//점프를 하는 순간 큰 힘으로 빠르게 위로 올라가야 함
	Gravity = 1000.0f;

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
	//MoveDir += float4::Up * JumpPower*_Time;									//큰 힘으로 뛰어오름

  											//서서히 아래로 떨어지게 함


	//if (MarioHeight <= abs(MoveDir.y))
	//{
	//	if (0 > MoveDir.y)
	//	{
	//		MoveDir.y = -MarioHeight;
	//	}
	//	else
	//	{
	//		MoveDir.y = MarioHeight;
	//	}
	//}


	//좌우 방향키가 눌러져 있다면 점프를 해당 방향에 맞게 뜀
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		MoveDir += float4::Left * MoveSpeed * _Time;
	}
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		MoveDir += float4::Right * MoveSpeed * _Time;
	}


	//땅에 닿으면 Idle
	if (true == IsGround && 0 <= MoveDir.y)
	{
		//Friction(MoveDir, _Time);

		if (ModeValue == PlayerMode::SUPERMARIO)
		{
			DirCheck("GrowthIdle");
		}
		else
		{
			DirCheck("Idle");
		}

		ChangeState(PlayerState::IDLE);
		return;
	}


	LimitSpeed(MoveDir);

	SetMove(MoveDir*_Time);
	AccGravity(_Time);

	Camera(MoveDir * _Time);

	IsGround = LiftUp();

	InitGravity(IsGround);
}
void Player::JumpEnd()
{
}


//(떨어지면 Jump모션을 취하며 Y값은 계속 증가)
void Player::FallStart()
{
	/*if (ModeValue == PlayerMode::SUPERMARIO)
	{
		DirCheck("GrowthJump");
	}
	else
	{
		DirCheck("Jump");
	}*/
}
void Player::FallUpdate(float _Time)
{
	//if (true == GameEngineInput::IsPress("LeftMove"))
	//{
	//	MoveDir += float4::Left * MoveSpeed;
	//}
	//else if (true == GameEngineInput::IsPress("RightMove"))
	//{
	//	MoveDir += float4::Right * MoveSpeed;
	//}
}
void Player::FallEnd()
{

}


void Player::DeathStart()
{
	//JumpPower = 210.0f;
	//DecrPower = 50.0f;
	//AnimationRender->ChangeAnimation("Death");
}
void Player::DeathUpdate(float _Time)
{
	/*MoveDir += float4::Up * JumpPower;

	JumpPower -= DecrPower * _Time;

	AnimationRender->ChangeAnimation("Death");*/

}
void Player::DeathEnd()
{

}


