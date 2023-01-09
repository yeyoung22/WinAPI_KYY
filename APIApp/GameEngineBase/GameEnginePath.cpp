#include "GameEnginePath.h"
#include <Windows.h>
#include <io.h>
#include <GameEngineBase/GameEngineDebug.h>

GameEnginePath::GameEnginePath()
	: Path(std::filesystem::current_path())			//현재 실행되는 파일 경로
{
}

GameEnginePath::GameEnginePath(std::filesystem::path _Path)
	: Path(_Path)
{
}

GameEnginePath::GameEnginePath(const std::string& _Path)
	: Path(_Path)
{

}

GameEnginePath::GameEnginePath(GameEnginePath&& _Other)
	: Path(_Other.Path)
{

}

GameEnginePath::~GameEnginePath()
{
}

GameEnginePath::GameEnginePath(const GameEnginePath& _Other)
	: Path(_Other.Path)
{

}

std::string GameEnginePath::GetPathToString() const
{
	return Path.string();
}

void GameEnginePath::MoveParent()
{
	Path = Path.parent_path();
}

void GameEnginePath::MoveParentToChildPath(const std::string_view& _String)
{
	//Path가 Root가 아닐경우,
	while (false == IsRoot())
	{
		//없는 경로라면, 이동하지 않음
		if (true == IsExistsToPlusString(_String))
		{
			return;
		}

		MoveParent();
	}

	MsgAssert("이런 경로를 자식으로 가진 부모는 존재하지 않습니다.");
}

bool GameEnginePath::Move(const std::string_view& _Path)
{
	Path += _Path;

	if (false == IsExists())
	{
		MsgAssert("존재하지 않는 경로로 이동하려고 했습니다.");
		return false;
	}

	return true;
}

bool GameEnginePath::IsRoot()
{
	return Path.root_path() == Path;
}

bool GameEnginePath::IsExists()
{	//            directory 경로   읽기/쓰기 특성
	//int _access(const char* Path, int mode);
	//명명된 파일이 없거나 지정된 모드가 없으면 -1 반환
	//mode = 00: 존재만
	return 0 == _access(Path.string().c_str(), 0);
}

bool GameEnginePath::IsExistsToPlusString(const std::string_view& _String)
{
	std::string Str = GetPathToString() + _String.data();
	return 0 == _access(Str.c_str(), 0);
}


//지울거
std::string GameEnginePath::GetPathToStringTmp() const
{
	return TmpPath.string();
}
