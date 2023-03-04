#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 마리오 불꽃과 같은 투사체
class Player;
class Effect : public GameEngineActor
{
	friend Player;
public:
	// constrcuter destructer
	Effect();
	~Effect();

	// delete Function
	Effect(const Effect& _Other) = delete;
	Effect(Effect&& _Other) noexcept = delete;
	Effect& operator=(const Effect& _Other) = delete;
	Effect& operator=(Effect&& _Other) noexcept = delete;

	void DirCheck(const std::string_view& _AnimationName);

	void SetEffectDir(std::string _str)
	{
		if (_str  == "Left_")
		{
			Dir = float4::Left;
		}
		else if (_str == "Right_")
		{
			Dir = float4::Right;
		}
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool IsGround = false;

	int Black = RGB(0, 0, 0);


	float ImgHalfWidth = 32.0f;
	float JumpPower = 230.0f;
	float MoveSpeed = 500.0f;
	float Gravity = 730.0f;

	float4 Dir = float4::Zero;
	float4 MoveDir = float4::Zero;
	float4 PivotRPos = { ImgHalfWidth - 8, -3 };
	float4 PivotLPos = { -ImgHalfWidth + 8, -3 };

	std::string DirString = "Right_";
	

	GameEngineRender* FireRender = nullptr;
	GameEngineCollision* FireCollision = nullptr;

	//Lift Player's Position upward
	bool LiftUp(float4 _Pos = float4::Zero);


	//벽인지 확인하는 함수
	bool CheckWall(float4 _Pivot = float4::Zero);



};

