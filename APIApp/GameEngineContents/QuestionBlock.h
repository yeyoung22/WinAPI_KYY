#pragma once
#include "Block.h"

// 설명 :
class QuestionBlock :public Block
{
public:
	// constrcuter destructer
	QuestionBlock();
	~QuestionBlock();

	// delete Function
	QuestionBlock(const QuestionBlock& _Other) = delete;
	QuestionBlock(QuestionBlock&& _Other) noexcept = delete;
	QuestionBlock& operator=(const QuestionBlock& _Other) = delete;
	QuestionBlock& operator=(QuestionBlock&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void SetEffectSound(const std::string_view& _String, int _loop = 1, float _BasicVolume = 0.3f) override;

private:
	bool TimerStart = false;

	float BasicVolume = 0.3f;									//Set Volume
	float WaitTime = 0.2f;
	float Gravity = 200.0f;

	float4 StartPos = float4::Zero;
	float4 MoveDir = float4::Zero;								//옮겨갈 벡터

	float BlockSizeHalf = 32.0f;			//block 64*64


	GameEngineRender* BlockRender = nullptr;
	GameEngineCollision* BlockCollision = nullptr;
	GameEngineCollision* BlockWallCollision = nullptr;


	void MoveUp();
	void MoveDown(float _DeltaTime);

};

