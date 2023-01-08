#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� : TitleLevel���� �÷��� ĳ���͸� ������ ��
class OptionLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	OptionLevel();
	~OptionLevel();

	// delete Function
	OptionLevel(const OptionLevel& _Other) = delete;
	OptionLevel(OptionLevel&& _Other) noexcept = delete;
	OptionLevel& operator=(const OptionLevel& _Other) = delete;
	OptionLevel& operator=(OptionLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;

private:

};

