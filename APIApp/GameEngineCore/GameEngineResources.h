#pragma once
#include <map>
#include <string>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineSound.h>

// ���� : ����, �̹��� ���� ����
//���� ����� GameEngineResource�� ����

class GameEngineSoundPlayer
{
public:
	GameEngineSoundPlayer() {}
	GameEngineSoundPlayer(FMOD::Channel* _Channel);

	void LoopCount(int _Count);						//�ݺ� Ƚ��
	void Volume(float _Volume);						//����
	void Stop();									//����
	void PauseOn();									//�Ͻ� ���� 
	void PauseOff();								//�Ͻ� ���� ��

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

	//�̹��� �ε�
	GameEngineImage* ImageLoad(const GameEnginePath& _Path);

	GameEngineImage* ImageLoad(const std::string_view& _Path, const std::string_view& _Name);

	//�̹��� Ž��
	GameEngineImage* ImageFind(const std::string_view& _Name);

	//���� �ε�
	GameEngineSound* SoundLoad(const GameEnginePath& _Path);

	GameEngineSound* SoundLoad(const std::string_view& _Path, const std::string_view& _Name);

	//���� ã��
	GameEngineSound* SoundFind(const std::string_view& _Name);

	//���� ���
	void SoundPlay(const std::string_view& _Name);

	//���� �ɼ� ����
	GameEngineSoundPlayer SoundPlayToControl(const std::string_view& _Name);




	//�޸� �Ҵ� ����
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

