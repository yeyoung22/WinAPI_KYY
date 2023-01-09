#pragma once
#include <string_view>
#include <vector>
#include "GameEnginePath.h"

// ���� :
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


	//�ش� ���丮 �� ���� ���� ����
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

