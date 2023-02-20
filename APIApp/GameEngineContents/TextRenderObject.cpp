#include "TextRenderObject.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>

TextRenderObject::TextRenderObject() 
{
}

TextRenderObject::~TextRenderObject() 
{
}

void TextRenderObject::SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor)
{
	GameEngineImage* FindNumberImage = GameEngineResources::GetInst().ImageFind(_ImageName);

	if (0 >= _Scale.x || 0 >= _Scale.y)
	{
		MsgAssert("크기가 0으로 문자를 출력할 수 없습니다.");
	}

	ImageName = _ImageName;
	WordScale = _Scale;
	Order = _Order;
	TransColor = _TransColor;
}

void TextRenderObject::SetCameraEffectOff()
{
	for (size_t i = 0; i < WordRenders.size(); i++)
	{
		WordRenders[i]->EffectCameraOff();
	}
}


void TextRenderObject::On()
{
	GameEngineObject::On();
	for (size_t i = 0; i < WordRenders.size(); i++)
	{
		WordRenders[i]->On();
	}
}

void TextRenderObject::Off()
{
	GameEngineObject::Off();
	for (size_t i = 0; i < WordRenders.size(); i++)
	{
		WordRenders[i]->Off();
	}
}

void TextRenderObject::SetValue(std::string_view& _Word)
{
	GameEngineActor* Actor = GetOwner<GameEngineActor>();
	std::string UpperNameWord = GameEngineString::ToUpper(_Word);		//값은 무조건 대문자로 치환


	if (nullptr == Actor)
	{
		MsgAssert("액터만이 TextRenderObject의 부모가 될 수 있습니다.");
	}

	//문자는 한 번 정해지면 길이는 변경 불가
	if (0 < WordRenders.size() &&  WordRenders.size() != UpperNameWord.size())
	{
		MsgAssert("한 번 정한 문자의 길이는 변경할 수 없습니다.");
	}

	//문자 길이만큼 랜더 생성
	for (int i = 0; i < UpperNameWord.size(); ++i)
	{
		WordRenders.push_back(Actor->CreateRender(Order));
	}

	float4 RenderPos = Pos;

	for (size_t i = 0; i < WordRenders.size(); i++)
	{
		GameEngineRender* Render = WordRenders[i];

		if (nullptr == Render)
		{
			MsgAssert("문자랜더러가 nullptr 입니다");
		}

		Render->SetTransColor(TransColor);
		Render->SetPosition(Pos + RenderPos);
		Render->SetImage(ImageName);
		Render->SetScale(WordScale);

		int FrameNumber = 0;

		FrameNumber = UpperNameWord[i] - 'A';
		
		Render->SetFrame(FrameNumber);

		//여기서 이미지랑 문자열이랑 일치하도록 해야 함
		//if (Word[i] == 'A')
		//{
		//	Render->SetFrame(0);
		//}
		//else if (Word[i] == 'B')
		//{
		//	Render->SetFrame(1);
		//}
		//else if (Word[i] == 'C')
		//{
		//	Render->SetFrame(2)
		//}
		//else if (Word[i] == 'D')
		//{

		//}
		//else if (Word[i] == 'E')
		//{

		//}
		//else if (Word[i] == 'F')
		//{

		//}
		//else if (Word[i] == 'G')
		//{

		//}
		//else if (Word[i] == 'H')
		//{

		//}
		//else if (Word[i] == 'I')
		//{

		//}
		//else if (Word[i] == 'J')
		//{

		//}
		//else if (Word[i] == 'K')
		//{

		//}
		//else if (Word[i] == 'L')
		//{

		//}
		//else if (Word[i] == 'M')
		//{

		//}
		//else if (Word[i] == 'N')
		//{

		//}
		//else if (Word[i] == 'O')
		//{

		//}
		//else if (Word[i] == 'P')
		//{

		//}
		//else if (Word[i] == 'Q')
		//{

		//}
		//else if (Word[i] == 'R')
		//{

		//}
		//else if (Word[i] == 'S')
		//{

		//}
		//else if (Word[i] == 'T')
		//{

		//}
		//else if (Word[i] == 'U')
		//{

		//}
		//else if (Word[i] == 'V')
		//{

		//}
		//else if (Word[i] == 'W')
		//{

		//}
		//else if (Word[i] == 'X')
		//{

		//}
		//else if (Word[i] == 'Y')
		//{

		//}
		//else if (Word[i] == 'Z')
		//{

		//}


		RenderPos.x += WordScale.x;
	}
}

void TextRenderObject::SetMove(float4 _RenderPos)
{
	for (size_t i = 0; i < WordRenders.size(); i++)
	{
		WordRenders[i]->SetMove(_RenderPos);
	}
}

void TextRenderObject::SetRenderPos(float4 _Pos)
{
	Pos = _Pos;
	//첫 번째 문자 랜더하고 그 다음 문자는 오른쪽으로 추가 됨
	for (size_t i = 0; i < WordRenders.size(); i++)
	{
		WordRenders[i]->SetPosition(_Pos + float4::Right * WordRenders[i]->GetScale() * static_cast<const float>(i));
	}
}