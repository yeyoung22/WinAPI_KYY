#pragma once
#include <vector>
#include <GameEngineCore/GameEngineActor.h>


// º≥∏Ì : ∞‘¿” ∏ 
class Map : public GameEngineActor
{
public:
	static float SumMapWidth;
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

	inline void StageClearOn()
	{
		IsStageClear = true;
	}

	std::vector<std::string> GetColMaps()
	{
		std::vector<std::string> ReturnVector;
		ReturnVector.reserve(ColMaps.size());

		for (int i = 0; i < ColMaps.size(); i++)
		{
			ReturnVector.push_back(ColMaps[i]);
		}

		return ReturnVector;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool IsStageClear = false;

	GameEngineRender* MapRender0 = nullptr;
	GameEngineRender* MapRender1 = nullptr;

	GameEngineCollision* BodyCollision = nullptr;

	std::vector<GameEngineRender*> MapRenders = std::vector<GameEngineRender*>();
	std::vector<std::string> Maps = std::vector<std::string>();
	std::vector<std::string> ColMaps = std::vector<std::string>();
};