#pragma once
#include "Block.h"

// ���� :
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
	float BasicVolume = 0.3f;									//Set Volume

	float Gravity = 200.0f;

	float4 StartPos = float4::Zero;
	float4 MoveDir = float4::Zero;								//�Űܰ� ����

	float BlockSizeHalf = 32.0f;			//block 64*64

	bool IsUp = false;
	bool IsDown = false;


	GameEngineRender* BlockRender = nullptr;
	GameEngineCollision* BlockCollision = nullptr;
	GameEngineCollision* BlockWallCollision = nullptr;


	void MoveUp(float _DeltaTime);
	void MoveDown(float _DeltaTime);

};

