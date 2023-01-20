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

GameEngineActor* GameEngineRender::GetActor()
{
	return GetOwner<GameEngineActor>();
}

void GameEngineRender::SetImage(const std::string_view& _ImageName)
{
	Image = GameEngineResources::GetInst().ImageFind(_ImageName);
}

void GameEngineRender::SetOrder(int _Order)
{
	Order = _Order;
	GetActor()->GetLevel()->PushRender(this);
}

void GameEngineRender::SetFrame(int _Frame)
{
	if (nullptr == Image)
	{
		MsgAssert("이미지가 존재하지 않는 랜더러에 프레임을 지정하려고 했습니다.");
	}

	if (false == Image->IsImageCutting())
	{
		MsgAssert("잘려있는 이미지만 프레임을 지정해줄 수 있습니다.");
	}

	if (false == Image->IsCutIndexValid(_Frame))
	{
		MsgAssert("유요하지 않은 이미지인덱스 입니다.");
	}

	Frame = _Frame;
}

void GameEngineRender::FrameAnimation::Render(float _DeltaTime)
{
	CurrentTime -= _DeltaTime;

	//일정 시간 동안 한 이미지를 보여주다가 시간이 다되면 다음으로 넘어감
	if (CurrentTime <= 0.0f)
	{
		++CurrentIndex;

		if (FrameIndex.size() <= CurrentIndex)
		{
			if (true == Loop)
			{
				CurrentIndex = 0;
			}
			else {
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
		MsgAssert("이미지를 세팅해주지 않았습니다.");
	}

	float4 CameraPos = float4::Zero;

	if (true == IsEffectCamera)
	{
		CameraPos = GetActor()->GetLevel()->GetCameraPos();
	}

	//카메라의 우측이동은 캐릭터 입장에서는 좌측 이동
	float4 RenderPos = GetActor()->GetPos() + Position - CameraPos;

	if (true == Image->IsImageCutting())
	{
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, Frame, RenderPos, Scale, TransColor);
	}
	else
	{
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, RenderPos, Scale, { 0, 0 }, Image->GetImageScale(), TransColor);
	}
}


void GameEngineRender::CreateAnimation(const FrameAnimationParameter& _Paramter)
{
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind(_Paramter.ImageName);

	if (nullptr == Image)
	{
		MsgAssert("존재하지 않는 이미지로 애니메이션을 만들려고 했습니다.");
	}

	if (false == Image->IsImageCutting())
	{
		MsgAssert("잘려있는 이미지만 프레임을 지정해줄 수 있습니다.");
	}

	std::string UpperName = GameEngineString::ToUpper(_Paramter.AnimationName);

	if (Animation.end() != Animation.find(UpperName))
	{
		MsgAssert("이미 존재하는 이름의 애니메이션 입니다." + UpperName);
	}


	FrameAnimation& NewAnimation = Animation[UpperName];

	NewAnimation.Image = Image;

	if (0 != _Paramter.FrameIndex.size())
	{
		NewAnimation.FrameIndex = _Paramter.FrameIndex;
	}
	else
	{
		for (int i = _Paramter.Start; i <= _Paramter.End; ++i)
		{
			NewAnimation.FrameIndex.push_back(i);
		}
	}

	//각 프레임별 시간 계산
	if (0 != _Paramter.FrameTime.size())
	{
		NewAnimation.FrameTime = _Paramter.FrameTime;
	}
	else
	{
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
		MsgAssert("존재하지 않는 애니메이션으로 바꾸려고 했습니다." + UpperName);
	}

	//기존의 애니메이션과 같은 것으로 교환할 경우, 리턴
	if (CurrentAnimation == &Animation[UpperName])
	{
		return;
	}

	CurrentAnimation = &Animation[UpperName];

	CurrentAnimation->CurrentIndex = 0;
	
	CurrentAnimation->CurrentTime = CurrentAnimation->FrameTime[CurrentAnimation->CurrentIndex];
}