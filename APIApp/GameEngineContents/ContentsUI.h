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

	//void IsRenderOnSwitch()
	//{
	//	IsRenderOn != IsRenderOn;
	//}



protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	bool IsRenderOn = false;

	float4 NumberScale = { 32, 38 };						//랜더링할 숫자 이미지 크기(사이즈)
	float4 WordScale = { 32, 46 };							//랜더링할 알파벳 이미지 크기(사이즈)
	float4 SymbolScale = { 29, 54 };

	NumberRenderObjectEX TimerSets;
	NumberRenderObjectEX ScoreSets;
	NumberRenderObjectEX NumCoinSets;
	NumberRenderObjectEX WorldLevelSets;
	NumberRenderObjectEX MapLevelSets;
	NumberRenderObjectEX TopScoreSets;

	WordRenderObject W_Time;
	WordRenderObject W_World;
	WordRenderObject W_Nickname;
	std::string_view Words = "";
	
	SPSymbolRenderObject S_Hyphen;
	SPSymbolRenderObject S_Asterisk;
	std::string_view Symbols = "";

	GameEngineRender* AnimationRender = nullptr;
};

