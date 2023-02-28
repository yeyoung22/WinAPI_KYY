#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

// 설명 :
class Monster : public GameEngineActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;



protected:
	void Start() override;
	void Update(float _DeltaTime) override;


	GameEngineSoundPlayer EffectPlayer;
private:
	float MoveSpeed = 100.0f;

	GameEngineRender* AnimationRender = nullptr;

	GameEngineCollision* HeadCollision = nullptr;
	GameEngineCollision* RightBodyCollision = nullptr;
	GameEngineCollision* LeftBodyCollision = nullptr;


	//Troopa는 timer필요

	int Point = 100;

	void SetEffectSound(const std::string_view& _String, int _loop = 1, float _BasicVolume = 0.3f);
	
};

