#pragma once

enum class MarioRenderOrder
{
	BackGround,
	Map,
	UI,
	Monster,
	Item,
	Player = 100,
};

enum class MarioCollisionOrder
{
	Player,
	Monster,
	Item,
	PlayerAttack,				//Fire Attack of Mario
	MonsterAttack,				//Fire Breath of Kupa
};
