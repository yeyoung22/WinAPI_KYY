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
		MsgAssert("액터만이 WordRenderObject의 부모가 될 수 있습니다.");
	}

	//문자는 한 번 정해지면 길이는 변경 불가
	if (0 < SymbolRenders.size() && SymbolRenders.size() != Symbols.size())
	{
		MsgAssert("한 번 정한 문자의 길이는 변경할 수 없습니다.");
	}

	//문자 길이만큼 랜더 생성
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
			MsgAssert("문자랜더러가 nullptr 입니다");
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
	//첫 번째 문자 랜더하고 그 다음 문자는 오른쪽으로 추가 됨
	for (size_t i = 0; i < SymbolRenders.size(); i++)
	{
		SymbolRenders[i]->SetPosition(_Pos + float4::Right * SymbolRenders[i]->GetScale() * static_cast<const float>(i));
	}
}