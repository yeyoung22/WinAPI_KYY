#pragma once

enum class MarioRenderOrder
{
	BackGround,					//���� ���� �����Ǿ�� ��
	Map,
	Monster,
	Item,
	Block,
	UI,
	Player = 100,				//���� ���߿� �����Ǿ�� ��
};

enum class MarioCollisionOrder
{
	Player,
	Monster,
	Item,
	QBlock,						//QuestionBlock
	PlayerAttack,				//Fire Attack of Mario
	MonsterAttack,				//Fire Breath of Kupa
	Door,
	Flag,

};
