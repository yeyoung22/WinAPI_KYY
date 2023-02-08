#include "Button.h"
#include <GameEnginePlatform/GameEngineInput.h>

Button::Button()
{
}

Button::~Button()
{
}

void Button::SetImage()
{

}

void Button::SetTargetCollisionGroup(int _PointTargetGroup)
{
	PointTargetGroup = _PointTargetGroup;
	if (nullptr == ButtonCollision)
	{
		ButtonCollision = CreateCollision(PointTargetGroup);
	}
}


void Button::Start()
{

	Render = CreateRender();
}

void Button::SetScale()
{
	if (true == ButtonCollision->Collision({ .TargetGroup = PointTargetGroup, .TargetColType = CollisionType::CT_Point, .ThisColType = ButtonCollisionType }))
	{
		if (true == GameEngineInput::IsDown("EngineMouseLeft") && nullptr != ClickPtr)
		{
			ClickPtr();
		}
	}
}