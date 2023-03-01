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

	void SetEffectSound(const std::string_view& _String, int _loop = 1, float _BasicVolume = 0.3f) override;

private:
	float BasicVolume = 0.3f;									//Set Volume

	GameEngineRender* BlockRender = nullptr;
	GameEngineCollision* BlockCollision = nullptr;
	GameEngineCollision* BlockWallCollision = nullptr;
};

