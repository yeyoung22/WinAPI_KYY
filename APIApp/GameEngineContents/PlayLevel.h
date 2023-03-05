#pragma once
#include "STLevel.h"
#include <GameEngineCore/GameEngineResources.h>

// 설명 :
class PlayLevel : public STLevel
{
public:
	static std::vector<std::vector<int>> MapNames;
	static PlayLevel* MainPlayLevel;

public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;


	void SetBGMPlayer(const std::string_view& _String, int _loop = 1, float _BasicVolume = 0.1f);
	void SetBGMStop()
	{
		BGMPlayer.Stop();
	}


protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	GameEngineSoundPlayer BGMPlayer;	//SoundPlayer를 받아서 사용(제어)

private:
	int MaxLoop = 20;
	
	float BGMVolume = 0.1f;
	float HurryUpTime = 100;

	float4 CoinRenScale = { 64.0f, 128.0f };
	float4 CoinColScale = { 32.0f, 58.0f };




	void SoundLoad();
	void ImageLoad();
};

