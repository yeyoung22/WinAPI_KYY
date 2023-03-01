#pragma once
#include <GameEngineCore/GameEngineActor.h>
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
	void Update(float _DeltaTime) override;

	GameEngineSoundPlayer EffectPlayer;
	virtual void SetEffectSound(const std::string_view& _String, int _loop = 1, float _BasicVolume = 0.3f) {}

private:



};

