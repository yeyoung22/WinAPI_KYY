#pragma once
#include <GameEngineCore/GameEngineCore.h>

// 설명 :
class SuperMarioCore : public GameEngineCore
{
public:
	// delete Function
	SuperMarioCore(const SuperMarioCore& _Other) = delete;
	SuperMarioCore(SuperMarioCore&& _Other) noexcept = delete;
	SuperMarioCore& operator=(const SuperMarioCore& _Other) = delete;
	SuperMarioCore& operator=(SuperMarioCore&& _Other) noexcept = delete;


	//<싱글톤>
	//프로그램을 통틀어 오직 1개의 객체만 생성됨(생성자 막음)
	//자기 자신을 가짐
	static SuperMarioCore& GetInst()
	{
		return Core;
	}

	// 포인터로 만들시에는 중간에 삭제가 용이
	//중간에 지워질 애를 포인터형으로 만들어서 굳이 동적할당?
	//static StudyGameCore& Destroy()
	//{
	//	delete Core;
	//}


protected:
	//부모에서 순수가상함수였으므로 자식에서는 구현이 강제화
	void Start() override;
	void Update() override;
	void End() override;

private:
	// constrcuter destructer
	SuperMarioCore();					//생성자 막음
	~SuperMarioCore();



	//static StudyGameCore* Core;
	static SuperMarioCore Core;	
};


