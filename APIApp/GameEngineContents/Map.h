#pragma once
#include <GameEngineCore/GameEngineActor.h>

// º≥∏Ì : ∞‘¿” ∏ 
class Map : public GameEngineActor
{
public:
	static Map* MainMap;
public:
	// constrcuter destructer
	Map();
	~Map();

	// delete Function
	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

	inline void IsStageClearOn()
	{
		IsStageClear = true;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool IsStageClear = false;

	GameEngineRender* MapRender0 = nullptr;
	GameEngineRender* MapRender1 = nullptr;
};

