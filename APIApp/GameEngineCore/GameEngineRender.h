#pragma once
#include <map>
#include <GameEnginePlatform/GameEngineImage.h>
#include "GameEngineObject.h"

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
class GameEngineRender : public GameEngineObject
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

	inline void SetPosition(float4 _Position)
	{
		Position = _Position;
	}

	inline void SetMove(float4 _Position)
	{
		Position += _Position;
	}

	inline void SetScale(float4 _Scale)
	{
		Scale = _Scale;
	}
	
	void SetScaleToImage();

	void SetFrame(int _Frame);

	inline GameEngineImage* GetImage()
	{
		return Image;
	}

	inline int GetOrder()
	{
		return Order;
	}

	inline int GetFrame()
	{
		return Frame;
	}

	GameEngineActor* GetActor();

	void SetTransColor(int _Color)
	{
		TransColor = _Color;
	}

	inline float4 GetPosition()
	{
		return Position;
	}

	inline float4 GetScale()
	{
		return Scale;
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

protected:

private:
	int Order = 0;
	float4 Position = float4::Zero;
	float4 Scale = float4::Zero;
	GameEngineImage* Image = nullptr;

	bool IsEffectCamera = true;					//ī�޶�� �Բ� �����̴� �͵�(true)

	int TransColor = RGB(255, 0, 255);			//Magenta

	int Frame = 0;

	void SetOrder(int _Order);

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


