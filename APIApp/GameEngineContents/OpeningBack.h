#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class OpeningBack : public GameEngineActor
{
public:
	// constrcuter destructer
	OpeningBack();
	~OpeningBack();

	// delete Function
	OpeningBack(const OpeningBack& _Other) = delete;
	OpeningBack(OpeningBack&& _Other) noexcept = delete;
	OpeningBack& operator=(const OpeningBack& _Other) = delete;
	OpeningBack& operator=(OpeningBack&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

