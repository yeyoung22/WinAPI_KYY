#pragma once

// Ό³Έν :
class GameEngineImage
{
public:
	// constrcuter destructer
	GameEngineImage();
	~GameEngineImage();

	// delete Function
	GameEngineImage(const GameEngineImage& _Other) = delete;
	GameEngineImage(GameEngineImage&& _Other) noexcept = delete;
	GameEngineImage& operator=(const GameEngineImage& _Other) = delete;
	GameEngineImage& operator=(GameEngineImage&& _Other) noexcept = delete;

protected:

private:

};

