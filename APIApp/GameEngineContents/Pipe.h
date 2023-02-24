#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

// 설명 : 파이프와 관련된 기능
class Pipe : public GameEngineActor
{
public:
	// constrcuter destructer
	Pipe();
	~Pipe();

	// delete Function
	Pipe(const Pipe& _Other) = delete;
	Pipe(Pipe&& _Other) noexcept = delete;
	Pipe& operator=(const Pipe& _Other) = delete;
	Pipe& operator=(Pipe&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	GameEngineSoundPlayer EffectPlayer;
private:
	float MoveSpeed = 230.0f;								//Same As Player MoveSpeed

	GameEngineRender* PipeRender = nullptr;
	GameEngineCollision* GateCollision = nullptr;
};

