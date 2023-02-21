#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "WordRenderObject.h"
#include "SPSymbolRenderObject.h"
#include "NumberRenderObjectEX.h"

// ���� : UI�� ���õ� ���
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
	float4 NumberScale = { 42, 48 };						//�������� ���� �̹��� ũ��(������)
	float4 WordScale = { 38, 44 };							//�������� ���ĺ� �̹��� ũ��(������)
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

