#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

enum class PlayerState
{
	IDLE,
	MOVE,
	BRAKE,
	JUMP,
	CROUCH,
	ATTACK,
	FALL,
	DEATH,
};

enum class PlayerMode
{
	MARIO,
	SUPERMARIO,
	FIREMARIO,
	STARMARIO
};

union ColorCheck
{
	int Color;

	struct
	{
		char R;
		char G;
		char B;
		char A;
	};
};

// 설명 : Player(Mario)
class Player : public GameEngineActor
{
public:
	static Player* MainPlayer;
	static float PlayTimer;									//Play Timer

	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;
	


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	bool IsLeftBrake = false;
	bool IsGround = false;

	int White = RGB(255, 255, 255);
	int Black = RGB(0, 0, 0);
	int Red = RGB(255, 0, 0);
	int Magenta = RGB(255, 0, 255);


	int StartFrame = 0;
	int Life = 3;												//Base Player Life
	
	float MarioHeight = 150.0f;									//When MarioMode is changed, the Value should be changed
	float MoveSpeed = 230.0f;									//Player Speed
	float JumpPower = 0.0f;
	float Gravity = 200.0f;										//For Decresing JumpPower
	float FrictionPower = 0.0025f;
	float BrakePower = 0.0f;
	float MaxSpeed = 250.0f;									



	std::string ColMapName;

	GameEngineImage* ColImage = nullptr;

	std::string DirString = "Right_";
	PlayerState StateValue = PlayerState::IDLE;
	PlayerMode ModeValue = PlayerMode::MARIO;
	float4 MoveDir = float4::Zero;								//옮겨갈 벡터
	float4 OriginPos = { 160, 960 - 128 };


	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	void DirCheck(const std::string_view& _AnimationName);

	// State
	bool FreeMoveState(float _DeltaTime);

	void ChangeMode(PlayerMode _Mode);
	void ChangeState(PlayerState _State);
	void UpdateState(float _Time);

	//FSM
	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _Time);
	void MoveEnd();

	void BrakeStart();
	void BrakeUpdate(float _Time);
	void BrakeEnd();

	void JumpStart();
	void JumpUpdate(float _Time);
	void JumpEnd();

	void CrouchStart();
	void CrouchUpdate(float _Time);
	void CrouchEnd();

	void AttackStart();
	void AttackUpdate(float _Time);
	void AttackEnd();

	void FallStart();
	void FallUpdate(float _Time);
	void FallEnd();

	void DeathStart();
	void DeathUpdate(float _Time);
	void DeathEnd();

	
	//Garavitional Acceleration
	void AccGravity(float _DeltaTime);
	void InitGravity(bool _IsGround)
	{
		if (true == _IsGround)
		{
			MoveDir.y = 0.0f;
		}
	}

	//Resistant Force
	void Friction(float4& _Pos, float _DeltaTime);

	//Limit Speed Left and Right(_X)
	void LimitSpeed(float4& _Pos);
	
	
	//Lift Player's Position upward
	bool LiftUp(float4 _Pos = float4::Zero);

	bool CheckMove(float4 _Pos, float _DeltaTime);

	
	void ActorMove(float _Time)
	{
		SetMove(MoveDir * _Time);							//움직임을 나타냄
	}

	void Camera(float4 _Pos);
};