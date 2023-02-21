#pragma once
#include "WordRenderObject.h"


// 설명 : 특수 기호를 랜더하는 기능
class SPSymbolRenderObject : public WordRenderObject
{
public:
	// constrcuter destructer
	SPSymbolRenderObject();
	virtual ~SPSymbolRenderObject();									//가상함수 테이블을 위함

	// delete Function
	SPSymbolRenderObject(const SPSymbolRenderObject& _Other) = delete;
	SPSymbolRenderObject(SPSymbolRenderObject&& _Other) noexcept = delete;
	SPSymbolRenderObject& operator=(const SPSymbolRenderObject& _Other) = delete;
	SPSymbolRenderObject& operator=(SPSymbolRenderObject&& _Other) noexcept = delete;

	void SetValue(std::string_view& _Symbol) override;
	void SetCameraEffectOff() override;
	void SetRenderPos(float4 _Pos) override;

protected:

private:
	std::vector<GameEngineRender*> SymbolRenders = std::vector<GameEngineRender*>();
};

