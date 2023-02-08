#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class PlayerState
{
	IDLE,
	MOVE,
	JUMP,
	DEATH,
	FALL,

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
	int MarioState = 0;											//0:Original 1:Growth 2:Fire 3:Star 

	float AccTime = 0.0f;
	float MarioHeight = 256.0f;									//Mario 상태가 변하면 값을 바꿔줘야 함
	float MoveSpeed = 200.0f;
	float JumpPower = 0.0f;

	std::string DirString = "Right_";
	PlayerState StateValue = PlayerState::IDLE;
	float4 MoveDir = float4::Zero;

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	void DirCheck(const std::string_view& _AnimationName);

	// State
	bool FreeMoveState(float _DeltaTime);

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

	void Movecalculation(float _DeltaTime);


	//void Camera(float _DeltaTime);
};