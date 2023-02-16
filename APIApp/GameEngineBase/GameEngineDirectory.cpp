#include "GameEngineDirectory.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineFile.h"

GameEngineDirectory::GameEngineDirectory() 
{
}

GameEngineDirectory::~GameEngineDirectory() 
{
}

bool GameEngineDirectory::MoveParent()
{
	//이미 Root인 경우
	if (true == Path.IsRoot())
	{
		MsgAssert("루트 디렉토리는 부모디렉토리로 이동할수 없습니다.");
		return false;
	}

	Path.MoveParent();

	return true;
}

void GameEngineDirectory::MoveParentToDirectory(const std::string_view& _String)
{
	std::string MovePath = "\\";
	MovePath += _String;

	Path.MoveParentToChildPath(MovePath.c_str());
}

bool GameEngineDirectory::Move(const std::string_view& _String)
{
	std::string MovePath = "\\";
	MovePath += _String;
	return Path.Move(MovePath.c_str());
}

GameEnginePath GameEngineDirectory::GetPlusFileName(const std::string_view& _String)
{
	std::string PathString = Path.GetPathToString();

	PathString += "\\";
	PathString += _String;

	GameEnginePath NewPath = PathString;

	return NewPath;
}


std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(const std::string_view& _Ext)
{
	std::filesystem::directory_iterator DirIter(Path.Path);

	std::string Ext = _Ext.data();							//확장자는 일단 고려하지 않음

	std::vector<GameEngineFile> Files;

	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		if (true == Entry.is_directory())
		{
			//재귀를 사용해도 다 순회
			continue;
		}

		Files.push_back(GameEngineFile(Entry.path()));
	}

	return Files;
}