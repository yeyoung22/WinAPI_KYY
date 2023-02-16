#pragma once
#include <map>
#include <GameEnginePlatform/GameEngineImage.h>
#include "GameEngineComponent.h"

enum class TextAlign
{
	Left = TA_LEFT,
	Right = TA_RIGHT,
	Center = TA_CENTER
};


class FrameAnimationParameter
{
public:
	std::string_view AnimationName = "";				//애니메이션 이름
	std::string_view ImageName = "";					//애니메이션화할 이미지
	int Start = 0;										//애니메이션 시작 인덱스
	int End = 0;										//애니메이션 끝 인덱스
	int CurrentIndex = 0;
	float InterTime = 0.1f;
	bool Loop = true;
	std::vector<int> FrameIndex = std::vector<int>();	//애니메이션화할 이미지 인덱스
	std::vector<float> FrameTime = std::vector<float>();
};

// 설명 : 랜더링에 관련된 기능
class GameEngineActor;
class GameEngineLevel;
class GameEngineRender : public GameEngineComponent
{
	friend GameEngineActor;
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineRender();
	~GameEngineRender();

	// delete Function
	GameEngineRender(const GameEngineRender& _Other) = delete;
	GameEngineRender(GameEngineRender&& _Other) noexcept = delete;
	GameEngineRender& operator=(const GameEngineRender& _Other) = delete;
	GameEngineRender& operator=(GameEngineRender&& _Other) noexcept = delete;

	inline GameEngineImage* GetImage()
	{
		return Image;
	}

	//현재 애니메이션에서 몇 번째 프레임이 실행되는지 확인
	//연속된 공격 모션 등에 활용
	inline int GetFrame()
	{
		return Frame;
	}

	void SetTransColor(int _Color)
	{
		TransColor = _Color;
	}

	inline void SetEffectCamera(bool _Effect)
	{
		IsEffectCamera = _Effect;
	}

	//UI같이 카메라 효과가 필요없는 것들은 false
	inline void EffectCameraOff()
	{
		SetEffectCamera(false);
	}
	//카메라 이펙트 켬
	inline void EffectCameraOn()
	{
		SetEffectCamera(true);
	}

	inline int GetTextHeight()
	{
		return TextHeight;
	}

	inline void SetAlpha(int _Alpha)
	{
		Alpha = _Alpha;
	}

	void SetImage(const std::string_view& _ImageName);

	void SetImageToScaleToImage(const std::string_view& _ImageName);

	void SetScaleToImage();

	void SetFrame(int _Frame);

	//애니메이션 효과 생성
	void CreateAnimation(const FrameAnimationParameter& _Parameter);
	//사용할 애니메이션 변경
	void ChangeAnimation(const std::string_view& _AnimationName);
	//애니메이션이 끝났는지 체크
	bool IsAnimationEnd();

	void SetOrder(int _Order) override;

	void SetText(const std::string_view& _Text, const int _TextHeight = 20, const std::string_view& _TextType = "굴림", const TextAlign _TextAlign = TextAlign::Center, const COLORREF _TextColor = RGB(0, 0, 0));

	//------test code
	void CreateReverseAnimation(const FrameAnimationParameter& _Parameter);


protected:

private:
	GameEngineImage* Image = nullptr;

	bool IsEffectCamera = true;					//카메라와 함께 움직이는 것들(true)

	int TransColor = RGB(255, 0, 255);			//Magenta

	int Frame = 0;

	int Alpha = 255;

	void Render(float _DeltaTime);
	void TextRender(float _DeltaTime);
	void ImageRender(float _DeltaTime);

	class FrameAnimation
	{
	public:
		GameEngineRender* Parent = nullptr;
		GameEngineImage* Image = nullptr;		//다듬어진 이미지여야 함
		std::vector<int> FrameIndex;			//지정한 범위의 이미지로 애니메이션만들 경우
		std::vector<float> FrameTime;			//이미지 사이 넘기는 시간 간격이 다를 경우 대비
		int CurrentIndex = 0;					//현재 인덱스
		float CurrentTime = 0.0f;
		bool Loop = true;						//마지막 이미지에서 기본적으로 멈춤

		bool IsEnd();

		void Render(float _DeltaTime);

		void Reset()
		{
			CurrentIndex = 0;
			CurrentTime = 0.0f;
		}
	};

	std::map<std::string, FrameAnimation> Animation;
	FrameAnimation* CurrentAnimation = nullptr;

	/// <summary>
/// TextRender
/// </summary>
	std::string RenderText = std::string();
	int TextHeight = 0;
	std::string TextType = std::string();
	TextAlign Align = TextAlign::Left;
	COLORREF TextColor = RGB(0, 0, 0);
	// 그런걸 하면 HBRUSH 만드는데 사용하고 나면 Release
	// GameEngineImage를 참조
};


