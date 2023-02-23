#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEnginePlatform/GameEngineImage.h>

// 설명 : Block과 관련한 기능들
class Block : public GameEngineActor
{
public:
	// constrcuter destructer
	Block();
	~Block();

	// delete Function
	Block(const Block& _Other) = delete;
	Block(Block&& _Other) noexcept = delete;
	Block& operator=(const Block& _Other) = delete;
	Block& operator=(Block&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float BlockSizeHalf = 32.0f;			//block 64*64

	float4 StartPos = float4::Zero;

	GameEngineRender* BlockRender = nullptr;
	GameEngineCollision* BlockCollision = nullptr;

	void MoveUp();
	void MoveDown();
};

