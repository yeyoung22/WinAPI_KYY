#pragma once
#include <map>
#include <string>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineSound.h>

// 설명 : 사운드, 이미지 전부 관리
//사운드 재생도 GameEngineResource가 해줌

class GameEngineSoundPlayer
{
public:
	GameEngineSoundPlayer() {}
	GameEngineSoundPlayer(FMOD::Channel* _Channel);

	void LoopCount(int _Count);						//반복 횟수
	void Volume(float _Volume);						//볼륨
	void Stop();									//정지
	void PauseOn();									//일시 정지 
	void PauseOff();								//일시 정지 끔

	bool GetPause();

private:
	FMOD::Channel* ControlChannel = nullptr;

};



class GameEnginePath;
class GameEngineImage;
class GameEngineSound;
class GameEngineResources
{
public:
	static GameEngineResources& GetInst()
	{
		return Inst;
	}

public:

	// delete Function
	GameEngineResources(const GameEngineResources& _Other) = delete;
	GameEngineResources(GameEngineResources&& _Other) noexcept = delete;
	GameEngineResources& operator=(const GameEngineResources& _Other) = delete;
	GameEngineResources& operator=(GameEngineResources&& _Other) noexcept = delete;

	//이미지 로드
	GameEngineImage* ImageLoad(const GameEnginePath& _Path);

	GameEngineImage* ImageLoad(const std::string_view& _Path, const std::string_view& _Name);

	//이미지 탐색
	GameEngineImage* ImageFind(const std::string_view& _Name);

	//사운드 로드
	GameEngineSound* SoundLoad(const GameEnginePath& _Path);

	GameEngineSound* SoundLoad(const std::string_view& _Path, const std::string_view& _Name);

	//사운드 찾음
	GameEngineSound* SoundFind(const std::string_view& _Name);

	//사운드 재생
	void SoundPlay(const std::string_view& _Name);

	//사운드 옵션 조절
	GameEngineSoundPlayer SoundPlayToControl(const std::string_view& _Name);




	//메모리 할당 해제
	void Release();


protected:

private:
	static GameEngineResources Inst;

	// constrcuter destructer
	GameEngineResources();
	~GameEngineResources();

	//        xxxx.bmp
	std::map<std::string, GameEngineImage*> AllImage;
	std::map<std::string, GameEngineSound*> AllSound;
};

