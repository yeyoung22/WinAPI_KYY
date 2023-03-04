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
	UI,
	Player = 100,				//���� ���߿� �����Ǿ�� ��
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
	Pipe,
	PlayerAttack,				//Fire Attack of Mario
	MonsterAttack,				//Fire Breath of Kupa
	Door,
	Flag,
	DeadLine,
	MoveStart,


};

enum class EndingScene
{
	Clear,
	GameOver,
	TimeOver,
};