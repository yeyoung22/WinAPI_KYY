#pragma once
#include "STLevel.h"
#include <GameEngineCore/GameEngineResources.h>

// 설명 :
class PlayLevel : public STLevel
{
public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	GameEngineSoundPlayer BGMPlayer;	//SoundPlayer를 받아서 사용(제어)

private:
	void SoundLoad();
	void ImageLoad();

	
};

