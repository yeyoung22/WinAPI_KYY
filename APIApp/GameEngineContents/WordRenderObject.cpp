#include "WordRenderObject.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>

WordRenderObject::WordRenderObject() 
{
}

WordRenderObject::~WordRenderObject() 
{
}

void WordRenderObject::SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor)
{
	GameEngineImage* FindNumberImage = GameEngineResources::GetInst().ImageFind(_ImageName);

	if (0 >= _Scale.x || 0 >= _Scale.y)
	{
		MsgAssert("ũ�Ⱑ 0���� ���ڸ� ����� �� �����ϴ�.");
	}

	ImageName = _ImageName;
	WordScale = _Scale;
	Order = _Order;
	TransColor = _TransColor;
}

void WordRenderObject::SetCameraEffectOff()
{
	for (size_t i = 0; i < WordRenders.size(); i++)
	{
		WordRenders[i]->EffectCameraOff();
	}
}


void WordRenderObject::On()
{
	GameEngineObject::On();
	for (size_t i = 0; i < WordRenders.size(); i++)
	{
		WordRenders[i]->On();
	}
}

void WordRenderObject::Off()
{
	GameEngineObject::Off();
	for (size_t i = 0; i < WordRenders.size(); i++)
	{
		WordRenders[i]->Off();
	}
}

void WordRenderObject::SetValue(std::string_view& _Word)
{
	GameEngineActor* Actor = GetOwner<GameEngineActor>();
	std::string UpperNameWord = GameEngineString::ToUpper(_Word);		//���� ������ �빮�ڷ� ġȯ


	if (nullptr == Actor)
	{
		MsgAssert("���͸��� WordRenderObject�� �θ� �� �� �ֽ��ϴ�.");
	}

	//���ڴ� �� �� �������� ���̴� ���� �Ұ�
	if (0 < WordRenders.size() &&  WordRenders.size() != UpperNameWord.size())
	{
		MsgAssert("�� �� ���� ������ ���̴� ������ �� �����ϴ�.");
	}

	//���� ���̸�ŭ ���� ����
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
			MsgAssert("���ڷ������� nullptr �Դϴ�");
		}

		Render->SetTransColor(TransColor);
		Render->SetPosition(Pos + RenderPos);
		Render->SetImage(ImageName);
		Render->SetScale(WordScale);

		int FrameNumber = 0;
		FrameNumber = UpperNameWord[i] - 'A';
		Render->SetFrame(FrameNumber);

		RenderPos.x += WordScale.x;
	}
}

void WordRenderObject::SetMove(float4 _RenderPos)
{
	for (size_t i = 0; i < WordRenders.size(); i++)
	{
		WordRenders[i]->SetMove(_RenderPos);
	}
}

void WordRenderObject::SetRenderPos(float4 _Pos)
{
	Pos = _Pos;
	//ù ��° ���� �����ϰ� �� ���� ���ڴ� ���������� �߰� ��
	for (size_t i = 0; i < WordRenders.size(); i++)
	{
		WordRenders[i]->SetPosition(_Pos + float4::Right * WordRenders[i]->GetScale() * static_cast<const float>(i));
	}
}