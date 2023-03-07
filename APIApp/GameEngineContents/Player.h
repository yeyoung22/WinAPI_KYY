#pragma once
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
	GROW,
	FALL,
	DEATH,
	ENTERPIPE,
	ENTERLPIPE,
	EXITPIPE,
	FALG,
	GOCASTLE,
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
	static bool InvincibleMode;								//무적상태: 몬스터와 부딪혀도 죽지 않음
	static Player* MainPlayer;
	static PlayerMode ModeValue;							//플레이어의 상태(Mario, SuperMario, FireMario)
	static float PlayTimer;									//Play Timer
	static int TotalScore;									//Get Score
	static int NumOfCoin;									//Number Of Coins
	static int WorldLevel;									//World Level  (World Level - Map Level)
	static int MapLevel;									//Map Level	 (Start at 1 and Finish at 4)
	static int TopScore;
	static int Round;
	static int Life;												//Base Player Life
	static GameEngineImage* ColImage;





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
		IsChanged = true;
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

	void AssignLevels(std::vector<std::vector<int>> _MapNames, int _Round);

	void DirCheck(const std::string_view& _AnimationName);

	void ChangeState(PlayerState _State);

	void SetIsShrinkOn()
	{
		IsShrink = true;
	}

	


	//플레이어의 충돌체 별로 처리할게 다르므로 vector에 넣어서 다른 곳에서 볼 수 있게 해야 함
	//복사본을 넘겨 주겠음
	std::vector<GameEngineCollision*> GetPlayerCollisions()
	{
		std::vector<GameEngineCollision*> ReturnVector;
		ReturnVector.reserve(PlayerCols.size());
	
		for (int i = 0; i < PlayerCols.size(); i++)
		{
			ReturnVector.push_back(PlayerCols[i]);
		}
		return ReturnVector;
	}

	PlayerState GetPlayerState()
	{
		return StateValue;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;


	GameEngineSoundPlayer EffectPlayer;

private:
	bool IsUnderGround = false;
	bool IsChanged = false;
	bool IsLeftBrake = false;
	bool IsGround = false;
	bool IsShrink = false;
	bool IsAlphaOn = false;
	bool ColLongger = false;
	bool ColShorter = false;
	bool FlagDownEnd = false;
	bool IsMoveStop = false;
	bool TimerStop = false;

	int White = RGB(255, 255, 255);
	int Black = RGB(0, 0, 0);
	int Red = RGB(255, 0, 0);
	int Magenta = RGB(255, 0, 255);
	
	int Origin_ColHeight = 60;
	int ColHeight = 124;

	int MaxLoop = 20;

	int StartFrame = 0;

	int Point = 100;

	float HurryUpTime = 100.0f;

	float Gravity = 200.0f;										//For Decresing JumpPower
	float ImgHalfWidth = 32.0f;									//To be cut PlayerImg's half size Width and Height
	float ImgHalfHeight = 64.0f;

	float TimeSpeed = 2.0f;										//Time Speed Control Constant
	//float MoveSpeed = 230.0f;									//Player Speed
	float MoveSpeed = 450.0f;
	float MaxSpeed = 500.f;								//테스트용 값이므로 지워야 함--------------------------------------------------------------------------
	//float MaxSpeed = 250.0f;									
	float FreeSpeed = 1200.0f;
	float LeftSpeed = 7.0f;										//남은 속도
	float PipeEnterSpeed = 68.0f;
	float FlagDownSpeed = 150.0f;

	float JumpPower = -800.0f;
	float SuperJumpPower = -835.0f;
	float BrakePower = 0.0f;
	float FrictionPower = 0.0025f;
	float ShrinkPower = 10.0f;
	
	float BasicVolume = 0.3f;									//Set Volume

	float CameraEndPos = 0.0f;

	float WaitTime = 1.8f;
	float InvincibleTimer = 2.0f;
	float ColMoveValue = 32.0f;


	float4 UnderGroundCameraPos = { 3072.0f, 960.0f };			//Caemra Position at UnderGround
	float4 UnderGroundStart = { 3202.0f , 1154.0f };					//Player Start Position at UnderGround
	float4 UnderGroundEnd = { 10496.0f, 770.0f};

	float4 PivotRPos = { ImgHalfWidth - 8, -3 };
	float4 PivotLPos = { -ImgHalfWidth + 8, -3 };

	float4 PivotRPos2 = { ImgHalfWidth - 8, -17 };
	float4 PivotLPos2 = { -ImgHalfWidth + 8, -17 };

	float4 MarioColScale = { 5, 60 };
	float4 SMarioColScale = { 5, 120 };

	//ColImage 관련 변수 및 함수
	std::string ColMapName;
	
	void ChangeColImage(const std::string& _ColMapName);

	std::string DirString = "Right_";
	std::string RightStr = "Right_";
	std::string LeftStr = "Left_";


	PlayerState StateValue = PlayerState::IDLE;

	float4 MoveDir = float4::Zero;								//옮겨갈 벡터
	float4 OriginPos = { 160, 960 - 128 };


	GameEngineRender* AnimationRender = nullptr;

	std::vector<GameEngineCollision*> PlayerCols;				//Player의 Collision은 넣어줄 벡터

	GameEngineCollision* HeadCollision = nullptr;
	GameEngineCollision* RightBodyCollision = nullptr;
	GameEngineCollision* LeftBodyCollision = nullptr;
	GameEngineCollision* BottomCollision = nullptr;
	GameEngineCollision* SHeadCollision = nullptr;


	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	// State
	bool FreeMoveState(float _DeltaTime);

	
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

	void GrowStart();
	void GrowUpdate(float _Time);
	void GrowEnd();

	void FallStart();
	void FallUpdate(float _Time);
	void FallEnd();


	void DeathStart();
	void DeathUpdate(float _Time);
	void DeathEnd();

	void EnterPipeStart();
	void EnterPipeUpdate(float _Time);
	void EnterPipeEnd();
	
	void EnterLPipeStart();
	void EnterLPipeUpdate(float _Time);
	void EnterLPipeEnd();

	void ExitPipeStart();
	void ExitPipeUpdate(float _Time);
	void ExitPipeEnd();

	void FlagStart();
	void FlagUpdate(float _Time);
	void FlagEnd();

	void GoCastleStart();
	void GoCastleUpdate(float _Time);
	void GoCastleEnd();



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

	//벽인지 확인하는 함수
	bool CheckWall(float4 _Pos, float4 _Pivot = float4::Zero);

	bool CheckAir(float4 _Pos);

	void ShrinkEffect(float _DeltaTime);


	void ActorMove(float _Time)
	{
		SetMove(MoveDir * _Time);							//움직임을 나타냄
	}
	
	void SetIsAlphaSwitch()
	{
		IsAlphaOn = !IsAlphaOn;
	}

	void SetInvincibleSwitch()
	{
		InvincibleMode = !InvincibleMode;
	}


	void SetEffectSound(const std::string_view& _String, int _loop = 1, float _BasicVolume = 0.3f);
};