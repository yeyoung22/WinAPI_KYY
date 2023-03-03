#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>


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

	void CreateItem(float4 _Pos, float4 _Scale, float4 _ColScale, ItemType _Type);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	GameEngineSoundPlayer EffectPlayer;
private:
	int Point = 100;

	float MoveSpeed = 120.0f;

	float4 BasicScale = { 128, 128 };

	ItemType PrevItemMode = ItemType::SUPERMUSHROOM;
	ItemType ItemMode = ItemType::SUPERMUSHROOM;

	GameEngineRender* ItemRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	
	std::map<ItemType, std::string> AnimNames = std::map<ItemType, std::string>();
};

