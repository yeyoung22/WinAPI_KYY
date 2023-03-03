#pragma once
#include "Block.h"

// 설명 :
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

	bool CheckRightBlock();
	bool CheckLeftBlock();
	bool CheckBottBlock();
	bool CheckHeadBlock();


protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:
	bool TimerStart = false;

	float BlockScale = 64.0f;
	float BlockHalfScale = 32.0f;
	float MicroCtrlVert = 5.0f;
	float MicroCtrlHorz = 28.0f;


	float BasicVolume = 0.3f;									//Set Volume
	float WaitTime = 0.2f;
	float Gravity = 200.0f;

	float4 StartPos = float4::Zero;
	float4 MoveDir = float4::Zero;								//옮겨갈 벡터

	float BlockSizeHalf = 32.0f;			//block 64*64


	GameEngineRender* BlockRender = nullptr;
	GameEngineCollision* BlockCollision = nullptr;				//효과를 주면 없앨 충돌체


	//벽면이 될 충돌채
	GameEngineCollision* HeadBlockCollision = nullptr;			
	GameEngineCollision* LeftBlockCollision = nullptr;
	GameEngineCollision* RightBlockCollision = nullptr;
	GameEngineCollision* BottomBlockCollision = nullptr;


	void MoveUp();
	void MoveDown(float _DeltaTime);

};

