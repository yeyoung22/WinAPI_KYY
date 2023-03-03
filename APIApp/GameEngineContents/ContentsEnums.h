#pragma once

enum class MarioRenderOrder
{
	BackGround,					//가장 먼저 랜더되어야 함
	BackGroundTxt,
	Map,
	Monster,
	PlayerAttack,
	Item,
	Block,
	UI,
	Player = 100,				//가장 나중에 랜더되어야 함
	Pipe
};

enum class MarioCollisionOrder
{
	Player,
	Monster,
	Item,
	Block,
	Pipe,
	PlayerAttack,				//Fire Attack of Mario
	MonsterAttack,				//Fire Breath of Kupa
	Door,
	Flag,

};

enum class EndingScene
{
	Clear,
	GameOver,
	TimeOver,
};