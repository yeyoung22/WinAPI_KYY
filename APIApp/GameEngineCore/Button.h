#pragma once
#include "GameEngineActor.h"
#include "GameEngineCollision.h"
#include "GameEngineRender.h"

enum class ButtonState
{
	Release,			//클릭 안함
	Press,				//클릭
	Hover,				//클릭하지 않고 위에서 맴도는 상태
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
