#include "Player.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>
#include "ContentsEnums.h"
#include "PlayLevel.h"
#include "Pipe.h"


std::string Player::GetStateName()
{
	switch (StateValue)
	{
	case PlayerState::IDLE:
		return "PlayerState::IDLE";
	case PlayerState::MOVE:
		return "PlayerState::MOVE";
	case PlayerState::BRAKE:
		return "PlayerState::BRAKE";
	case PlayerState::JUMP:
		return "PlayerState::JUMP";
	case PlayerState::CROUCH:
		return "PlayerState::CROUCH";
	case PlayerState::ATTACK:
		return "PlayerState::ATTACK";
	case PlayerState::GROW:
		return "PlayerState::GROW";
	case PlayerState::FALL:
		return "PlayerState::FALL";
	case PlayerState::DEATH:
		return "PlayerState::DEATH";
	case PlayerState::ENTERPIPE:
		return "PlayerState::ENTERPIPE";
	case PlayerState::ENTERLPIPE:
		return "PlayerState::ENTERLPIPE";
	default:
		break;
	}
	return "";
}


//State ����
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
	case PlayerState::CROUCH:
		CrouchStart();
		break;
	case PlayerState::ATTACK:
		AttackStart();
		break;
	case PlayerState::GROW:
		GrowStart();
		break;
	case PlayerState::FALL:
		FallStart();
		break;
	case PlayerState::DEATH:
		DeathStart();
		break;
	case PlayerState::ENTERPIPE:
		EnterPipeStart();
		break;
	case PlayerState::ENTERLPIPE:
		EnterLPipeStart();
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
	case PlayerState::CROUCH:
		CrouchEnd();
		break;
	case PlayerState::ATTACK:
		AttackEnd();
		break;
	case PlayerState::GROW:
		GrowEnd();
		break;
	case PlayerState::FALL:
		FallEnd();
		break;
	case PlayerState::DEATH:
		DeathEnd();
		break;
	case PlayerState::ENTERPIPE:
		EnterPipeEnd();
		break;
	case PlayerState::ENTERLPIPE:
		EnterLPipeEnd();
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
	case PlayerState::CROUCH:
		CrouchUpdate(_Time);
		break;
	case PlayerState::ATTACK:
		AttackUpdate(_Time);
		break;
	case PlayerState::GROW:
		GrowUpdate(_Time);
		break;
	case PlayerState::FALL:
		FallUpdate(_Time);
		break;
	case PlayerState::DEATH:
		DeathUpdate(_Time);
		break;
	case PlayerState::ENTERPIPE:
		EnterPipeUpdate(_Time);
		break;
	case PlayerState::ENTERLPIPE:
		EnterLPipeUpdate(_Time);
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
	else if (ModeValue == PlayerMode::FIREMARIO)
	{
		DirCheck("FireIdle");
	}
	else
	{
		DirCheck("Idle");
	}
}
void Player::IdleUpdate(float _Time)
{
	if (true == IsShrink)
	{
		!IsAlphaOn;
		ShrinkEffect(_Time);
	}

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

	if (ModeValue != PlayerMode::MARIO && GameEngineInput::IsPress("Crouch"))
	{
		ChangeState(PlayerState::CROUCH);
		return;
	}

	if (false == GameEngineInput::IsAnyKey())		//move�ϸ鼭 jump�� �������� �ϴٰ� idle���·� ����
	{
		Friction(MoveDir, _Time);					//x���� ���� ��� �����̴� ���� �ذ�
	}

	

	AccGravity(_Time);
	ActorMove(_Time);


	if (false == CanMove)
	{
		IsGround = LiftUp();
		InitGravity(IsGround);
	}
	
}
void Player::IdleEnd() 
{
	PrevState = PlayerState::IDLE;
}



