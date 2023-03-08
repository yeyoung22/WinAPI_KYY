#pragma once

enum class MarioRenderOrder
{
	BackGround,					//���� ���� �����Ǿ�� ��
	BackGroundTxt,
	Map,
	Monster,
	PlayerAttack,
	Item,
	Block,
	Player = 100,				//���� ���߿� �����Ǿ�� ��
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

