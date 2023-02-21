#include "GameEngineRender.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include "GameEngineCore.h"
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

void GameEngineRender::SetImageToScaleToImage(const std::string_view& _ImageName)
{
	Image = GameEngineResources::GetInst().ImageFind(_ImageName);
	SetScaleToImage();
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
	GetActor()->GetLevel()->PushRender(this, _Order);
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

		CurrentTime += FrameTime[CurrentIndex];
	}
}


void GameEngineRender::SetText(const std::string_view& _Text, const int _TextHeight, const std::string_view& _TextType, const TextAlign _TextAlign, const COLORREF _TextColor)
{
	RenderText = _Text;
	TextHeight = _TextHeight;
	TextType = _TextType;
	Align = _TextAlign;
	TextColor = _TextColor;
}

void GameEngineRender::Render(float _DeltaTime)
{
	if (RenderText != "")
	{
		TextRender(_DeltaTime);	
	}
	else
	{
		ImageRender(_DeltaTime);
	}
}

//�ؽ�Ʈ�� ������
void GameEngineRender::TextRender(float _DeltaTime)
{

	float4 CameraPos = float4::Zero;

	if (true == IsEffectCamera)
	{
		CameraPos = GetActor()->GetLevel()->GetCameraPos();
	}

	float4 RenderPos = GetActorPlusPos() - CameraPos;

	HDC hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	HFONT hFont, OldFont;
	LOGFONTA lf;
	lf.lfHeight = TextHeight;
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = 0;
	lf.lfItalic = 0;
	lf.lfUnderline = 0;
	lf.lfStrikeOut = 0;
	lf.lfCharSet = HANGEUL_CHARSET;
	lf.lfOutPrecision = 0;
	lf.lfClipPrecision = 0;
	lf.lfQuality = 0;
	lf.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
	lstrcpy(lf.lfFaceName, TEXT(TextType.c_str()));
	hFont = CreateFontIndirect(&lf);
	OldFont = static_cast<HFONT>(SelectObject(hdc, hFont));

	//SetTextAlign(hdc, static_cast<UINT>(Align));
	SetTextColor(hdc, TextColor);
	SetBkMode(hdc, TRANSPARENT);

	RECT Rect;
	Rect.left = RenderPos.ix();
	Rect.top = RenderPos.iy();
	Rect.right = RenderPos.ix() + TextBoxScale.ix();
	Rect.bottom = RenderPos.iy() + TextBoxScale.iy();


	if (GameEngineCore::GetInst()->IsDebug())
	{
		HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
		HBRUSH myBrush = static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
		HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(DoubleDC, myBrush));
		HPEN myPen = CreatePen(PS_DASH, 0, RGB(0, 0, 0));
		HPEN oldPen = static_cast<HPEN>(SelectObject(DoubleDC, myPen));
		Rectangle(GameEngineWindow::GetDoubleBufferImage()->GetImageDC(), Rect.left, Rect.top, Rect.right, Rect.bottom);

		SelectObject(DoubleDC, oldBrush);
		DeleteObject(myBrush);
		SelectObject(DoubleDC, oldPen);
		DeleteObject(myPen);
	}

	DrawTextA(GameEngineWindow::GetDoubleBufferImage()->GetImageDC(), RenderText.c_str(), static_cast<int>(RenderText.size()), &Rect, static_cast<UINT>(Align));

	//TextOutA(GameEngineWindow::GetDoubleBufferImage()->GetImageDC(), RenderPos.ix(), RenderPos.iy(), RenderText.c_str(), static_cast<int>(RenderText.size()));

	SelectObject(hdc, OldFont);
	DeleteObject(hFont);

	return;
}

