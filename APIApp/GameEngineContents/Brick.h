#pragma once
#include "Block.h"

// 설명 : 벽돌 기능
class Brick : public Block
{
public:
	// constrcuter destructer
	Brick();
	~Brick();

	// delete Function
	Brick(const Brick& _Other) = delete;
	Brick(Brick&& _Other) noexcept = delete;
	Brick& operator=(const Brick& _Other) = delete;
	Brick& operator=(Brick&& _Other) noexcept = delete;

	void SetChipOn();
	void SetChipOff();

	void IsMoveOn()
	{
		IsMove = true;
	}

	bool GetIsChipMoveEnd()
	{
		return IsChipMoveEnd;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:
	bool IsChipMoveEnd = false;
	bool IsMove = false;
	bool IsUpEnd = false;
	bool IsChipMove = false;
	bool IsChipUp = false;

	float BlockScale = 64.0f;
	float BlockHalfScale = 32.0f;
	float MicroCtrlVert = 50.0f;
	float MicroCtrlVert2 = 10.0f;
	float MicroCtrlHorz = 28.0f;
	float UpPower = 16.0f;

	float WaitTime = 1.0f;
	float Gravity = 500.0f;
	float MoveSpeed = 300.0f;
	float ChipSpeed = 60.0f;
	float ChipGravity = 900.0f;
	float JumpPower = 430.0f;


	float4 StartPos = float4::Zero;
	float4 MoveDir = float4::Zero;								//옮겨갈 벡터
	float4 ChipMove = float4::Zero;
	float4 ChipScale = { 64, 64 };

	GameEngineRender* BlockRender = nullptr;
	GameEngineRender* Chip1 = nullptr;
	GameEngineRender* Chip2 = nullptr;
	GameEngineRender* Chip3 = nullptr;
	GameEngineRender* Chip4 = nullptr;



	//벽면이 될 충돌채
	GameEngineCollision* BlockCollision = nullptr;


	void MoveUp(float _DeltaTime);
	void MoveDown(float _DeltaTime);
};

