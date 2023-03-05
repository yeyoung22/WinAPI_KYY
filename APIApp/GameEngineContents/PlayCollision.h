#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 트리거용 콜리전, 깃발 등 고정된 위치의 충돌체와 관련한 기능
class PlayCollision : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayCollision();
	~PlayCollision();

	// delete Function
	PlayCollision(const PlayCollision& _Other) = delete;
	PlayCollision(PlayCollision&& _Other) noexcept = delete;
	PlayCollision& operator=(const PlayCollision& _Other) = delete;
	PlayCollision& operator=(PlayCollision&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineCollision* DeadLineCol1 = nullptr;
	GameEngineCollision* DeadLineCol2 = nullptr;
	GameEngineCollision* DeadLineCol3 = nullptr;

	GameEngineCollision* FlagCollision = nullptr;
};

