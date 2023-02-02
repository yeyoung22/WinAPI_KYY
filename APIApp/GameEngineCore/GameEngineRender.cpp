#include "GameEngineRender.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include "GameEngineActor.h"
#include "GameEngineLevel.h"

GameEngineRender::GameEngineRender()
{
}

GameEngineRender::~GameEngineRender()
{
}

void GameEngineRender::SetImage(const std::string_view& _ImageName)
{
	Image = GameEngineResources::GetInst().ImageFind(_ImageName);
	SetScaleToImage();				//SetImage()�ϸ� �ٷ� SetScaleToImage()�� ����
}

//������ �̹����� ũ��� ������ ����
void GameEngineRender::SetScaleToImage()
{
	if (nullptr == Image)
	{
		MsgAssert("�̹����� �������� �ʾҴµ� �̹����� ũ��� �����Ϸ��� �߽��ϴ�.");
	}

	SetScale(Image->GetImageScale());
}


void GameEngineRender::SetOrder(int _Order)
{
	GameEngineObject::SetOrder(_Order);
	GetActor()->GetLevel()->PushRender(this);
}

void GameEngineRender::SetFrame(int _Frame)
{
	if (nullptr == Image)
	{
		MsgAssert("�̹����� �������� �ʴ� �������� �������� �����Ϸ��� �߽��ϴ�.");
	}

	if (false == Image->IsImageCutting())
	{
		MsgAssert("�߷��ִ� �̹����� �������� �������� �� �ֽ��ϴ�.");
	}

	if (false == Image->IsCutIndexValid(_Frame))
	{
		MsgAssert("�������� ���� �̹����ε��� �Դϴ�.");
	}

	Frame = _Frame;
}

bool GameEngineRender::FrameAnimation::IsEnd()
{
	int Value = (static_cast<int>(FrameIndex.size()) - 1);
	return CurrentIndex == Value;
}

void GameEngineRender::FrameAnimation::Render(float _DeltaTime)
{
	//���� �ð� ���� Ư�� �̹����� �����ִٰ� �ð��� �� �Ǹ� �������� �ѱ�
	CurrentTime -= _DeltaTime;

	if (CurrentTime <= 0.0f)
	{
		++CurrentIndex;							//���� �̹����� �ѱ�

		if (FrameIndex.size() <= CurrentIndex)
		{
			if (true == Loop)
			{
				CurrentIndex = 0;
			}
			else {
				//�������� ����
				CurrentIndex = static_cast<int>(FrameIndex.size()) - 1;
			}
		}

		CurrentTime = FrameTime[CurrentIndex];
	}
}


void GameEngineRender::Render(float _DeltaTime)
{

	if (nullptr != CurrentAnimation)
	{
		CurrentAnimation->Render(_DeltaTime);
		Frame = CurrentAnimation->FrameIndex[CurrentAnimation->CurrentIndex];
		Image = CurrentAnimation->Image;
	}

	if (nullptr == Image)
	{
		MsgAssert("�̹����� ���������� �ʾҽ��ϴ�.");
	}

	float4 CameraPos = float4::Zero;

	if (true == IsEffectCamera)
	{
		CameraPos = GetActor()->GetLevel()->GetCameraPos();
	}

	//ī�޶��� �����̵��� ĳ���� ���忡���� ���� �̵�
	float4 RenderPos = GetActorPlusPos() - CameraPos;
	

	if (true == Image->IsImageCutting())
	{
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, Frame, RenderPos, GetScale(), TransColor);
	}
	else
	{
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, RenderPos, GetScale(), { 0, 0 }, Image->GetImageScale(), TransColor);
	}
}

bool GameEngineRender::IsAnimationEnd()
{
	return CurrentAnimation->IsEnd();
}

void GameEngineRender::CreateAnimation(const FrameAnimationParameter& _Paramter)
{
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind(_Paramter.ImageName);

	//����� �̹��� ���翩�� Ȯ��
	if (nullptr == Image)
	{
		MsgAssert("�������� �ʴ� �̹����� �ִϸ��̼��� ������� �߽��ϴ�.");
	}

	//�߷� �ִ� �̹��� ���
	if (false == Image->IsImageCutting())
	{
		MsgAssert("�߷��ִ� �̹����� �������� �������� �� �ֽ��ϴ�.");
	}

	std::string UpperName = GameEngineString::ToUpper(_Paramter.AnimationName);

	//�ִϸ��̼� �̸��� �ߺ� ����
	if (Animation.end() != Animation.find(UpperName))	//�� ã���� end()��ȯ
	{
		MsgAssert("�̹� �����ϴ� �̸��� �ִϸ��̼� �Դϴ�." + UpperName);
	}

	FrameAnimation& NewAnimation = Animation[UpperName];	//�����Ͱ� �ƴϹǷ� map�� new, delete��

	NewAnimation.Image = Image;


	if (0 != _Paramter.FrameIndex.size())
	{
		NewAnimation.FrameIndex = _Paramter.FrameIndex;
	}
	else
	{	
		//���� ������ ������ �ִϸ��̼� ����
		for (int i = _Paramter.Start; i <= _Paramter.End; ++i)
		{
			NewAnimation.FrameIndex.push_back(i);
		}
	}

	if (0 != _Paramter.FrameTime.size())
	{
		//�̹����� ����� ������ �ð�
		NewAnimation.FrameTime = _Paramter.FrameTime;
	}
	else
	{
		//���� ��鸶�� ����Ǵ� �ð��� ����
		for (int i = 0; i < NewAnimation.FrameIndex.size(); ++i)
		{
			NewAnimation.FrameTime.push_back(_Paramter.InterTime);
		}
	}

	NewAnimation.Loop = _Paramter.Loop;
	NewAnimation.Parent = this;
}

void GameEngineRender::ChangeAnimation(const std::string_view& _AnimationName)
{
	std::string UpperName = GameEngineString::ToUpper(_AnimationName);

	if (Animation.end() == Animation.find(UpperName))
	{
		MsgAssert("�������� �ʴ� �ִϸ��̼����� �ٲٷ��� �߽��ϴ�." + UpperName);
	}

	//���� �ִϸ��̼ǰ� ���� ������ ��ȯ�� ���, �ϴ� ����
	if (CurrentAnimation == &Animation[UpperName])
	{
		return;
	}

	CurrentAnimation = &Animation[UpperName];

	CurrentAnimation->CurrentIndex = 0;
	
	CurrentAnimation->CurrentTime = CurrentAnimation->FrameTime[CurrentAnimation->CurrentIndex];
}