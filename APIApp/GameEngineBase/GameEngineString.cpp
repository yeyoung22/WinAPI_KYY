#include "GameEngineString.h"
#include <Windows.h>
#include "GameEngineDebug.h"


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

//멀티바이트->유니코드 변환
std::wstring GameEngineString::AnsiToUniCode(const std::string_view& _Text)
{
	//MultiByteToWideChar()함수: 직접 변환 && 변환 후 얼마의 바이트가 필요한지 알려줌
	//CP_ACP: 변환하기 위한 인코딩 옵션 타입 중 하나
	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0);

	if (0 == Size)
	{
		MsgAssert("문자열 변환에 실패했습니다");
		return L"";
	}

	std::wstring Result;
	Result.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size);

	if (0 == Size)
	{
		MsgAssert("문자열 변환에 실패했습니다");
		return L"";
	}

	return Result;
}

//유니코드->멀티바이트 변환
std::string GameEngineString::UniCodeToAnsi(const std::wstring_view& _Text)
{
	int Size = WideCharToMultiByte(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, nullptr);

	if (0 == Size)
	{
		MsgAssert("문자열 변환에 실패했습니다");
		return "";
	}

	std::string Result;
	Result.resize(Size);

	Size = WideCharToMultiByte(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

	if (0 == Size)
	{
		MsgAssert("문자열 변환에 실패했습니다");
		return "";
	}

	return Result;
}

//유니코드->UTF-8 변환
std::string GameEngineString::UniCodeToUTF8(const std::wstring_view& _Text)
{
	int Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, nullptr);

	if (0 == Size)
	{
		MsgAssert("문자열 변환에 실패했습니다");
		return "";
	}

	std::string Result;
	Result.resize(Size);

	Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

	if (0 == Size)
	{
		MsgAssert("문자열 변환에 실패했습니다");
		return "";
	}

	return Result;

}

//멀티바이트->유니코드->UTF-8 변환
std::string GameEngineString::AnsiToUTF8(const std::string_view& _Text)
{
	std::wstring Unicode = AnsiToUniCode(_Text);
	return UniCodeToUTF8(Unicode.c_str());
}