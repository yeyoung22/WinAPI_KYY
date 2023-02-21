#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "WordRenderObject.h"
#include "SPSymbolRenderObject.h"
#include "NumberRenderObjectEX.h"

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
	float4 NumberScale = { 42, 48 };						//랜더링할 숫자 이미지 크기(사이즈)
	float4 WordScale = { 38, 44 };							//랜더링할 알파벳 이미지 크기(사이즈)
	float4 SymbolScale = { 36, 50 };

	NumberRenderObjectEX TimerSets;
	NumberRenderObjectEX ScoreSets;
	NumberRenderObjectEX NumCoinSets;
	NumberRenderObjectEX WorldLevelSets;
	NumberRenderObjectEX MapLevelSets;

	WordRenderObject W_Time;
	WordRenderObject W_World;
	WordRenderObject W_Nickname;
	std::string_view Words = "";
	
	SPSymbolRenderObject S_Hyphen;
	SPSymbolRenderObject S_Asterisk;
	std::string_view Symbols = "";

	GameEngineRender* AnimationRender = nullptr;
};

