#pragma once

enum class MarioRenderOrder
{
	BackGround,
	Map,
	Monster,
	Item,
	Player,
};

enum class MarioCollisionOrder
{
	Player,
	Monster,
	Item,
	PlayerAttack,				//Fire Attack of Mario
	MonsterAttack,				//Fire Breath of Kupa
};
