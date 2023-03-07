#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnums.h"

// Ό³Έν :
class EndingBack : public GameEngineActor
{
public:
	static EndingBack* Ending;
public:
	// constrcuter destructer
	EndingBack();
	~EndingBack();

	// delete Function
	EndingBack(const EndingBack& _Other) = delete;
	EndingBack(EndingBack&& _Other) noexcept = delete;
	EndingBack& operator=(const EndingBack& _Other) = delete;
	EndingBack& operator=(EndingBack&& _Other) noexcept = delete;

	void SetEndingScene(EndingScene _Scene)
	{
		Scene = _Scene;
	}

	EndingScene& GetEndingScene()
	{
		return Scene;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	EndingScene Scene = EndingScene::GameOver;
	std::vector<std::string> SceneName;

	float4 ImgScale = { 900, 136 };

	float WaitTime = 10.0f;

	GameEngineRender* Render  = nullptr;

	GameEngineRender* TxtImgRender1 = nullptr;
	GameEngineRender* TxtImgRender2 = nullptr;
	GameEngineRender* TxtImgRender3 = nullptr;
};