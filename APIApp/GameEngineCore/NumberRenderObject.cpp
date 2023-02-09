#include "NumberRenderObject.h"
#include "GameEngineResources.h"
#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineString.h>

NumberRenderObject::NumberRenderObject() 
{
}

NumberRenderObject::~NumberRenderObject() 
{
}

void NumberRenderObject::SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor, const std::string_view& _NegativeName)
{	
	GameEngineImage* FindNumberImage = GameEngineResources::GetInst().ImageFind(_ImageName);
	
	//1장의 이미지에 0~9가 있어야 하며, 이 이미지를 잘라서 사용
	if (FindNumberImage->GetImageCuttingCount() != 10)
	{
		MsgAssert("숫자 이미지는 무조건 10개로 짤려있어야 합니다.");
	}

	if (0 >= _Scale.x || 0 >= _Scale.y)
	{
		MsgAssert("크기가 0으로 숫자를 출력할 수 없습니다.");
	}

	ImageName = _ImageName;
	NumberScale = _Scale;
	Order = _Order;
	TransColor = _TransColor;
	NegativeName = _NegativeName;
}

void NumberRenderObject::SetValue(int _Value)
{
	GameEngineActor* Actor = GetOwner<GameEngineActor>();

	Value = _Value;

	std::vector<unsigned int> Numbers = GameEngineMath::GetDigits(Value);

	if (nullptr == Actor)
	{
		MsgAssert("액터만이 NumberRenderObject의 부모가 될 수 있습니다.");
	}

	//자리수가 바뀌었고 기존에 랜더하던 것보다 자리수가 크다면, 부족한 만큼 랜더 생성
	if (NumberRenders.size() != Numbers.size() && NumberRenders.size() < Numbers.size())
	{
		size_t CurRenderSize = NumberRenders.size();

		for (size_t i = 0; i < (Numbers.size() - CurRenderSize); i++)
		{
			NumberRenders.push_back(Actor->CreateRender(Order));
		}
	}

	float4 RenderPos;

	Negative = _Value > 0 ? false : true;

	if (true == Negative && nullptr == NegativeRender)
	{
		NegativeRender = Actor->CreateRender(Order);
		NegativeRender->SetTransColor(TransColor);
		NegativeRender->SetPosition(Pos + RenderPos);
		NegativeRender->SetImage(NegativeName);
		NegativeRender->SetScale(NumberScale);
		RenderPos.x += NumberScale.x;
	}

	if (nullptr != NegativeRender)
	{
		NegativeRender->SetPosition(Pos + RenderPos);
		RenderPos.x += NumberScale.x;
	}

	for (size_t i = 0; i < NumberRenders.size(); i++)
	{
		GameEngineRender* Render = NumberRenders[i];

		if (nullptr == Render)
		{
			MsgAssert("숫자랜더러가 nullptr 입니다");
		}

		Render->SetTransColor(TransColor);
		Render->SetPosition(Pos + RenderPos);
		Render->SetImage(ImageName);
		Render->SetScale(NumberScale);
		Render->SetFrame(Numbers[i]);

		RenderPos.x += NumberScale.x;
	}

	switch (AlignState)
	{
	case Align::Left:
		break;
	case Align::Right:
		SetMove(float4::Left * static_cast<const float>(GameEngineMath::GetLenth(Value) - 1) * NumberScale.x);
		NegativeRender->SetPosition(float4::Left * static_cast<const float>(GameEngineMath::GetLenth(Value) - 1) * NumberScale.x);
		break;
	case Align::Center:
		SetMove((float4::Left * static_cast<const float>(GameEngineMath::GetLenth(Value) - 1) * NumberScale.x).half());
		NegativeRender->SetPosition((float4::Left * static_cast<const float>(GameEngineMath::GetLenth(Value) - 1) * NumberScale.x).half());
		break;
	default:
		break;
	}
	
	for (size_t i = 0; i < NumberRenders.size(); i++)
	{
		//CameraEffect
		NumberRenders[i]->SetEffectCamera(CameraEffect);
	}

}

void NumberRenderObject::SetMove(float4 _RenderPos)
{
	for (size_t i = 0; i < NumberRenders.size(); i++)
	{
		NumberRenders[i]->SetMove(_RenderPos);
	}
}

//정렬방법 설정
void NumberRenderObject::SetAlign(Align _Align)
{
	AlignState = _Align;
}