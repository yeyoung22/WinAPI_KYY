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
	std::string_view AnimationName = "";				//�ִϸ��̼� �̸�
	std::string_view ImageName = "";					//�ִϸ��̼�ȭ�� �̹���
	int Start = 0;										//�ִϸ��̼� ���� �ε���
	int End = 0;										//�ִϸ��̼� �� �ε���
	int CurrentIndex = 0;
	float InterTime = 0.1f;
	bool Loop = true;
	std::vector<int> FrameIndex = std::vector<int>();	//�ִϸ��̼�ȭ�� �̹��� �ε���
	std::vector<float> FrameTime = std::vector<float>();
};

// ���� : �������� ���õ� ���
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

	//���� �ִϸ��̼ǿ��� �� ��° �������� ����Ǵ��� Ȯ��
	//���ӵ� ���� ��� � Ȱ��
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

	//UI���� ī�޶� ȿ���� �ʿ���� �͵��� false
	inline void EffectCameraOff()
	{
		SetEffectCamera(false);
	}
	//ī�޶� ����Ʈ ��
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

	//�ִϸ��̼� ȿ�� ����
	void CreateAnimation(const FrameAnimationParameter& _Parameter);
	//����� �ִϸ��̼� ����
	void ChangeAnimation(const std::string_view& _AnimationName);
	//�ִϸ��̼��� �������� üũ
	bool IsAnimationEnd();

	void SetOrder(int _Order) override;

	void SetText(const std::string_view& _Text, const int _TextHeight = 20, const std::string_view& _TextType = "����", const TextAlign _TextAlign = TextAlign::Center, const COLORREF _TextColor = RGB(0, 0, 0));

	//------test code
	void CreateReverseAnimation(const FrameAnimationParameter& _Parameter);


protected:

private:
	GameEngineImage* Image = nullptr;

	bool IsEffectCamera = true;					//ī�޶�� �Բ� �����̴� �͵�(true)

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
		GameEngineImage* Image = nullptr;		//�ٵ���� �̹������� ��
		std::vector<int> FrameIndex;			//������ ������ �̹����� �ִϸ��̼Ǹ��� ���
		std::vector<float> FrameTime;			//�̹��� ���� �ѱ�� �ð� ������ �ٸ� ��� ���
		int CurrentIndex = 0;					//���� �ε���
		float CurrentTime = 0.0f;
		bool Loop = true;						//������ �̹������� �⺻������ ����

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
	// �׷��� �ϸ� HBRUSH ����µ� ����ϰ� ���� Release
	// GameEngineImage�� ����
};


