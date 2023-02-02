#pragma once
#include <map>
#include <GameEnginePlatform/GameEngineImage.h>
#include "GameEngineComponent.h"

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

	void SetImage(const std::string_view& _ImageName);

	void SetScaleToImage();

	void SetFrame(int _Frame);

	inline GameEngineImage* GetImage()
	{
		return Image;
	}

	inline int GetFrame()
	{
		return Frame;
	}

	void SetTransColor(int _Color)
	{
		TransColor = _Color;
	}

	//UI���� ī�޶� ȿ���� �ʿ���� �͵��� false
	inline void EffectCameraOff()
	{
		IsEffectCamera = false;
	}

	//�ִϸ��̼� ȿ�� ����
	void CreateAnimation(const FrameAnimationParameter& _Paramter);
	//����� �ִϸ��̼� ����
	void ChangeAnimation(const std::string_view& _AnimationName);
	//�ִϸ��̼��� �������� üũ
	bool IsAnimationEnd();

	void SetOrder(int _Order) override;

protected:

private:
	GameEngineImage* Image = nullptr;

	bool IsEffectCamera = true;					//ī�޶�� �Բ� �����̴� �͵�(true)

	int TransColor = RGB(255, 0, 255);			//Magenta

	int Frame = 0;

	void Render(float _DeltaTime);

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
};


