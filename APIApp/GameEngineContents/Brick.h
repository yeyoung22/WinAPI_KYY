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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:

	float BlockScale = 64.0f;
	float BlockHalfScale = 32.0f;
	float MicroCtrlVert = 5.0f;
	float MicroCtrlHorz = 28.0f;


	float BasicVolume = 0.3f;									//Set Volume
	float WaitTime = 0.2f;
	float Gravity = 200.0f;

	float4 StartPos = float4::Zero;
	float4 MoveDir = float4::Zero;								//옮겨갈 벡터

	float BlockSizeHalf = 32.0f;			//block 64*64


	GameEngineRender* BlockRender = nullptr;
	GameEngineCollision* BlockCollision = nullptr;
	
	//벽면이 될 충돌채
	GameEngineCollision* HeadBlockCollision = nullptr;
	GameEngineCollision* LeftBlockCollision = nullptr;
	GameEngineCollision* RightBlockCollision = nullptr;
	GameEngineCollision* BottomBlockCollision = nullptr;
};