void Player::MoveStart()
{
	if (ModeValue == PlayerMode::SUPERMARIO)											//Growth ver.Mario
	{
		DirCheck("GrowthMove");
	}
	else if (ModeValue == PlayerMode::FIREMARIO)
	{
		DirCheck("FireMove");
	}
	else
	{
		DirCheck("Move");
	}
}
void Player::MoveUpdate(float _Time)
{
	if (true == IsShrink)
	{
		!IsAlphaOn;
		ShrinkEffect(_Time);
	}

	if (
		false == GameEngineInput::IsPress("LeftMove") &&
		false == GameEngineInput::IsPress("RightMove")
		)
	{
		Friction(MoveDir, _Time);
		ChangeState(PlayerState::IDLE);
		return;
	}

	if (ModeValue != PlayerMode::MARIO && true == GameEngineInput::IsDown("Crouch"))
	{
		Friction(MoveDir, _Time);
		ChangeState(PlayerState::CROUCH);
		return;
	}

	//Brake State�� �ѱ�------------------------------------
	if (
		(0 > MoveDir.x) &&									//�������� ���� �߿� ���������� ��
		(true == GameEngineInput::IsPress("RightMove"))
		)
	{
		IsLeftBrake = true;
		ChangeState(PlayerState::BRAKE);
		return;
	}
	
	if (
		(0 < MoveDir.x) &&									//���������� ���� �߿� �������� ��
		(true == GameEngineInput::IsPress("LeftMove"))
		)
	{
		IsLeftBrake = false;
		ChangeState(PlayerState::BRAKE);
		return;
	}

	//Jump State�� �ѱ�------------------------------------
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
	
	if (true == CheckAir(MoveDir * _Time))
	{
		ChangeState(PlayerState::FALL);
		return;
	}


	LimitSpeed(MoveDir);
	AccGravity(_Time);
	

	if (true ==GameEngineInput::IsPress("LeftMove") && true == CheckWall(MoveDir * _Time, PivotLPos))
	{
		MoveDir.x = 0.0f;

		if (true == GameEngineInput::IsPress("RightMove"))				//�������� ���� �߿� ���������� ��
		{
			if (ModeValue == PlayerMode::SUPERMARIO)											//Growth ver.Mario
			{
				AnimationRender->ChangeAnimation("Right_GrowthMove");
			}
			else if (ModeValue == PlayerMode::FIREMARIO)											//Growth ver.Mario
			{
				AnimationRender->ChangeAnimation("Right_FireMove");
			}
			else
			{
				AnimationRender->ChangeAnimation("Right_Move");
			}
			return;
		}
		
	}
	else if (true == GameEngineInput::IsPress("RightMove") && true == CheckWall(MoveDir * _Time, PivotRPos))
	{
		MoveDir.x = 0.0f;

		if (true == GameEngineInput::IsPress("LeftMove"))				//���������� ���� �߿� �������� ��
		{
			ChangeState(PlayerState::MOVE);
			return;
		}
	}

	SetMove(MoveDir * _Time);
	Camera(MoveDir * _Time);

	IsGround = LiftUp();
	InitGravity(IsGround);
	
}
void Player::MoveEnd() 
{
	PrevState = PlayerState::MOVE;
}


void Player::BrakeStart()
{
	BrakePower = 400.0f;
	if (ModeValue == PlayerMode::SUPERMARIO)											//Growth ver.Mario
	{
		if (true == IsLeftBrake)
		{
			AnimationRender->ChangeAnimation("Right_GrowthBrake");
		}
		else
		{
			AnimationRender->ChangeAnimation("Left_GrowthBrake");
		}
	}
	else if (ModeValue == PlayerMode::FIREMARIO)											//Growth ver.Mario
	{
		if (true == IsLeftBrake)
		{
			AnimationRender->ChangeAnimation("Right_FireBrake");
		}
		else
		{
			AnimationRender->ChangeAnimation("Left_FireBrake");
		}
	}
	else
	{
		if (true == IsLeftBrake)
		{
			AnimationRender->ChangeAnimation("Right_Brake");
		}
		else
		{
			AnimationRender->ChangeAnimation("Left_Brake");
		}
	}
}
void Player::BrakeUpdate(float _Time)
{
	if (true == IsShrink)
	{
		!IsAlphaOn;
		ShrinkEffect(_Time);
	}

	LimitSpeed(MoveDir);
	AccGravity(_Time);

	if (ModeValue != PlayerMode::MARIO && true == GameEngineInput::IsDown("Crouch"))
	{
		Friction(MoveDir, _Time);
		ChangeState(PlayerState::CROUCH);
		return;
	}


	if (0 < MoveDir.x)
	{
		MoveDir.x -= BrakePower * _Time;			//���� �̵�(BrakePower �̵��� �� �ӵ��� ����)
	}
	else {
		MoveDir.x += BrakePower * _Time;			//���� �̵�
	}


	if (true == CheckWall(MoveDir * _Time, PivotLPos))
	{
		MoveDir.x = 0.0f;
		ChangeState(PlayerState::IDLE);
		return;
	}
	else if (true == CheckWall(MoveDir * _Time, PivotRPos))
	{
		MoveDir.x = 0.0f;
		ChangeState(PlayerState::IDLE);
		return;
	}


	SetMove(MoveDir * _Time);
	Camera(MoveDir * _Time);

	IsGround = LiftUp();
	InitGravity(IsGround);
	
	if (LeftSpeed >= abs(MoveDir.x))						//���� �ӵ��� 5.0f�����̸� ���¸� �ٲ�
	{
		if (false == GameEngineInput::IsPress("LeftMove") && false == GameEngineInput::IsPress("RightMove"))
		{
			ChangeState(PlayerState::IDLE);			//�ƹ��͵� �� ������ IDLE
			return;
		}
		else if (true == GameEngineInput::IsDown("Jump"))
		{
			ChangeState(PlayerState::JUMP);
			return;
		}
		else
		{
			ChangeState(PlayerState::MOVE);			//��� ������ �ִ� ��Ȳ ����� Move
			return;
		}
	}

	if (true == CheckAir(MoveDir * _Time))
	{
		ChangeState(PlayerState::FALL);
		return;
	}
	

	IsGround = LiftUp();
	InitGravity(IsGround);
}
void Player::BrakeEnd()
{
	PrevState = PlayerState::BRAKE;
}


