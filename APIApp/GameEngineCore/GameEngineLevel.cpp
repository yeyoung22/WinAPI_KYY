#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineActor.h"
#include "GameEngineRender.h"
#include "GameEngineCollision.h"

bool GameEngineLevel::IsDebugRender = false;		
float4 GameEngineLevel::TextOutStart = float4::Zero;
std::vector<std::string> GameEngineLevel::DebugTexts;


GameEngineLevel::GameEngineLevel() 
{
}

GameEngineLevel::~GameEngineLevel()
{
	for (std::pair<int, std::list<GameEngineActor*>> UpdateGroup : Actors)					//Range For
	{
		std::list<GameEngineActor*>& ActorList = UpdateGroup.second;						//���簡 �� �Ͼ�� �ϱ� ���� &

		for (GameEngineActor* Actor : ActorList)
		{
			// Actors.erase()
			if (nullptr != Actor)
			{
				delete Actor;
				Actor = nullptr;
			}
		}
	}

	Actors.clear();
}

void GameEngineLevel::ActorStart(GameEngineActor* _Actor, int _Order)
{
	if (nullptr == _Actor)
	{
		MsgAssert("nullptr ���͸� Start�Ϸ��� �߽��ϴ�.");
		return;
	}

	_Actor->SetOwner(this);
	_Actor->SetOrder(_Order);
	_Actor->Start();
}

void GameEngineLevel::ActorsUpdate(float _DeltaTime)
{
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

			for (GameEngineActor* Actor : ActorList)
			{
				if (nullptr == Actor || false == Actor->IsUpdate())
				{
					continue;
				}

				Actor->LiveTime += _DeltaTime;
				Actor->Update(_DeltaTime);
			}
		}
	}

	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

			for (GameEngineActor* Actor : ActorList)
			{
				if (nullptr == Actor || false == Actor->IsUpdate())
				{
					continue;
				}

				Actor->LateUpdate(_DeltaTime);
			}
		}
	}
}



void GameEngineLevel::Release()
{
	//Collision ����
	{ 
		std::map<int, std::list<GameEngineCollision*>>::iterator GroupStartIter = Collisions.begin();
		std::map<int, std::list<GameEngineCollision*>>::iterator GroupEndIter = Collisions.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineCollision*>& CollisionList = GroupStartIter->second;

			std::list<GameEngineCollision*>::iterator CollisionIterStart = CollisionList.begin();
			std::list<GameEngineCollision*>::iterator CollisionIterEnd = CollisionList.end();

			for (; CollisionIterStart != CollisionIterEnd; )
			{
				GameEngineCollision* ReleaseCollision = *CollisionIterStart;

				if (nullptr != ReleaseCollision && false == ReleaseCollision->IsDeath())
				{
					++CollisionIterStart;
					continue;
				}

				CollisionIterStart = CollisionList.erase(CollisionIterStart);
			}
		}
	}
	//Render ����
	{ 
		std::map<int, std::list<GameEngineRender*>>::iterator GroupStartIter = Renders.begin();
		std::map<int, std::list<GameEngineRender*>>::iterator GroupEndIter = Renders.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineRender*>& RenderList = GroupStartIter->second;

			std::list<GameEngineRender*>::iterator RenderIterStart = RenderList.begin();
			std::list<GameEngineRender*>::iterator RenderIterEnd = RenderList.end();

			for (; RenderIterStart != RenderIterEnd; )
			{
				GameEngineRender* ReleaseRender = *RenderIterStart;

				if (nullptr != ReleaseRender && false == ReleaseRender->IsDeath())
				{
					++RenderIterStart;
					continue;
				}

				RenderIterStart = RenderList.erase(RenderIterStart);
			}
		}
	}
	//Actor ����
	{

		std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

			std::list<GameEngineActor*>::iterator ActorIterStart = ActorList.begin();
			std::list<GameEngineActor*>::iterator ActorIterEnd = ActorList.end();

			for (; ActorIterStart != ActorIterEnd; )
			{
				GameEngineActor* ReleaseActor = *ActorIterStart;

				// Actors.erase()
				if (nullptr != ReleaseActor && false == ReleaseActor->IsDeath())
				{
					ReleaseActor->Release();
					++ActorIterStart;
					continue;
				}

				ActorIterStart = ActorList.erase(ActorIterStart);

				delete ReleaseActor;
				ReleaseActor = nullptr;
			}
		}
	}
}


void GameEngineLevel::ActorsRender(float _DeltaTime)
{
	//Render
	{
		std::map<int, std::list<GameEngineRender*>>::iterator GroupStartIter = Renders.begin();
		std::map<int, std::list<GameEngineRender*>>::iterator GroupEndIter = Renders.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineRender*>& RenderList = GroupStartIter->second;

			for (GameEngineRender* Renderer : RenderList)
			{
				if (nullptr == Renderer || false == Renderer->IsUpdate())
				{
					continue;
				}

				Renderer->Render(_DeltaTime);
			}
		}
	}
	//ActorRender
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

			for (GameEngineActor* Actor : ActorList)
			{
				if (nullptr == Actor || false == Actor->IsUpdate())
				{
					continue;
				}

				Actor->Render(_DeltaTime);
			}
		}
	}
	//CollisionDebugRender
	{
		if (true == IsDebugRender)
		{
			std::map<int, std::list<GameEngineCollision*>>::iterator GroupStartIter = Collisions.begin();
			std::map<int, std::list<GameEngineCollision*>>::iterator GroupEndIter = Collisions.end();

			for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
			{
				std::list<GameEngineCollision*>& CollisionList = GroupStartIter->second;
				std::list<GameEngineCollision*>::iterator CollisionIterStart = CollisionList.begin();
				std::list<GameEngineCollision*>::iterator CollisionIterEnd = CollisionList.end();

				for (; CollisionIterStart != CollisionIterEnd; ++CollisionIterStart)
				{
					GameEngineCollision* DebugCollision = *CollisionIterStart;
					if (nullptr == DebugCollision || false == DebugCollision->IsUpdate())
					{
						continue;
					}
					DebugCollision->DebugRender();
				}
			}
		}
	}


	//���
	{
		TextOutStart = float4::Zero;

		for (size_t i = 0; i < DebugTexts.size(); i++)
		{
			HDC ImageDc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
			TextOutA(ImageDc, TextOutStart.ix(), TextOutStart.iy(), DebugTexts[i].c_str(), static_cast<int>(DebugTexts[i].size()));
			TextOutStart.y += 20.0f;
		}

		DebugTexts.clear();					//��� �� ����
	}
}

void GameEngineLevel::PushRender(GameEngineRender* _Render)
{
	if (nullptr == _Render)
	{
		MsgAssert("nullptr�� ������ ������ �׷�ӿ� �������� �߽��ϴ�.");
	}

	//�̹� �� ���� �� ����
	Renders[_Render->GetOrder()].push_back(_Render);
}

void GameEngineLevel::PushCollision(GameEngineCollision* _Collision)
{
	if (nullptr == _Collision)
	{
		MsgAssert("nullptr�� �浹ü�� �浹 �׷�ӿ� �������� �߽��ϴ�.");
	}

	//�̹� �� ���� �� ����
	Collisions[_Collision->GetOrder()].push_back(_Collision);
}