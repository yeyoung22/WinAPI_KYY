#pragma once
#include "Monster.h"

// 설명 :
class Goomba : public Monster
{
public:
	// constrcuter destructer
	Goomba();
	~Goomba();

	// delete Function
	Goomba(const Goomba& _Other) = delete;
	Goomba(Goomba&& _Other) noexcept = delete;
	Goomba& operator=(const Goomba& _Other) = delete;
	Goomba& operator=(Goomba&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void SetEffectSound(const std::string_view& _String, int _loop = 1, float _BasicVolume = 0.3f) override;
private:
	GameEngineCollision* HeadCollision = nullptr;
	GameEngineCollision* RightBodyCollision = nullptr;
	GameEngineCollision* LeftBodyCollision = nullptr;

	float MoveSpeed = 100.0f;

	GameEngineRender* AnimationRender = nullptr;

	//Troopa는 timer필요
	int Point = 100;
};