//�̹����� ������
void GameEngineRender::ImageRender(float _DeltaTime)
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

	float4 RenderPos = GetActorPlusPos() - CameraPos;

	if (true == Image->IsImageCutting())
	{
		if (255 == Alpha)
		{
			GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, Frame, RenderPos, GetScale(), TransColor);
		}
		else if (255 > Alpha)
		{
			GameEngineWindow::GetDoubleBufferImage()->AlphaCopy(Image, Frame, RenderPos, GetScale(), Alpha);
		}
	}
	else
	{
		if (255 == Alpha)
		{
			GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, RenderPos, GetScale(), { 0, 0 }, Image->GetImageScale(), TransColor);
		}
		else if (255 > Alpha)
		{
			GameEngineWindow::GetDoubleBufferImage()->AlphaCopy(Image, RenderPos, GetScale(), { 0, 0 }, Image->GetImageScale(), Alpha);
		}
		
	}
}

bool GameEngineRender::IsAnimationEnd()
{
	return CurrentAnimation->IsEnd();
}

void GameEngineRender::CreateAnimation(const FrameAnimationParameter& _Parameter)
{
	//�ִϸ��̼��� ����� ���� �̹��� ����
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind(_Parameter.ImageName);

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

	std::string UpperName = GameEngineString::ToUpper(_Parameter.AnimationName);

	//�ִϸ��̼� �̸��� �ߺ� ����
	if (Animation.end() != Animation.find(UpperName))	//�� ã���� end()��ȯ
	{
		MsgAssert("�̹� �����ϴ� �̸��� �ִϸ��̼� �Դϴ�." + UpperName);
	}

	FrameAnimation& NewAnimation = Animation[UpperName];	//�����Ͱ� �ƴϹǷ� map�� new, delete��

	NewAnimation.Image = Image;


	if (0 != _Parameter.FrameIndex.size())
	{
		NewAnimation.FrameIndex = _Parameter.FrameIndex;
	}
	else
	{	
		//���� ������ ������ �ִϸ��̼� ����
		for (int i = _Parameter.Start; i <= _Parameter.End; ++i)
		{
			NewAnimation.FrameIndex.push_back(i);
		}
	}

	if (0 != _Parameter.FrameTime.size())
	{
		//�̹����� ����� ������ �ð�
		NewAnimation.FrameTime = _Parameter.FrameTime;
	}
	else
	{
		//���� ��鸶�� ����Ǵ� �ð��� ����
		for (int i = 0; i < NewAnimation.FrameIndex.size(); ++i)
		{
			NewAnimation.FrameTime.push_back(_Parameter.InterTime);
		}
	}

	NewAnimation.Loop = _Parameter.Loop;
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



void GameEngineRender::CreateReverseAnimation(const FrameAnimationParameter& _Parameter)
{
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind(_Parameter.ImageName);

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

	std::string UpperName = GameEngineString::ToUpper(_Parameter.AnimationName);

	//�ִϸ��̼� �̸��� �ߺ� ����
	if (Animation.end() != Animation.find(UpperName))	//�� ã���� end()��ȯ
	{
		MsgAssert("�̹� �����ϴ� �̸��� �ִϸ��̼� �Դϴ�." + UpperName);
	}

	FrameAnimation& NewAnimation = Animation[UpperName];	//�����Ͱ� �ƴϹǷ� map�� new, delete��

	NewAnimation.Image = Image;


	if (0 != _Parameter.FrameIndex.size())
	{
		NewAnimation.FrameIndex = _Parameter.FrameIndex;
	}
	else
	{
		//���� ������ ������ �ִϸ��̼� ����
		for (int i = _Parameter.Start; i >= _Parameter.End; --i)
		{
			NewAnimation.FrameIndex.push_back(i);
		}
	}

	if (0 != _Parameter.FrameTime.size())
	{
		//�̹����� ����� ������ �ð�
		NewAnimation.FrameTime = _Parameter.FrameTime;
	}
	else
	{
		//���� ��鸶�� ����Ǵ� �ð��� ����
		for (int i = 0; i < NewAnimation.FrameIndex.size(); ++i)
		{
			NewAnimation.FrameTime.push_back(_Parameter.InterTime);
		}
	}

	NewAnimation.Loop = _Parameter.Loop;
	NewAnimation.Parent = this;
}