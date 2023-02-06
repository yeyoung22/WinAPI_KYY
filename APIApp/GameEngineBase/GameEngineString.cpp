#include "GameEngineString.h"

GameEngineString::GameEngineString() 
{
}

GameEngineString::~GameEngineString() 
{
}

std::string GameEngineString::ToUpper(const std::string_view& _Str)
{
	std::string Text = _Str.data();

	//문자열을 하나씩 순회하며 대문자로 치환
	for (size_t i = 0; i < Text.size(); i++)
	{
		Text[i] = toupper(Text[i]);
	}

	return Text;
}

//정수를 문자로 반환
std::string GameEngineString::ToString(int Value)
{
	return std::to_string(Value);
}