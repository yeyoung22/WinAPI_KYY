#pragma once
#include <string>
#include <string_view>

// 설명 :
class GameEngineString
{
public:
	//대문자 치환
	static std::string ToUpper(const std::string_view& _Str);

protected:

private:
	//사용X
	// constrcuter destructer
	GameEngineString();
	~GameEngineString();
	
	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;
};

