#include "SPSymbolRenderObject.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineCore/GameEngineActor.h>


SPSymbolRenderObject::SPSymbolRenderObject() 
{
}

SPSymbolRenderObject::~SPSymbolRenderObject() 
{
}

void SPSymbolRenderObject::SetValue(std::string_view& _Symbol)
{
	GameEngineActor* Actor = GetOwner<GameEngineActor>();
	std::string Symbols = _Symbol.data();


	if (nullptr == Actor)
	{
		MsgAssert("���͸��� WordRenderObject�� �θ� �� �� �ֽ��ϴ�.");
	}

	//���ڴ� �� �� �������� ���̴� ���� �Ұ�
	if (0 < SymbolRenders.size() && SymbolRenders.size() != Symbols.size())
	{
		MsgAssert("�� �� ���� ������ ���̴� ������ �� �����ϴ�.");
	}

	//���� ���̸�ŭ ���� ����
	for (int i = 0; i < Symbols.size(); ++i)
	{
		SymbolRenders.push_back(Actor->CreateRender(Order));
	}

	float4 RenderPos = Pos;

	for (size_t i = 0; i < SymbolRenders.size(); i++)
	{
		GameEngineRender* Render = SymbolRenders[i];

		if (nullptr == Render)
		{
			MsgAssert("���ڷ������� nullptr �Դϴ�");
		}

		Render->SetTransColor(TransColor);
		Render->SetPosition(Pos + RenderPos);
		Render->SetImage(ImageName);
		Render->SetScale(WordScale);

		int FrameNumber = 0;


		if ('*' == Symbols[i])
		{
			FrameNumber = Symbols[i] - '*';
		}
		else if ('?' == Symbols[i])
		{
			FrameNumber = Symbols[i] - '?' + 1;
		}
		else if ('!' == Symbols[i])
		{
			FrameNumber = Symbols[i] - '!' + 2;
		}
		else if (':' == Symbols[i])
		{
			FrameNumber = Symbols[i] - ':' + 3;
		}
		else if ('-' == Symbols[i])
		{
			FrameNumber = Symbols[i] - '-' + 4;
		}
		else if ('.' == Symbols[i])
		{
			FrameNumber = Symbols[i] - '.' + 5;
		}
		else if ('\'' == Symbols[i])
		{
			FrameNumber = Symbols[i] - '\'' + 6;
		}

		
		Render->SetFrame(FrameNumber);

		RenderPos.x += WordScale.x;
	}
}

void SPSymbolRenderObject::SetCameraEffectOff()
{
	for (size_t i = 0; i < SymbolRenders.size(); i++)
	{
		SymbolRenders[i]->EffectCameraOff();
	}
}

void SPSymbolRenderObject::SetRenderPos(float4 _Pos)
{
	Pos = _Pos;
	//ù ��° ���� �����ϰ� �� ���� ���ڴ� ���������� �߰� ��
	for (size_t i = 0; i < SymbolRenders.size(); i++)
	{
		SymbolRenders[i]->SetPosition(_Pos + float4::Right * SymbolRenders[i]->GetScale() * static_cast<const float>(i));
	}
}