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

//��Ƽ����Ʈ->�����ڵ� ��ȯ
std::wstring GameEngineString::AnsiToUniCode(const std::string_view& _Text)
{
	//MultiByteToWideChar()�Լ�: ���� ��ȯ && ��ȯ �� ���� ����Ʈ�� �ʿ����� �˷���
	//CP_ACP: ��ȯ�ϱ� ���� ���ڵ� �ɼ� Ÿ�� �� �ϳ�
	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0);

	if (0 == Size)
	{
		MsgAssert("���ڿ� ��ȯ�� �����߽��ϴ�");
		return L"";
	}

	std::wstring Result;
	Result.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size);

	if (0 == Size)
	{
		MsgAssert("���ڿ� ��ȯ�� �����߽��ϴ�");
		return L"";
	}

	return Result;
}

//�����ڵ�->��Ƽ����Ʈ ��ȯ
std::string GameEngineString::UniCodeToAnsi(const std::wstring_view& _Text)
{
	int Size = WideCharToMultiByte(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, nullptr);

	if (0 == Size)
	{
		MsgAssert("���ڿ� ��ȯ�� �����߽��ϴ�");
		return "";
	}

	std::string Result;
	Result.resize(Size);

	Size = WideCharToMultiByte(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

	if (0 == Size)
	{
		MsgAssert("���ڿ� ��ȯ�� �����߽��ϴ�");
		return "";
	}

	return Result;
}

//�����ڵ�->UTF-8 ��ȯ
std::string GameEngineString::UniCodeToUTF8(const std::wstring_view& _Text)
{
	int Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, nullptr);

	if (0 == Size)
	{
		MsgAssert("���ڿ� ��ȯ�� �����߽��ϴ�");
		return "";
	}

	std::string Result;
	Result.resize(Size);

	Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

	if (0 == Size)
	{
		MsgAssert("���ڿ� ��ȯ�� �����߽��ϴ�");
		return "";
	}

	return Result;

}

//��Ƽ����Ʈ->�����ڵ�->UTF-8 ��ȯ
std::string GameEngineString::AnsiToUTF8(const std::string_view& _Text)
{
	std::wstring Unicode = AnsiToUniCode(_Text);
	return UniCodeToUTF8(Unicode.c_str());
}