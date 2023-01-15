#pragma once
#include <map>
#include <string>
#include <GameEnginePlatform/GameEngineImage.h>

// 설명 : 사운드 이미지 전부 관리
class GameEnginePath;
class GameEngineImage;
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

	
	bool ImageLoad(const GameEnginePath& _Path);

	bool ImageLoad(const std::string_view& _Path, const std::string_view& _Name);

	//이미지 탐색
	GameEngineImage* ImageFind(const std::string_view& _Name);

	//
	void Release();


protected:

private:
	static GameEngineResources Inst;

	// constrcuter destructer
	GameEngineResources();
	~GameEngineResources();

	//        xxxx.bmp
	std::map<std::string, GameEngineImage*> AllImage;
};

