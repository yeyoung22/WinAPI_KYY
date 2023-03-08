#pragma once
#include "Monster.h"
#include "NumberRenderObjectEX.h"

// 설명 :
class Troopa : public Monster
{
public:
	// constrcuter destructer
	Troopa();
	~Troopa();

	// delete Function
	Troopa(const Troopa& _Other) = delete;
	Troopa(Troopa&& _Other) noexcept = delete;
	Troopa& operator=(const Troopa& _Other) = delete;
	Troopa& operator=(Troopa&& _Other) noexcept = delete;

	void SetShellColOn();
	void SetShellColOff();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
	
	void AccGravity(float _DeltaTime)override;
	void InitGravity(bool _IsGround)override;
	bool LiftUp()override;
	bool CheckWall(float4 _Pivot)override;
	bool CheckAir()override;
	void SetDirSwitch()override;

private:
	bool TimerStart = false;
	bool MoveStart = false;
	bool IsGround = false;

	Monster* DeathMon = nullptr;


	int White = RGB(255, 255, 255);
	int Black = RGB(0, 0, 0);
	int Red = RGB(255, 0, 0);
	int Magenta = RGB(255, 0, 255);
	int Point = 100;
	int count = 0;

	float ShellColOffTime = 1.0f;
	float WaitTime = 2.0f;

	float Gravity = 200.0f;										//For Decresing JumpPower
	float ImgHalfWidth = 32.0f;									//To be cut PlayerImg's half size Width and Height
	float ImgHalfHeight = 64.0f;

	float TimeSpeed = 2.0f;										//Time Speed Control Constant
	float MoveSpeed = 140.0f;									//Player Speed								
	float MoveSpeed2 = 80.0f;
	float LeftSpeed = 7.0f;										//남은 속도


	float4 MoveDir = float4::Zero;
	float4 Dir = float4::Left;									//몬스터의 움직이는 방향
	float4 PivotRPos = { ImgHalfWidth - 8, -3 };
	float4 PivotLPos = { -ImgHalfWidth + 8, -3 };
	float4 TriggerScale = { 10, 700 };
	float4 TiriggerCtrlPos = { -500, -350 };
	float4 NumberScale = { 16, 32 };


	std::string DirString = "Left_";

	GameEngineCollision* HeadCollision = nullptr;
	GameEngineCollision* RightBodyCollision = nullptr;
	GameEngineCollision* LeftBodyCollision = nullptr;
	GameEngineCollision* RightShellCollision = nullptr;
	GameEngineCollision* LeftShellCollision = nullptr;
	GameEngineCollision* TriggerCollision = nullptr;

	GameEngineRender* AnimationRender = nullptr;

	MonsterState StateValue = MonsterState::MOVE;

	NumberRenderObjectEX PointSet;

	void DirCheck(const std::string_view& _AnimationName);
	void MonsterMove(float _DeltaTime);
	void IdleUpdate(float _DeltaTime);
	void MoveUpdate(float _DeltaTime);
	void FallUpdate(float _DeltaTime);
	void ShellUpdate(float _DeltaTime);
	void DeathUpdate(float _DeltaTime);
	void SetOnPointSet(int _Point);
	void SetTroopaColOff();
};

