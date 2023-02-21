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

//Number �̹��� ����
void NumberRenderObjectEX::SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor, const std::string_view& _NegativeName)
{
	GameEngineImage* FindNumberImage = GameEngineResources::GetInst().ImageFind(_ImageName);

	if (FindNumberImage->GetImageCuttingCount() != 10)
	{
		MsgAssert("���� �̹����� ������ 10���� �߷� �־�� �մϴ�.");
	}

	if (0 >= _Scale.x || 0 >= _Scale.y)
	{
		MsgAssert("ũ�Ⱑ 0�� ���ڸ� ����� �� �����ϴ�.");
	}

	ImageName = _ImageName;
	NumberScale = _Scale;
	Order = _Order;
	TransColor = _TransColor;
	NegativeName = _NegativeName;
}

//Number �̹����� Render ����
void NumberRenderObjectEX::SetNumberRenders(size_t _Index, int _TransColor, float4 _Pos, const std::string_view& _ImageName, float4 _Scale, bool _CameraEffect, int _Frame)
{
	GameEngineRender* Render = NumberRenders[_Index];

	if (nullptr == Render)
	{
		MsgAssert("���� �������� nullptr �Դϴ�");
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

//�������ϰ� ���� ���� �� ����
void NumberRenderObjectEX::SetValue(int _Value)
{
	GameEngineActor* Actor = GetOwner<GameEngineActor>();
	Value = _Value;

	//GetDigits()�Լ�: �� �ڸ��� ���ڸ� ���� vector ��ȯ
	std::vector<unsigned int> Numbers = GameEngineMath::GetDigits(Value);

	if (nullptr == Actor)
	{
		MsgAssert("���͸��� NumberRenderObject�� �θ� �� �� �ֽ��ϴ�.");
	}

	//NumOfDigits�� SetNumOfDigits()�Լ��� �̸� ����
	if ((-1 != NumOfDigits) && (Numbers.size() > NumOfDigits))				//�ڸ��� ����(Value ���� > ���� ����)
	{
		MsgAssert("NumOfDigits ���� ���� value�� ���� �۽��ϴ�.");
	}

	//digits���̸� value���̷� ����
	if (-1 != NumOfDigits && Value < 0)											//Value: ����, �ڸ��� ����
	{
		ResetDigits();
		MsgAssert("Value�� ������ ���ÿ� Digits���̰� �����Ǿ����ϴ�.");
	}


	Negative = _Value >= 0 ? false : true;										//0�� �ƴ� ���� = true

	//NumOfDigits�� '-1'�� �ƴϸ�, NumberOfdigits: �ڸ���
	//Negative�� true�̸� 1�� ��ȯ
	//Digits�� ������ ���, ����ϰ� ���� �ڸ��� + ��ȣ (+1)�� ����
	//Digits: �� �������ϰ� ���� �ڸ���
	int Digits = (NumOfDigits == -1 ? Numbers.size() : NumOfDigits) + (Negative ? 1 : 0);

	//���� �� ����(������� �ʴ� ������ 0�� ������
	if (true == IsFixed)
	{
		for (size_t i = 0; i < NumOfDigits; i++)
		{
			NumberRenders.push_back(Actor->CreateRender(Order));
		}

	}
	else
	{
		if (NumberRenders.size() < Digits)											//NumberRenders�� �߰��ؾ� �ϴ� ���								//NumberRenders�� �߰��ؾ� �ϴ� ���
		{
			size_t CurRenderSize = NumberRenders.size();

			for (size_t i = 0; i < (Digits - CurRenderSize); ++i)					//������ �ڸ������� ū �ڸ����� ���� �������ϴ� �ܿ�
			{
				NumberRenders.push_back(Actor->CreateRender(Order));				//�ʿ��� ������ŭ ������ �� ����
			}
		}
		else																		//NumberRenders�� ���� �ؾ��ϴ� ���  +)�����Ǵ� ���																// NumberRenders�� ���� �ؾ��ϴ� ���  +)�����Ǵ� ���
		{
			size_t CurRenderSize = NumberRenders.size();

			for (size_t i = 0; i < (CurRenderSize - Digits); ++i)					//������ �ڸ������� ���� �ڸ����� ���ڸ� �������ϴ� ���
			{
				GameEngineRender* LastRender = NumberRenders.back();
				NumberRenders.pop_back();											//������ ������ �̾Ƴ�
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

	//�����̸鼭 ���� ��ȣ ������ nullptr�� ���
	if (true == Negative && nullptr == NegativeRender)
	{
		//Index�� 0�� �ƴ� 1���� ����(0��°�� ��ȣ�� �����ؾ� ��)
		SetNumberRenders(NumRenderIndex++, TransColor, RenderPos, NegativeName, NumberScale, CameraEffect);		//'-'��ȣ ���
		RenderPos.x += NumberScale.x;
	}

	//Digits: �������ϰ� ���� �ڸ���
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

//�� ĭ�� �̵��ؼ� ���� �ڸ��� ���� ���
void NumberRenderObjectEX::SetMove(float4 _RenderPos)
{
	for (size_t i = 0; i < NumberRenders.size(); i++)
	{
		NumberRenders[i]->SetMove(_RenderPos);
	}
}

//���Ĺ�� ����
void NumberRenderObjectEX::SetAlign(Align _Align)
{
	AlignState = _Align;
}

//���� ������ ���� �� �� ���� �Լ� ȣ��
void NumberRenderObjectEX::SetRenderPos(float4 _Pos)
{
	Pos = _Pos;
	SetValue(Value);
}