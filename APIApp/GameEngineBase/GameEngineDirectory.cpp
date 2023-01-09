#include "GameEngineDirectory.h"
#include <GameEngineBase/GameEngineDebug.h>

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



void GameEngineDirectory::LeaveFile(const std::string_view& _String)
{
	std::string tmpString = Path.GetPathToStringTmp();

	

	size_t tmpNum = tmpString.find(_String.data());
	size_t length = _String.size();
	tmpString.erase(tmpNum, length);
	//tmpString.erase(tmpString.find(_String.data()), tmpString.end());

	int a = 0;
}