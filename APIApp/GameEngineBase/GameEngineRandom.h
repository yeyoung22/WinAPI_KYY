#pragma once
#include <random>

// ���� : ���� ������ ���õ� ���
// ������ �ᱹ ������ �˰������� ����� ����,
// �õ尪�� �̿��� ���� �����ϰ� ��
// �õ尪�� �ٲ��� ������ ���� ���� ������ ��
// ���� ���� ���� ���� ��ü�� ���� �������̽����� ���ϰ� ���
class GameEngineRandom
{
public:
	//���� ���� ������ ���� �ʿ�X && �ϳ��� ����ϰ� ���� ��쿡 ���
	static GameEngineRandom MainRandom;
public:
	// constrcuter destructer
	GameEngineRandom();
	~GameEngineRandom();

	// delete Function
	GameEngineRandom(const GameEngineRandom& _Other) = delete;
	GameEngineRandom(GameEngineRandom&& _Other) noexcept = delete;
	GameEngineRandom& operator=(const GameEngineRandom& _Other) = delete;
	GameEngineRandom& operator=(GameEngineRandom&& _Other) noexcept = delete;

	//rand()�Լ��ʹ� �޸� �ִ�, �ּҰ��� ���� ������ ���ԵǾ� �߻�

	int RandomInt(int _Min, int _Max)
	{
		//Creater ���
		std::uniform_int_distribution<int> Uniform(_Min, _Max);		//ǥ���ϰ� ���� ������ �ִ�, �ּҰ�
		return Uniform(MtGen);
	}

	float RandomFloat(float _Min, float _Max)
	{
		std::uniform_real_distribution <float> Uniform(_Min, _Max);
		return Uniform(MtGen);										//�Լ� ��ü ����
	}

	//���� �õ尪�� �־��ֱ� ���� �Լ�
	void SetSeed(__int64 _Seed)
	{
		MtGen = std::mt19937_64(_Seed);
	}

protected:

private:
	//���� ���ʷ����� Ŭ����: ���� ���� �� �� ����
	std::mt19937_64 MtGen = std::mt19937_64();						//�޸��� Ʈ������ �˰����� ����� ���׷�����

	//���� ũ�������� Ŭ����: 1���� �� �� ����
};

