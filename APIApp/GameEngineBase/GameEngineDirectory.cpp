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
	//�̹� Root�� ���
	if (true == Path.IsRoot())
	{
		MsgAssert("��Ʈ ���丮�� �θ���丮�� �̵��Ҽ� �����ϴ�.");
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

	std::string Ext = _Ext.data();							//Ȯ���ڴ� �ϴ� ������� ����

	std::vector<GameEngineFile> Files;

	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		if (true == Entry.is_directory())
		{
			//��͸� ����ص� �� ��ȸ
			continue;
		}

		Files.push_back(GameEngineFile(Entry.path()));
	}

	return Files;
}