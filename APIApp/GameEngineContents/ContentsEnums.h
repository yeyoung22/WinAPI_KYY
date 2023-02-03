#pragma once

enum class MarioRenderOrder
{
	BackGround,
	Map,
	Monster,
	Player,
};

enum class MarioCollisionOrder
{
	Player,
	Monster,
	PlayerAttack,
	MonsterAttack,
};