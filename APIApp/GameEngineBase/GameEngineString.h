#pragma once
#include <string>
#include <string_view>

//���ڴ� ���� == ���� ��Ī���

//��Ƽ����Ʈ: 1����Ʈ�� 2����Ʈ�� ǥ���ϴ� ���ڵ� ���(Ansi ǥ�����)
//�����ڵ� : ���ڸ� 2����Ʈ�� ǥ���ϴ� ���ڵ� ���
//=> 2����Ʈ ���� ����ǥ���� ������ ��� ���ڸ� 2����Ʈ �ȿ� ������ ����
 
// �����ذ�: UTF ��� ���


// ���� : ���� ó���� ������ ���
class GameEngineString
{
public:
	//�빮�� ġȯ
	static std::string ToUpper(const std::string_view& _Str);
	static std::string ToString(int Value);

	static std::wstring AnsiToUniCode(const std::string_view& _Text);
	static std::string UniCodeToAnsi(const std::wstring_view& _Text);

	static std::string UniCodeToUTF8(const std::wstring_view& _Text);
	static std::string AnsiToUTF8(const std::string_view& _Text);

protected:

private:
	//���X
	// constrcuter destructer
	GameEngineString();
	~GameEngineString();
	
	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;
};

