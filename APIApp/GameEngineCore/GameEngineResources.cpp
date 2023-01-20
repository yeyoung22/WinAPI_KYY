#include "GameEngineResources.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineDebug.h>


GameEngineResources GameEngineResources::Inst;

GameEngineResources::GameEngineResources() 
{
}

GameEngineResources::~GameEngineResources() 
{
}

void GameEngineResources::Release()
{
	for (std::pair<std::string, GameEngineImage*> Pair : AllImage)
	{
		if (nullptr == Pair.second)
		{
			continue;
		}
		delete Pair.second;
	}
	AllImage.clear();
}

//이미지
GameEngineImage* GameEngineResources::ImageLoad(const GameEnginePath& _Path)
{
	return ImageLoad(_Path.GetPathToString().c_str(), _Path.GetFileName().c_str());
}

GameEngineImage* GameEngineResources::ImageLoad(const std::string_view& _Path, const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	//AllImage에 UpperName을 가진 이미지 존재 여부 확인
	if (AllImage.end() != AllImage.find(UpperName))
	{
		MsgAssert("이미 로드한 이미지를 또 로드하려고 했습니다." + UpperName);
		return nullptr;
	}

	//같은 이미지가 없는 경우 수행
	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->ImageLoad(_Path);
	//map에 이미지를 넣음
	AllImage.insert(std::make_pair(UpperName, NewImage));

	return NewImage;
}

GameEngineImage* GameEngineResources::ImageFind(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	//find(key값)는 iterator를 가져옴(못 찾으면 .end())
	std::map<std::string, GameEngineImage*>::iterator FindIter = AllImage.find(UpperName);

	if (AllImage.end() == FindIter)
	{
		MsgAssert("로드하지 않은 이미지를 사용하려고 했습니다" + UpperName);
		return nullptr;
	}

	return FindIter->second;
}