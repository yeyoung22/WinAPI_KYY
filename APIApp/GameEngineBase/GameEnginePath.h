#pragma once
// c++�� ����Ǵ� ������ ����Ҽ� �ִ� ��� ���ڿ� ���� ó������� ����
#include <filesystem>

// ���� : ��� ���� ���
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

	//���� ��η� �̵�
	void MoveParent();

	//�ڽ��� Ư�� ��γ� Ư�� ������ �ִ� ������ �ڵ� move(���� ���)
	void MoveParentToChildPath(const std::string_view& _String);

	//���� ����
	bool IsExists();
	bool IsExistsToPlusString(const std::string_view& _String);

	//Root���� ����
	bool IsRoot();

	//Path ����
	bool Move(const std::string_view& _Path);
	
protected:

private:
	std::filesystem::path Path;
};