void Player::JumpStart()
{
	MoveDir.y = SuperJumpPower;											//������ �ϴ� ���� ū ������ ������ ���� �ö󰡾� ��
	Gravity = 1250.0f;												//�Ʒ��� ����߸��� ��

	if (ModeValue == PlayerMode::SUPERMARIO)
	{
		DirCheck("GrowthJump");
		SetEffectSound("jump_superMario.wav");
	}
	else if (ModeValue == PlayerMode::FIREMARIO)
	{
		DirCheck("FireJump");
		SetEffectSound("jump_superMario.wav");
	}
	else
	{
		MoveDir.y = JumpPower;											//������ �ϴ� ���� ū ������ ������ ���� �ö󰡾� ��
		DirCheck("Jump");
		SetEffectSound("jump.wav");
	}	
}
void Player::JumpUpdate(float _Time)
{
	if (true == IsShrink)
	{
		!IsAlphaOn;
		ShrinkEffect(_Time);
	}

	//�¿� ����Ű�� ������ �ִٸ� ������ �ش� ���⿡ �°� ��
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		MoveDir += float4::Left * MoveSpeed * _Time;
	}
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		MoveDir += float4::Right * MoveSpeed * _Time;
	}


	//���� ������ Idle
	if (true == IsGround && 0 <= MoveDir.y)
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	LimitSpeed(MoveDir);

	//������ �� 2���� �˻��ؼ� �� �� ���ʿ� �ִ� ���� false�̸� x���� 0�� �� �ǰ� ��
	if (true == CheckWall(MoveDir * _Time, PivotLPos) && true == CheckWall(MoveDir*_Time, PivotLPos2))
	{
		MoveDir.x = 0;

		if (true == IsGround && 0 <= MoveDir.y)
		{
			ChangeState(PlayerState::IDLE);
			return;
		}
	}
	else if (true == CheckWall(MoveDir * _Time, PivotRPos) && true == CheckWall(MoveDir * _Time, PivotRPos2))
	{
		MoveDir.x = 0;

		if (true == IsGround && 0 <= MoveDir.y)
		{
			ChangeState(PlayerState::IDLE);
			return;
		}
	}

	SetMove(MoveDir * _Time);
	Camera(MoveDir * _Time);

	
	AccGravity(_Time);
	IsGround = LiftUp();

	InitGravity(IsGround);
}
void Player::JumpEnd()
{
}


void Player::CrouchStart()
{
	if (ModeValue == PlayerMode::FIREMARIO)
	{
		DirCheck("FireCrouch");
	}
	else
	{
		DirCheck("Crouch");
	}
	
}
void Player::CrouchUpdate(float _Time)
{
	if (true == IsShrink)
	{
		!IsAlphaOn;
		ShrinkEffect(_Time);
	}

	if (
		false == GameEngineInput::IsPress("LeftMove") &&
		false == GameEngineInput::IsPress("RightMove") &&
		false == GameEngineInput::IsPress("Crouch")
		)
	{
		//Friction(MoveDir, _Time);
		ChangeState(PlayerState::IDLE);
		return;
	}
	
	LimitSpeed(MoveDir);

	SetMove(MoveDir * _Time);
	AccGravity(_Time);

	Camera(MoveDir * _Time);

	IsGround = LiftUp();

	InitGravity(IsGround);
}
void Player::CrouchEnd()
{
	PrevState = PlayerState::CROUCH;
}


void Player::AttackStart()
{

}
void Player::AttackUpdate(float _Time)
{

}
void Player::AttackEnd()
{
	PrevState = PlayerState::ATTACK;
}

void Player::GrowStart()
{
	if (ModeValue == PlayerMode::MARIO)
	{
		ChangeMode(PlayerMode::SUPERMARIO);
		DirCheck("Bigger");
	}
	else
	{
		IsChanged = false;
	}

	SetEffectSound("growup.wav");
}
void Player::GrowUpdate(float _Time)
{
	if (true == AnimationRender->IsAnimationEnd())
	{
		if (false == GameEngineInput::IsAnyKey())
		{
			Player::MainPlayer->ChangeState(PlayerState::IDLE);
			return;
		}

		if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove"))
		{
			Player::MainPlayer->ChangeState(PlayerState::MOVE);
			return;
		}

		if (GameEngineInput::IsDown("Jump"))
		{
			Player::MainPlayer->ChangeState(PlayerState::JUMP);
			return;
		}

		if (GameEngineInput::IsPress("Crouch"))
		{
			Player::MainPlayer->ChangeState(PlayerState::CROUCH);
			return;
		}
	}

	
}
void Player::GrowEnd()
{
	PrevState = PlayerState::GROW;
}

