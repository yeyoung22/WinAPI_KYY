#pragma once
#include "GameEngineActor.h"
#include "GameEngineCollision.h"
#include "GameEngineRender.h"

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

	void SetImage();
	void SetScale();

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

protected:
	void Start() override;

private:
	GameEngineRender* Render = nullptr;
	GameEngineCollision* ButtonCollision = nullptr;
	int PointTargetGroup = 0;
	CollisionType ButtonCollisionType = CollisionType::CT_Rect;
	void(*ClickPtr)() = nullptr;

};
