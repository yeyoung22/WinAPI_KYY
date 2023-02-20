#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>
#include "TextRenderObject.h"

// 설명 : UI와 관련된 기능
class ContentsUI : public GameEngineActor
{
public:
	// constrcuter destructer
	ContentsUI();
	~ContentsUI();

	// delete Function
	ContentsUI(const ContentsUI& _Other) = delete;
	ContentsUI(ContentsUI&& _Other) noexcept = delete;
	ContentsUI& operator=(const ContentsUI& _Other) = delete;
	ContentsUI& operator=(ContentsUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	float4 NumberScale = { 50, 56 };						//랜더링할 숫자 이미지 크기(사이즈)
	float4 WordScale = { 44, 50 };							//랜더링할 알파벳 이미지 크기(사이즈)

	NumberRenderObject TimerSets;
	NumberRenderObject ScoreSets;
	NumberRenderObject NumCoinSets;
	NumberRenderObject WorldLevelSets;

	TextRenderObject WTime;
	std::string_view Words = "";
	
};

