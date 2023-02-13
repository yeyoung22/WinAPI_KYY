#pragma once
#include <string>
#include <string_view>

// 설명 : 오브젝트 구조의 기본 클래스
class GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineObject();
	virtual ~GameEngineObject();				//가상함수 테이블을 위함

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;


	bool IsUpdate()
	{
		//Parent 존재->나는 켜져있어야 함&&죽으면 안됨&&부모도 켜져야 함
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

	//이름 설정
	void SetName(const std::string_view& _View)
	{
		Name = _View;	
	}
	//이름 반환
	const std::string& GetName()
	{
		return Name;
	}

	//이름 복사
	std::string GetNameCopy()
	{
		return Name;
	}

protected:

private:
	int Order;

	GameEngineObject* Parent = nullptr;		//자신을 관리 또는 소유한 오브젝트

	bool ObjectDeath = false;
	bool ObjectUpdate = true;

	std::string Name;
};

