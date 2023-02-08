#pragma once
#include "GameEngineActor.h"
#include "GameEngineCollision.h"
#include "GameEngineRender.h"

enum class ButtonState
{
	Release, // 안눌렸다.
	Press, // 눌렸다.
	Hover, // 나를 누를수 있는 녀석이 위에서 맴돌고 있다.
};


// 설명 : 버튼과 관련된 기능
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

	//마우스로 클릭하면 그에 해당하는 행동을 하는 함수를 CallBack
	void SetClickCallBack(void(*_ClickPtr)())
	{
		ClickPtr = _ClickPtr;
	}

	//충돌체크 할 그룹 설정
	void SetTargetCollisionGroup(int _PointTargetGroup);

	//버튼의 충돌체 타입 설정
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