//(�������� Jump����� ���ϸ� Y���� ��� ����)
void Player::FallStart()
{
	if (ModeValue == PlayerMode::SUPERMARIO)
	{
		DirCheck("GrowthJump");
	}
	else if (ModeValue == PlayerMode::FIREMARIO)
	{
		DirCheck("FireJump");
	}
	else
	{
		DirCheck("Jump");
	}
}
void Player::FallUpdate(float _Time)
{
	/*if (true == IsShrink)
	{
		ShrinkEffect(_Time);
	}*/

	LimitSpeed(MoveDir);
	AccGravity(_Time);
	SetMove(MoveDir * _Time);
	Camera(MoveDir * _Time);

	IsGround = LiftUp();
	InitGravity(IsGround);
	
	//���� ������ Idle
	if (true == IsGround)
	{
		ChangeState(PlayerState::IDLE);
		return;
	}
}
void Player::FallEnd()
{
	PrevState = PlayerState::FALL;
}


void Player::DeathStart()
{
	WaitTime = 3.0f;
	MoveDir.y = -300.0f;
	Gravity = 1000.0f;

	PlayLevel::MainPlayLevel->SetBGMPlayer("Miss.mp3");
	DirCheck("Death");
}	
void Player::DeathUpdate(float _Time)
{
	float DeadLine = GameEngineWindow::GetScreenSize().y;
	float4 PlayerPos = GetPos();

	MoveDir.x = 0.0f;

	SetCanMoveOn();
	AccGravity(_Time);
	
	WaitTime -= _Time;
	SetMove(MoveDir * _Time);


	if (0 >= WaitTime)
	{
		MainPlayer->Death();
		GameEngineCore::GetInst()->ChangeLevel("EndingLevel");
	}


}
void Player::DeathEnd()
{
	PrevState = PlayerState::DEATH;
}

void Player::EnterPipeStart()
{
	PlayLevel::MainPlayLevel->SetBGMPlayer("pipe.wav", 1);
	WaitTime = 0.8f;

	if (ModeValue == PlayerMode::SUPERMARIO)
	{
		AnimationRender->ChangeAnimation("Right_GrowthIdle");
	}
	else if (ModeValue == PlayerMode::FIREMARIO)
	{
		AnimationRender->ChangeAnimation("Right_FireIdle");
	}
	else
	{
		AnimationRender->ChangeAnimation("Right_Idle");
	}
}
void Player::EnterPipeUpdate(float _Time)
{
   	WaitTime -= _Time;
	SetMove(float4::Down* PipeEnterSpeed *_Time);
	

	if (0 >= WaitTime)
	{
		IsUnderGround = true;
		SetCanMoveOff();
		PlayLevel::MainPlayLevel->SetBGMPlayer("Underground.mp3", MaxLoop);

		MoveDir.x = 0.0f;
		SetPos({ UnderGroundStart });
		GetLevel()->SetCameraPos(UnderGroundCameraPos);
		
		ChangeState(PlayerState::FALL);
		return;
	}
}
void Player::EnterPipeEnd()
{
	PrevState = PlayerState::ENTERPIPE;
}


void Player::EnterLPipeStart()
{
	PlayLevel::MainPlayLevel->SetBGMPlayer("pipe.wav", 1);
	WaitTime = 0.8f;

	if (ModeValue == PlayerMode::SUPERMARIO)
	{
		AnimationRender->ChangeAnimation("Right_GrowthIdle");
	}
	else if (ModeValue == PlayerMode::FIREMARIO)
	{
		AnimationRender->ChangeAnimation("Right_FireIdle");
	}
	else
	{
		AnimationRender->ChangeAnimation("Right_Idle");
	}
}
void Player::EnterLPipeUpdate(float _Time)
{
	WaitTime -= _Time;
	SetMove(float4::Right * PipeEnterSpeed * _Time);


	if (0 >= WaitTime)
	{
		IsUnderGround = false;
		PlayLevel::MainPlayLevel->SetBGMPlayer("RunningAbout.mp3", MaxLoop);

		MoveDir.x = 0.0f;
		SetPos({ UnderGroundStart });
		GetLevel()->SetCameraPos({GetPos().x, 0.0f});

		ChangeState(PlayerState::IDLE);
		return;
	}
}
void Player::EnterLPipeEnd() 
{
	PrevState = PlayerState::ENTERLPIPE;
}