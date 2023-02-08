#pragma once
#include "GameEngineActor.h"
#include "GameEngineCollision.h"
#include "GameEngineRender.h"

enum class ButtonState
{
	Release, // �ȴ��ȴ�.
	Press, // ���ȴ�.
	Hover, // ���� ������ �ִ� �༮�� ������ �ɵ��� �ִ�.
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

	std::string SetHoverImage(const std::string_view& _Name)
	{
		HoverImageName = _Name;
	}
	std::string SetReleaseImage(const std::string_view& _Name)
	{
		ReleaseImageName = _Name;
	}
	std::string SetPressImage(const std::string_view& _Name)
	{
		PressImageName = _Name;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender* Render = nullptr;
	GameEngineCollision* ButtonCollision = nullptr;
	int PointTargetGroup = 0;
	CollisionType ButtonCollisionType = CollisionType::CT_Rect;
	void(*ClickPtr)() = nullptr;

	ButtonState State;
	std::string CurImageName;
	std::string HoverImageName;
	std::string ReleaseImageName;
	std::string PressImageName;
};
