#pragma once
#include <GameEnginePlatform/ThirdParty/FMOD/inc/fmod.hpp>
#include <string_view>


// 설명 : 사운드관련 기능(사운드 파일 역할)
class GameEngineSound
{
public:
	static void SoundUpdate();

public:
	// constrcuter destructer
	GameEngineSound();
	~GameEngineSound();

	// delete Function
	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;


	void SoundLoad(const std::string_view& _Path);
	FMOD::Channel* Play();

	bool EndOfMusic(FMOD::System* _SoundSystem, FMOD_CHANNELCONTROL_CALLBACK_TYPE _CallBackType);

protected:

private:
	FMOD::Sound* FMODSound = nullptr;
};

