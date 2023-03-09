#pragma once
#include "Block.h"

// ���� :
class QuestionBlock :public Block
{
public: 
	//static QuestionBlock* QBlock;
public:
	// constrcuter destructer
	QuestionBlock();
	~QuestionBlock();

	// delete Function
	QuestionBlock(const QuestionBlock& _Other) = delete;
	QuestionBlock(QuestionBlock&& _Other) noexcept = delete;
	QuestionBlock& operator=(const QuestionBlock& _Other) = delete;
	QuestionBlock& operator=(QuestionBlock&& _Other) noexcept = delete;


	void SetImgChange(); 
	//void SetQBlockColOff();
	void SetQBlockRenOff();
	void SetQBlockRenOn();
	void IsMoveOn()
	{
		IsMove = true;
	}
	void SetIsUsedOn()
	{
		IsUsed = true;
	}
	bool GetIsUsed()
	{
		return IsUsed;
	}
	void SetHiddenColOn();
	void SetHiddenColOff();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:
	bool IsUsed = false;
	bool IsMove = false;
	bool IsUpEnd = false;

	float BlockScale = 64.0f;
	float BlockHalfScale = 32.0f;
	float MicroCtrlVert = 5.0f;
	float MicroCtrlHorz = 28.0f;
	float UpPower = 16.0f;

	float WaitTime = 0.2f;
	float Gravity = 500.0f;
	float MoveSpeed = 300.0f;


	float4 StartPos = float4::Zero;
	float4 MoveDir = float4::Zero;								//�Űܰ� ����


	GameEngineRender* BlockRender = nullptr;
	GameEngineCollision* EffectCollision = nullptr;				//ȿ���� �ָ� ���� �浹ü
	GameEngineCollision* HiddenCollision = nullptr;

	//������ �� �浹ä
	GameEngineCollision* BlockCollision = nullptr;			


	void MoveUp(float _DeltaTime);
	void MoveDown(float _DeltaTime);
};

