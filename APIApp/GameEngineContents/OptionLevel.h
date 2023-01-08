#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 설명 : TitleLevel에서 플레이 캐릭터를 변경할 때
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

