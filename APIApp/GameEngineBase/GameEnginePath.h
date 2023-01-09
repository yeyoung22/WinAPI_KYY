#pragma once
// c++이 실행되는 곳에서 사용할수 있는 모든 문자열 관련 처리방식을 지원
#include <filesystem>

// 설명 : 경로 관련 기능
class GameEnginePath
{
public:
	// constrcuter destructer
	GameEnginePath();
	GameEnginePath(std::filesystem::path _Path);
	GameEnginePath(const std::string& _Path);
	~GameEnginePath();

	// delete Function
	GameEnginePath(const GameEnginePath& _Other);
	GameEnginePath(GameEnginePath&& _Other);
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;

	std::string GetPathToString() const;

	//상위 경로로 이동
	void MoveParent();

	//자식중 특정 경로나 특정 파일이 있는 곳까지 자동 move(하위 경로)
	void MoveParentToChildPath(const std::string_view& _String);

	//존재 여부
	bool IsExists();
	bool IsExistsToPlusString(const std::string_view& _String);

	//Root인지 여부
	bool IsRoot();

	//Path 변경
	bool Move(const std::string_view& _Path);
	
protected:

private:
	std::filesystem::path Path;
};

