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

void NumberRenderObject::SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor)
{
	GameEngineImage* FindNumberImage = GameEngineResources::GetInst().ImageFind(_ImageName);
	
	//1���� �̹����� 0~9�� �־�� �ϸ�, �� �̹����� �߶� ���
	if (FindNumberImage->GetImageCuttingCount() != 10)
	{
		MsgAssert("���� �̹����� ������ 10���� ©���־�� �մϴ�.");
	}

	if (0 >= _Scale.x || 0 >= _Scale.y)
	{
		MsgAssert("ũ�Ⱑ 0���� ���ڸ� ����� �� �����ϴ�.");
	}

	ImageName = _ImageName;
	NumberScale = _Scale;
	Order = _Order;
	TransColor = _TransColor;
}

void NumberRenderObject::SetValue(int _Value)
{
	Value = _Value;

	std::vector<unsigned int> Numbers = GameEngineMath::GetDigits(Value);

	GameEngineActor* Actor = GetOwner<GameEngineActor>();

	if (nullptr == Actor)
	{
		MsgAssert("���͸��� NumberRenderObject�� �θ� �� �� �ֽ��ϴ�.");
	}

	//�ڸ����� �ٲ���� ������ �����ϴ� �ͺ��� �ڸ����� ũ�ٸ�, ������ ��ŭ ���� ����
	if (NumberRenders.size() != Numbers.size() && NumberRenders.size() < Numbers.size())
	{
		size_t CurRenderSize = NumberRenders.size();

		for (size_t i = 0; i < (Numbers.size() - CurRenderSize); i++)
		{
			NumberRenders.push_back(Actor->CreateRender(Order));
		}
	}

	float4 RenderPos;

	for (size_t i = 0; i < NumberRenders.size(); i++)
	{
		GameEngineRender* Render = NumberRenders[i];

		if (nullptr == Render)
		{
			MsgAssert("���ڷ������� nullptr �Դϴ�");
		}

		Render->SetTransColor(TransColor);
		Render->SetPosition(Pos + RenderPos);
		Render->SetImage(ImageName);
		Render->SetScale(NumberScale);
		Render->SetFrame(Numbers[i]);

		RenderPos.x += NumberScale.x;
	}
}