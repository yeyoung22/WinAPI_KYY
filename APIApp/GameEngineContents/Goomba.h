#pragma once
#include "Monster.h"

// 설명 :
class Goomba : public Monster
{
public:
	// constrcuter destructer
	Goomba();
	~Goomba();

	// delete Function
	Goomba(const Goomba& _Other) = delete;
	Goomba(Goomba&& _Other) noexcept = delete;
	Goomba& operator=(const Goomba& _Other) = delete;
	Goomba& operator=(Goomba&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;


	virtual void AccGravity(float _DeltaTime);
	virtual void InitGravity(bool _IsGround);
	virtual void Friction(float4& _Pos, float _DeltaTime);
	virtual bool LiftUp(float4 _Pos);
	virtual bool CheckWall(float4 _Pivot);

private:
	bool TimerStart = false;
	bool MoveStart = false;

	Monster* DeathMon = nullptr;

	int White = RGB(255, 255, 255);
	int Black = RGB(0, 0, 0);
	int Red = RGB(255, 0, 0);
	int Magenta = RGB(255, 0, 255);
	int Point = 100;

	float Gravity = 200.0f;										//For Decresing JumpPower
	float ImgHalfWidth = 16.0f;									//To be cut PlayerImg's half size Width and Height
	float ImgHalfHeight = 64.0f;

	float WaitTime = 0.3f;

	float TimeSpeed = 2.0f;										//Time Speed Control Constant
	float MoveSpeed = 170.0f;									//Player Speed								
	float LeftSpeed = 7.0f;										//남은 속도

	float FrictionPower = 0.0025f;

	float4 MoveDir = float4::Zero;
	float4 Dir = float4::Left;									//몬스터의 움직이는 방향

	float4 PivotRPos = { ImgHalfWidth - 8, -3 };
	float4 PivotLPos = { -ImgHalfWidth + 8, -3 };

	float4 PivotRPos2 = { ImgHalfWidth - 8, -17 };
	float4 PivotLPos2 = { -ImgHalfWidth + 8, -17 };

	float4 TriggerScale = { 10, 700 };
	float4 TiriggerCtrlPos = { -500, -350 };




	GameEngineCollision* HeadCollision = nullptr;
	GameEngineCollision* RightBodyCollision = nullptr;
	GameEngineCollision* LeftBodyCollision = nullptr;

	GameEngineCollision* TriggerCollision = nullptr;


	GameEngineRender* AnimationRender = nullptr;


};

