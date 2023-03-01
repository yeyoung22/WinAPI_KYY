#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

enum class ItemType
{
	NONE,
	SUPERMUSHROOM,
	LIFEMUSHROOM,
	FIREFLOWER,
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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	GameEngineSoundPlayer EffectPlayer;
private:
	float MoveSpeed = 120.0f;

	ItemType PrevItemMode = ItemType::SUPERMUSHROOM;
	ItemType ItemMode = ItemType::SUPERMUSHROOM;

	GameEngineRender* ItemRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	
	std::map<ItemType, std::string> AnimNames = std::map<ItemType, std::string>();
};

