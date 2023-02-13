#pragma once
#include "GameEngineActor.h"
#include "GameEngineCollision.h"
#include "GameEngineRender.h"

enum class ButtonState
{
	Release,			//Ŭ�� ����
	Press,				//Ŭ��
	Hover,				//Ŭ������ �ʰ� ������ �ɵ��� ����
};


// ���� : ��ư�� ���õ� ���
class GameEngineRender;
class Button : public GameEngineActor
{
public:
	// constrcuter destructer
	Button();
	~Button();

	// delete Function
	Button(const Button& _Other) = delete;
	Button(Button&& _Other) noexcept = delete;
	Button& operator=(const Button& _Other) = delete;
	Button& operator=(Button&& _Other) noexcept = delete;

	void SetRenderOrder(int _Value);

	void SetScale(float4 _Scale);

	//���콺�� Ŭ���ϸ� �׿� �ش��ϴ� �ൿ�� �ϴ� �Լ��� CallBack
	void SetClickCallBack(void(*_ClickPtr)())
	{
		ClickPtr = _ClickPtr;
	}

	//�浹üũ �� �׷� ����
	void SetTargetCollisionGroup(int _PointTargetGroup);

	//��ư�� �浹ü Ÿ�� ����
	void SetButtonCollisionType(CollisionType _ButtonCollisionType)
	{
		ButtonCollisionType = _ButtonCollisionType;
	}

	void SetHoverImage(const std::string_view& _Name, int _HoverIndex = -1)
	{
		HoverImageName = _Name;
		HoverIndex = _HoverIndex;
	}
	void SetReleaseImage(const std::string_view& _Name, int _ReleaseIndex = -1)
	{
		ReleaseImageName = _Name;
		ReleaseIndex = _ReleaseIndex;
	}
	void SetPressImage(const std::string_view& _Name, int _PressIndex = -1)
	{
		PressImageName = _Name;
		PressIndex = _PressIndex;
	}

	GameEngineRender* GetButtonRender()
	{
		return ButtonRender;
	}

	GameEngineCollision* GetButtonCollision()
	{
		return ButtonCollision;
	}

	ButtonState GetState()
	{
		return State;
	}

	int GetHoverIndex()
	{
		return HoverIndex;
	}

	int GetReleaseIndex()
	{
		return ReleaseIndex;
	}

	int GetPressIndex()
	{
		return PressIndex;
	}

	void SetCollisionOrder(int _Order);

	float4 GetScale()
	{
		return Scale;
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender* ButtonRender = nullptr;
	GameEngineCollision* ButtonCollision = nullptr;
	int PointTargetGroup = 0;
	CollisionType ButtonCollisionType = CollisionType::CT_Rect;
	void(*ClickPtr)() = nullptr;

	float4 Scale;
	ButtonState State;
	std::string CurImageName;
	std::string HoverImageName;
	int HoverIndex = -1;
	std::string ReleaseImageName;
	int ReleaseIndex = -1;
	std::string PressImageName;
	int PressIndex = -1;
};
