#pragma once
#include "GameEngineImage.h"
#include <map>
#include <string>

// ���� : ��� ���ҽ� ����(����, �̹���)
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
	//<�̱���>
	static GameEngineResources Inst;

	// constrcuter destructer
	GameEngineResources();
	~GameEngineResources();

	//�̹����� ���ϸ����� �����ϱ� ����
	//        xxxx.bmp
	std::map<std::string, GameEngineImage*> AllImage;
};

