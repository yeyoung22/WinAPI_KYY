#pragma once
#include <vector>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>
#include <GameEngineCore/GameEngineResources.h>

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
	static bool IsDebugMode;								//true: 디버그 모드(ColMap이 랜더, 충돌체 랜더, 플레이어의 좌표 줄력)
	static Player* MainPlayer;
	static PlayerMode ModeValue;							//플레이어의 상태(Mario, SuperMario, FireMario)
	static float PlayTimer;									//Play Timer
	static int TotalScore;									//Get Score
	static int NumOfCoin;									//Number Of Coins
	static int WorldLevel;									//World Level  (World Level - Map Level)
	static int MapLevel;									//Map Level	 (Start at 1 and Finish at 4)

	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;
	
	void ChangeMode(PlayerMode _Mode)
	{
		ModeValue = _Mode;
	}

	static void DebugModeSwitch()
	{
		IsDebugMode = !IsDebugMode;
	}

	void SetImgHalfWidth(float _Value)
	{
		ImgHalfWidth = _Value;
	}

	void SetImgHalfHeight(float _Value)
	{
		ImgHalfHeight = _Value;
	}
	
	float GetImgHalfWidth()
	{
		return ImgHalfWidth;		
	}

	float GetImgHalfHeight()
	{
		return ImgHalfHeight;
	}

	void Camera(float4 _Pos);

	void AssignLevels(std::vector<std::pair<int, int>> _MapNames, int _Round);


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;


	GameEngineSoundPlayer EffectPlayer;

private:

	bool IsLeftBrake = false;
	bool IsGround = false;

	int White = RGB(255, 255, 255);
	int Black = RGB(0, 0, 0);
	int Red = RGB(255, 0, 0);
	int Magenta = RGB(255, 0, 255);
	int Round = 1;


	int StartFrame = 0;
	int Life = 3;												//Base Player Life
	
	float MarioHeight = 150.0f;									//When MarioMode is changed, the Value should be changed
	float MoveSpeed = 230.0f;									//Player Speed
	float JumpPower = 0.0f;
	float Gravity = 200.0f;										//For Decresing JumpPower
	float FrictionPower = 0.0025f;
	float BrakePower = 0.0f;
	float MaxSpeed = 250.0f;									
	float ImgHalfWidth = 32.0f;									//To be cut PlayerImg's half size Width and Height
	float ImgHalfHeight = 64.0f;
	float FreeSpeed = 1200.0f;
	float LeftSpeed = 7.0f;										//남은 속도

	float CameraEndPos = 0.0f;

	//ColImage 관련 변수 및 함수
	std::string ColMapName;
	GameEngineImage* ColImage = nullptr;
	void ChangeColImage(const std::string& _ColMapName);

	std::string DirString = "Right_";
	PlayerState StateValue = PlayerState::IDLE;
	
	float4 MoveDir = float4::Zero;								//옮겨갈 벡터
	float4 OriginPos = { 160, 960 - 128 };


	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	void DirCheck(const std::string_view& _AnimationName);

	// State
	bool FreeMoveState(float _DeltaTime);

	void ChangeState(PlayerState _State);
	void UpdateState(float _Time);

	//Debug_현재 StateValue를 반환하는 함수
	std::string GetStateName();

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
	void InitGravity(bool _IsGround);

	//Resistant Force
	void Friction(float4& _Pos, float _DeltaTime);

	//Limit Speed Left and Right(_X)
	void LimitSpeed(float4& _Pos);
	
	
	//Lift Player's Position upward
	bool LiftUp(float4 _Pos = float4::Zero);

	//위쪽이 천장인지 확인하는 함수
	bool CheckCeiling(float4 _Pos);

	//오른쪽 왼쪽이 벽인지 확인하는 함수
	bool CheckRightWall(float4 _Pos);
	bool CheckLeftWall(float4 _Pos);

	bool CheckAir(float4 _Pos);

	void ActorMove(float _Time)
	{
		SetMove(MoveDir * _Time);							//움직임을 나타냄
	}

};