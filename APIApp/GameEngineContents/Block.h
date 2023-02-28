#pragma once
#include <GameEngineCore/GameEngineActor.h>
//#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>

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

	GameEngineSoundPlayer EffectPlayer;
private:
	float BlockSizeHalf = 32.0f;			//block 64*64

	float4 StartPos = float4::Zero;

	float4 MoveDir = float4::Zero;								//옮겨갈 벡터

	GameEngineRender* BlockRender = nullptr;
	GameEngineCollision* BlockCollision = nullptr;
	GameEngineCollision* BlockWallCollision = nullptr;

	void MoveUp(float _DeltaTime);
	void MoveDown(float _DeltaTime);

	float BasicVolume = 0.3f;									//Set Volume

	void SetEffectSound(const std::string_view& _String, int _loop = 1, float _BasicVolume = 0.3f);

	bool IsUp = false;
	bool IsDown = false;

};

