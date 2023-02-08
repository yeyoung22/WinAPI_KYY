#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class EndingBack : public GameEngineActor
{
public:
	// constrcuter destructer
	EndingBack();
	~EndingBack();

	// delete Function
	EndingBack(const EndingBack& _Other) = delete;
	EndingBack(EndingBack&& _Other) noexcept = delete;
	EndingBack& operator=(const EndingBack& _Other) = delete;
	EndingBack& operator=(EndingBack&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

