#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

enum class PlayerState
{
	IDLE,
	MOVE,
	JUMP,
	DEATH,
	FALL,
};

enum class PlayerMode
{
	MARIO,
	SUPERMARIO,
	FIREMARIO,
	STARMARIO
};


// 설명 : Player(Mario)
class Player : public GameEngineActor
{
public:
	static Player* MainPlayer;

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
	int StartFrame = 0;
	int Life = 3;
	
	float PlayTimer = 400.0f;
	float AccTime = 0.0f;
	float MarioHeight = 256.0f;									//Mario 상태가 변하면 값을 바꿔줘야 함
	float MoveSpeed = 200.0f;
	float JumpPower = 0.0f;

	NumberRenderObject NumberSets;

	std::string DirString = "Right_";
	PlayerState StateValue = PlayerState::IDLE;
	PlayerMode ModeValue = PlayerMode::MARIO;
	float4 MoveDir = float4::Zero;

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

	void JumpStart();
	void JumpUpdate(float _Time);
	void JumpEnd();

	void FallStart();
	void FallUpdate(float _Time);
	void FallEnd();

	void DeathStart();
	void DeathUpdate(float _Time);
	void DeathEnd();

	//void Movecalculation(float _DeltaTime);

	//중력가속도
	bool IsGravityOff = false;
	float4 Gravity = float4::Zero;
	void GravitionalAcc(float _DeltaTime);
	inline void GravitionalAccOff()
	{
		IsGravityOff = true;
	}

	GameEngineImage* ColImage = nullptr;

	//움직일 수 있는지...
	bool MoveCheck(float _DeltaTime);

	//void Camera(float _DeltaTime);
};