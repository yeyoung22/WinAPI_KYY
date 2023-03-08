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
	Player = 100,				//가장 나중에 랜더되어야 함
	UI,
	Pipe
};

enum class MarioCollisionOrder
{
	Player,
	Monster,
	Item,
	Brick,
	QBlock,
	BlockItem,
	ItemOn,
	Pipe,
	PlayerAttack,				//Fire Attack of Mario
	MonsterAttack,				//Fire Breath of Kupa
	Shell,
	Door,
	Flag,
	DeadLine,
	MonsterTrigger,
	Hidden,



};

enum class EndingScene
{
	Clear,
	GameOver,
	TimeOver,
};

