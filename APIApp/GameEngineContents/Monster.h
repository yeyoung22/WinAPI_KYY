#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
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
	virtual void SetEffectSound(const std::string_view& _String, int _loop = 1, float _BasicVolume = 0.3f);

	virtual void AccGravity(float _DeltaTime){}
	virtual void InitGravity(bool _IsGround) {}
	virtual void  Friction(float4& _Pos, float _DeltaTime) {}
	virtual bool LiftUp(float4 _Pos) { return false; }
	virtual bool CheckWall(float4 _Pivot) { return false; }


	float4 MoveDir = float4::Zero;
	GameEngineSoundPlayer EffectPlayer;
private:

};

