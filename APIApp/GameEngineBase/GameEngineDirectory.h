#pragma once
#include <string_view>
#include <vector>
#include "GameEnginePath.h"

// 설명 :
class GameEngineFile;
class GameEngineDirectory
{
public:
	// constrcuter destructer
	GameEngineDirectory();
	~GameEngineDirectory();

	// delete Function
	GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory(GameEngineDirectory&& _Other) noexcept = delete;
	GameEngineDirectory& operator=(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory&& _Other) noexcept = delete;


	//해당 디렉토리 내 파일 존재 여부
	bool IsFile(const std::string_view& _FileName);

	bool MoveParent();

	void MoveParentToDirectory(const std::string_view& _String);

	bool Move(const std::string_view& _String);

	GameEnginePath GetPlusFileName(const std::string_view& _String);



	// std::vector<GameEngineFile> GetAllFile();



protected:

private:
	//"D:\yeyoung\0_Academy\Portfolio\WinAPI_KYY\APIApp\ContentsResources\Image\";
	GameEnginePath Path;
};

