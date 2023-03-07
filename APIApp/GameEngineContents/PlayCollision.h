#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "NumberRenderObjectEX.h"

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
	bool TimerStart = false;


	float WaitTime = 0.2f;

	int White = RGB(255, 0, 255);
	int PoleLength = 480;
	int Point = 0;

	float4 NumberScale = { 10, 10 };

	NumberRenderObjectEX PointSet;

	GameEngineCollision* DeadLineCol1 = nullptr;
	GameEngineCollision* DeadLineCol2 = nullptr;
	GameEngineCollision* DeadLineCol3 = nullptr;

	GameEngineCollision* FlagCollision = nullptr;

	void SetPointSet(float4 _Pos);
	void SetPointSetOff();
};
