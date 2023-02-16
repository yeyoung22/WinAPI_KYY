#pragma once
#include <string>
#include <string_view>

//문자는 정수 == 문자 매칭방식

//멀티바이트: 1바이트나 2바이트로 표현하는 인코딩 방식(Ansi 표현방식)
//유니코드 : 문자를 2바이트로 표현하는 인코딩 방식
//=> 2바이트 이하 글자표현은 전세계 모든 글자를 2바이트 안에 담을수 없음
 
// 문제해결: UTF 방식 등등


// 설명 : 문자 처리와 관련한 기능
class GameEngineString
{
public:
	//대문자 치환
	static std::string ToUpper(const std::string_view& _Str);
	static std::string ToString(int Value);

	static std::wstring AnsiToUniCode(const std::string_view& _Text);
	static std::string UniCodeToAnsi(const std::wstring_view& _Text);

	static std::string UniCodeToUTF8(const std::wstring_view& _Text);
	static std::string AnsiToUTF8(const std::string_view& _Text);

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

