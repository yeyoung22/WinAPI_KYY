#pragma once
#include "WordRenderObject.h"


// ���� : Ư�� ��ȣ�� �����ϴ� ���
class SPSymbolRenderObject : public WordRenderObject
{
public:
	// constrcuter destructer
	SPSymbolRenderObject();
	virtual ~SPSymbolRenderObject();									//�����Լ� ���̺��� ����

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

