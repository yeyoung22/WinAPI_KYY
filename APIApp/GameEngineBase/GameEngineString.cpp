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

	//���ڿ��� �ϳ��� ��ȸ�ϸ� �빮�ڷ� ġȯ
	for (size_t i = 0; i < Text.size(); i++)
	{
		Text[i] = toupper(Text[i]);
	}

	return Text;
}

//������ ���ڷ� ��ȯ
std::string GameEngineString::ToString(int Value)
{
	return std::to_string(Value);
}