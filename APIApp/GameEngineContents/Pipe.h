#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>

enum class PipeType
{
	NONE,
	TOP,
	LEFT,
};

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

	void SetPipeMode(PipeType _Type)
	{
		PipeMode = _Type;
	}

	void SetAllColOff()
	{
		GateCollision->Off();
		ExitCollision->Off();
	}

	void SetGateColOff()
	{
		GateCollision->Off();
	}

	void SetExitColOff()
	{
		ExitCollision->Off();
	}

	void SetPipeRenScale(float4 _Scale);

	void MoveCenterOnPipe(float _DeltaTime);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	GameEngineSoundPlayer EffectPlayer;
private:
	float MoveSpeed = 230.0f;								//Same As Player MoveSpeed

	PipeType PrevPipeMode = PipeType::TOP;
	PipeType PipeMode = PipeType::TOP;


	std::map<PipeType, std::string> AnimNames = std::map<PipeType, std::string>();

	GameEngineRender* PipeRender = nullptr;
	GameEngineCollision* GateCollision = nullptr;
	GameEngineCollision* ExitCollision = nullptr;

	
};

