#pragma once
#include <string>
#include <string_view>

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

	virtual void On()
	{
		ObjectUpdate = true;
	}
	virtual void Off()
	{
		ObjectUpdate = false;
	}

	virtual void OnOffSwtich()
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

	virtual void SetOwner(GameEngineObject* _Parent)
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

	//�̸� ����
	void SetName(const std::string_view& _View)
	{
		Name = _View;	
	}
	//�̸� ��ȯ
	const std::string& GetName()
	{
		return Name;
	}

	//�̸� ����
	std::string GetNameCopy()
	{
		return Name;
	}

protected:

private:
	int Order;

	GameEngineObject* Parent = nullptr;		//�ڽ��� ���� �Ǵ� ������ ������Ʈ

	bool ObjectDeath = false;
	bool ObjectUpdate = true;

	std::string Name;
};

