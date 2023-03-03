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