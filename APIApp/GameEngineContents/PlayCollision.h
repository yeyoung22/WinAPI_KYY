#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� : Ʈ���ſ� �ݸ���, ��� �� ������ ��ġ�� �浹ü�� ������ ���
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

