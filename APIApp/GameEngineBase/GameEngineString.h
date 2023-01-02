#pragma once

// 설명 :
class GameEngineString
{
public:

	// delete Function
	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;

protected:

private:
	//사용X
	// constrcuter destructer
	GameEngineString();
	~GameEngineString();
};

