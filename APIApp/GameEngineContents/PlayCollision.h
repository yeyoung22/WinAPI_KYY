#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "NumberRenderObjectEX.h"

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
	bool TimerStart = false;
	bool PointTimerStart = false;

	float WaitTime = 0.2f;
	float PointSetTimer = 0.5f;

	int White = RGB(255, 0, 255);
	int PoleLength = 480;
	int Point = 0;

	float4 NumberScale = { 16, 32 };

	NumberRenderObjectEX PointSet;

	GameEngineCollision* DeadLineCol1 = nullptr;
	GameEngineCollision* DeadLineCol2 = nullptr;
	GameEngineCollision* DeadLineCol3 = nullptr;

	GameEngineCollision* FlagCollision = nullptr;
	void SetPointSetOff();
	void SetPointSetOn(int _Point);

};

