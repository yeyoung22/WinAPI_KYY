#include "NumberRenderObjectEX.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>

NumberRenderObjectEX::NumberRenderObjectEX()
{
}

NumberRenderObjectEX::~NumberRenderObjectEX()
{
}

//Number 이미지 세팅
void NumberRenderObjectEX::SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor, const std::string_view& _NegativeName)
{
	GameEngineImage* FindNumberImage = GameEngineResources::GetInst().ImageFind(_ImageName);

	if (FindNumberImage->GetImageCuttingCount() != 10)
	{
		MsgAssert("숫자 이미지는 무조건 10개로 잘려 있어야 합니다.");
	}

	if (0 >= _Scale.x || 0 >= _Scale.y)
	{
		MsgAssert("크기가 0인 숫자를 출력할 수 없습니다.");
	}

	ImageName = _ImageName;
	NumberScale = _Scale;
	Order = _Order;
	TransColor = _TransColor;
	NegativeName = _NegativeName;
}

//Number 이미지의 Render 설정
void NumberRenderObjectEX::SetNumberRenders(size_t _Index, int _TransColor, float4 _Pos, const std::string_view& _ImageName, float4 _Scale, bool _CameraEffect, int _Frame)
{
	GameEngineRender* Render = NumberRenders[_Index];

	if (nullptr == Render)
	{
		MsgAssert("숫자 랜더러가 nullptr 입니다");
	}

	Render->SetTransColor(_TransColor);
	Render->SetPosition(_Pos);
	Render->SetImage(_ImageName);
	Render->SetScale(_Scale);
	Render->SetEffectCamera(_CameraEffect);




	if (-1 != _Frame)
	{
		Render->SetFrame(_Frame);
	}
}

//랜더링하고 싶은 숫자 값 설정
void NumberRenderObjectEX::SetValue(int _Value)
{
	GameEngineActor* Actor = GetOwner<GameEngineActor>();
	Value = _Value;

	//GetDigits()함수: 각 자리의 숫자를 넣은 vector 반환
	std::vector<unsigned int> Numbers = GameEngineMath::GetDigits(Value);

	if (nullptr == Actor)
	{
		MsgAssert("액터만이 NumberRenderObject의 부모가 될 수 있습니다.");
	}

	//NumOfDigits는 SetNumOfDigits()함수로 미리 설정
	if ((-1 != NumOfDigits) && (Numbers.size() > NumOfDigits))				//자릿수 설정(Value 길이 > 설정 길이)
	{
		MsgAssert("NumOfDigits 설정 값이 value값 보다 작습니다.");
	}

	//digits길이를 value길이로 변경
	if (-1 != NumOfDigits && Value < 0)											//Value: 음수, 자릿수 설정
	{
		ResetDigits();
		MsgAssert("Value가 음수인 동시에 Digits길이가 설정되었습니다.");
	}


	Negative = _Value >= 0 ? false : true;										//0이 아닌 음수 = true

	//NumOfDigits가 '-1'이 아니면, NumberOfdigits: 자릿수
	//Negative가 true이면 1을 반환
	//Digits는 음수인 경우, 출력하고 싶은 자릿수 + 부호 (+1)를 해줌
	//Digits: 총 랜더링하고 싶은 자릿수
	int Digits = (NumOfDigits == -1 ? Numbers.size() : NumOfDigits) + (Negative ? 1 : 0);

	//랜더 수 고정(사용하지 않는 랜더는 0을 랜더함
	if (true == IsFixed)
	{
		for (size_t i = 0; i < NumOfDigits; i++)
		{
			NumberRenders.push_back(Actor->CreateRender(Order));
		}

	}
	else
	{
		if (NumberRenders.size() < Digits)											//NumberRenders를 추가해야 하는 경우								//NumberRenders를 추가해야 하는 경우
		{
			size_t CurRenderSize = NumberRenders.size();

			for (size_t i = 0; i < (Digits - CurRenderSize); ++i)					//기존의 자릿수보다 큰 자릿수의 숫자 랜더링하는 겨우
			{
				NumberRenders.push_back(Actor->CreateRender(Order));				//필요한 개수만큼 랜더를 더 생성
			}
		}
		else																		//NumberRenders를 삭제 해야하는 경우  +)유지되는 경우																// NumberRenders를 삭제 해야하는 경우  +)유지되는 경우
		{
			size_t CurRenderSize = NumberRenders.size();

			for (size_t i = 0; i < (CurRenderSize - Digits); ++i)					//기존의 자릿수보다 작은 자릿수의 숫자를 랜더링하는 경우
			{
				GameEngineRender* LastRender = NumberRenders.back();
				NumberRenders.pop_back();											//마지막 랜더를 뽑아냄
				LastRender->Death();
			}
		}
	}

	// Pos
	float4 RenderPos = Pos;
	size_t NumRenderIndex = 0;

	switch (AlignState)
	{
	case Align::Left:
		break;
	case Align::Right:
		RenderPos.x -= (Digits - 1) * NumberScale.x;
		break;
	case Align::Center:
		RenderPos.x -= ((Digits - 1) * NumberScale.x) / 2;
		break;
	default:
		break;
	}

	//음수이면서 음수 부호 랜더가 nullptr인 경우
	if (true == Negative && nullptr == NegativeRender)
	{
		//Index를 0이 아닌 1부터 시작(0번째는 부호를 랜더해야 함)
		SetNumberRenders(NumRenderIndex++, TransColor, RenderPos, NegativeName, NumberScale, CameraEffect);		//'-'부호 고려
		RenderPos.x += NumberScale.x;
	}

	//Digits: 랜더링하고 싶은 자릿수
	for (; NumRenderIndex < Digits - Numbers.size(); ++NumRenderIndex)
	{
		SetNumberRenders(NumRenderIndex, TransColor, RenderPos, ImageName, NumberScale, CameraEffect, 0);
		RenderPos.x += NumberScale.x;
	}

	if (true == IsFixed)
	{
		size_t Diff = Digits - Numbers.size();

		for (int i = 0; i < Diff; i++)
		{
			SetNumberRenders(NumRenderIndex, TransColor, RenderPos, ImageName, NumberScale, CameraEffect, 0);
			++NumRenderIndex;
		}

		for (int i = 0; NumRenderIndex < NumberRenders.size(); ++NumRenderIndex)
		{
			SetNumberRenders(NumRenderIndex, TransColor, RenderPos, ImageName, NumberScale, CameraEffect, Numbers[i++]);
		}

	}
	else
	{
		for (int i = 0; NumRenderIndex < NumberRenders.size(); ++NumRenderIndex)
		{
			SetNumberRenders(NumRenderIndex, TransColor, RenderPos, ImageName, NumberScale, CameraEffect, Numbers[i++]);
			RenderPos.x += NumberScale.x;
		}
	}
	
}

//한 칸식 이동해서 다음 자리에 숫자 출력
void NumberRenderObjectEX::SetMove(float4 _RenderPos)
{
	for (size_t i = 0; i < NumberRenders.size(); i++)
	{
		NumberRenders[i]->SetMove(_RenderPos);
	}
}

//정렬방법 설정
void NumberRenderObjectEX::SetAlign(Align _Align)
{
	AlignState = _Align;
}

//랜더 포지션 설정 및 값 설정 함수 호출
void NumberRenderObjectEX::SetRenderPos(float4 _Pos)
{
	Pos = _Pos;
	SetValue(Value);
}