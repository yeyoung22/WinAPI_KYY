#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>

enum class ItemType
{
	NONE,
	SUPERMUSHROOM,
	LIFEMUSHROOM,
	FIREFLOWER,
	COIN,
	HIDDENCOIN,
};


// 설명 : 게임 내 아이템과 관련된 기능
class Item : public GameEngineActor
{
public:
	// constrcuter destructer
	Item();
	~Item();

	// delete Function
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

	void SetItemMode(ItemType _Type)
	{
		ItemMode = _Type;
	}

	void SetItemRenderScale(float4 _Scale);

	void SetColScale(float4 _Scale);

	void SetColPos(float4 _Pos);

	void SetItemRenderOff();

	void SetItemRenderOn();

	void SetBodyColOn();

	void SetBodyColOff();

	void SetSwitchColOn();

	void SetSwitchColOff();

	void SetCoinMode();

	ItemType GetItemMode()
	{
		return ItemMode;
	}

	void CreateItem(float4 _Pos, float4 _Scale, float4 _ColScale, ItemType _Type);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	GameEngineSoundPlayer EffectPlayer;
private:
	bool IsSwitchOn = false;
	bool IsUpEnd = false;
	bool IsDownEnd = false;

	int Point = 100;
	int TPoint = 1000;
	int Black = RGB(0, 0, 0);

	float JumpPower = 380.0f;
	float ImgHalfWidth = 32.0f;
	float UpLimit = -62.0f;
	float MoveSpeed = 310.0f;
	float Gravity = 800.0f;
	float WaitTime = 0.7f;

	float4 Dir = float4::Right;						//기본적인 방향: right
	float4 BasicScale = { 128, 128 };
	float4 MoveDir = float4::Zero;
	float4 PivotRPos = { ImgHalfWidth - 5, -10 };
	float4 PivotLPos = { -ImgHalfWidth +5, -10 };


	ItemType PrevItemMode = ItemType::HIDDENCOIN;
	ItemType ItemMode = ItemType::HIDDENCOIN;

	GameEngineRender* ItemRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineCollision* SwitchCollision = nullptr;
	
	void SetEffectSound(const std::string_view& _String, int _loop = 1, float _BasicVolume = 0.3f);
	void AccGravity(float _DeltaTime);
	bool CheckWall( float4 _Pivot);
	//bool CheckWall(float4 _Pos, float4 _Pivot);
	bool LiftUp();

	std::map<ItemType, std::string> AnimNames = std::map<ItemType, std::string>();
};

