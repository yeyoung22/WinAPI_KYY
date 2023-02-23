#pragma once

enum class MarioRenderOrder
{
	BackGround,					//가장 먼저 랜더되어야 함
	Map,
	Monster,
	Item,
	Block,
	UI,
	Player = 100,				//가장 나중에 랜더되어야 함
};

enum class MarioCollisionOrder
{
	Player,
	Monster,
	Item,
	Block,
	PlayerAttack,				//Fire Attack of Mario
	MonsterAttack,				//Fire Breath of Kupa
	Door,
	Flag,

};
