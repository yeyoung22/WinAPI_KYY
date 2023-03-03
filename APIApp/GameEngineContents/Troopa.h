#pragma once
#include "Monster.h"

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


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
	virtual void AccGravity(float _DeltaTime);
	virtual void InitGravity(bool _IsGround);
	virtual void  Friction(float4& _Pos, float _DeltaTime);
	virtual bool LiftUp(float4 _Pos);
	virtual bool CheckWall(float4 _Pos, float4 _Pivot);

private:

	int White = RGB(255, 255, 255);
	int Black = RGB(0, 0, 0);
	int Red = RGB(255, 0, 0);
	int Magenta = RGB(255, 0, 255);
	int Point = 100;

	float WaitTime = 1.5f;

	float Gravity = 200.0f;										//For Decresing JumpPower
	float ImgHalfWidth = 32.0f;									//To be cut PlayerImg's half size Width and Height
	float ImgHalfHeight = 64.0f;

	float TimeSpeed = 2.0f;										//Time Speed Control Constant
	float MoveSpeed = 210.0f;									//Player Speed								
	float LeftSpeed = 7.0f;										//남은 속도

	float FrictionPower = 0.0025f;

	float4 MoveDir = float4::Zero;

	float4 PivotRPos = { ImgHalfWidth - 8, -3 };
	float4 PivotLPos = { -ImgHalfWidth + 8, -3 };

	float4 PivotRPos2 = { ImgHalfWidth - 8, -17 };
	float4 PivotLPos2 = { -ImgHalfWidth + 8, -17 };

	GameEngineCollision* HeadCollision = nullptr;
	GameEngineCollision* RightBodyCollision = nullptr;
	GameEngineCollision* LeftBodyCollision = nullptr;


	GameEngineRender* AnimationRender = nullptr;

};

