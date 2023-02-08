#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class TitleBack : public GameEngineActor
{
public:
	static bool IsMultiMode;

	// constrcuter destructer
	TitleBack();
	~TitleBack();

	// delete Function
	TitleBack(const TitleBack& _Other) = delete;
	TitleBack(TitleBack&& _Other) noexcept = delete;
	TitleBack& operator=(const TitleBack& _Other) = delete;
	TitleBack& operator=(TitleBack&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender* IconRender = nullptr;
};

