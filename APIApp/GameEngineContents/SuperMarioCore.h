#pragma once
#include <GameEngineCore/GameEngineCore.h>

// ���� :
class SuperMarioCore : public GameEngineCore
{
public:
	// delete Function
	SuperMarioCore(const SuperMarioCore& _Other) = delete;
	SuperMarioCore(SuperMarioCore&& _Other) noexcept = delete;
	SuperMarioCore& operator=(const SuperMarioCore& _Other) = delete;
	SuperMarioCore& operator=(SuperMarioCore&& _Other) noexcept = delete;


	//<�̱���>
	//���α׷��� ��Ʋ�� ���� 1���� ��ü�� ������(������ ����)
	//�ڱ� �ڽ��� ����
	static SuperMarioCore& GetInst()
	{
		return Core;
	}

	// �����ͷ� ����ÿ��� �߰��� ������ ����
	//�߰��� ������ �ָ� ������������ ���� ���� �����Ҵ�?
	//static StudyGameCore& Destroy()
	//{
	//	delete Core;
	//}


protected:
	//�θ𿡼� ���������Լ������Ƿ� �ڽĿ����� ������ ����ȭ
	void Start() override;
	void Update() override;
	void End() override;

private:
	// constrcuter destructer
	SuperMarioCore();					//������ ����
	~SuperMarioCore();



	//static StudyGameCore* Core;
	static SuperMarioCore Core;	
};


