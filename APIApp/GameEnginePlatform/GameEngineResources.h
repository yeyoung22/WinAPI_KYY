#pragma once
#include "GameEngineImage.h"
#include <map>
#include <string>

// 설명 : 모든 리소스 관리(사운드, 이미지)
class GameEngineResources
{
public:

	// delete Function
	GameEngineResources(const GameEngineResources& _Other) = delete;
	GameEngineResources(GameEngineResources&& _Other) noexcept = delete;
	GameEngineResources& operator=(const GameEngineResources& _Other) = delete;
	GameEngineResources& operator=(GameEngineResources&& _Other) noexcept = delete;

	GameEngineResources& GetInst()
	{
		return Inst;
	}

protected:
	void ImageLoad(const std::string_view& _Path);

private:
	//<싱글톤>
	static GameEngineResources Inst;

	// constrcuter destructer
	GameEngineResources();
	~GameEngineResources();

	//이미지를 파일명으로 관리하기 위함
	//        xxxx.bmp
	std::map<std::string, GameEngineImage*> AllImage;
};

