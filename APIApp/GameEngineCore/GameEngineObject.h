#pragma once


// ���� : ������Ʈ ������ �⺻ Ŭ����
class GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineObject();
	virtual ~GameEngineObject();				//�����Լ� ���̺��� ����

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;


	bool IsUpdate()
	{
		//Parent ����->���� �����־�� ��&&������ �ȵ�&&�θ� ������ ��
		return nullptr != Parent ? ((true == ObjectUpdate && false == IsDeath()) && true == Parent->IsUpdate()) : (ObjectUpdate && false == IsDeath());
	}

	bool IsDeath()
	{
		return nullptr != Parent ? (true == ObjectDeath || Parent->IsDeath()) : (true == ObjectDeath);
	}

	void Death()
	{
		ObjectDeath = true;
	}

	void On()
	{
		ObjectUpdate = true;
	}
	void Off()
	{
		ObjectUpdate = false;
	}

	void OnOffSwtich()
	{
		ObjectUpdate = !ObjectUpdate;
	}

	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}

	int GetOrder()
	{
		return Order;
	}

	void SetOwner(GameEngineObject* _Parent)
	{
		Parent = _Parent;
	}

	template<typename ConvertType>
	ConvertType* GetOwner()
	{
		return dynamic_cast<ConvertType*>(Parent);
	}

	GameEngineObject* GetOwner()
	{
		return Parent;
	}

protected:

private:
	int Order;

	GameEngineObject* Parent = nullptr;		//�ڽ��� ���� �Ǵ� ������ ������Ʈ

	bool ObjectDeath = false;
	bool ObjectUpdate = true;
};

