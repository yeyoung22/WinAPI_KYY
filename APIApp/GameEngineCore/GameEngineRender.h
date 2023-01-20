#pragma once
#include <map>
#include <GameEnginePlatform/GameEngineImage.h>
#include "GameEngineObject.h"

class FrameAnimationParameter
{
public:
	std::string_view AnimationName = "";
	std::string_view ImageName = "";
	int Start = 0;
	int End = 0;
	int CurrentIndex = 0;
	float InterTime = 0.1f;
	bool Loop = true;
	std::vector<int> FrameIndex = std::vector<int>();
	std::vector<float> FrameTime = std::vector<float>();
};

// 설명 : 랜더링에 관련된 기능
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

	inline void SetScale(float4 _Scale)
	{
		Scale = _Scale;
	}

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

	inline void EffectCameraOff()
	{
		IsEffectCamera = false;
	}

	//애니메이션 효과 생성
	void CreateAnimation(const FrameAnimationParameter& _Paramter);
	//사용할 애니메이션 변경
	void ChangeAnimation(const std::string_view& _AnimationName);

protected:

private:
	int Order = 0;
	float4 Position = float4::Zero;
	float4 Scale = float4::Zero;
	GameEngineImage* Image = nullptr;

	bool IsEffectCamera = true;

	int TransColor = RGB(255, 0, 255);			//Magenta

	int Frame = 0;

	void SetOrder(int _Order);

	void Render(float _DeltaTime);

	class FrameAnimation
	{
	public:
		GameEngineRender* Parent = nullptr;
		//다듬어진 이미지여야 함
		GameEngineImage* Image = nullptr;
		std::vector<int> FrameIndex;
		std::vector<float> FrameTime;
		int CurrentIndex = 0;
		float CurrentTime = 0.0f;
		bool Loop = true;

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


