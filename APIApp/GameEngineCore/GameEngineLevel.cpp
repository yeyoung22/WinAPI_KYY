#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineActor.h"
#include "GameEngineRender.h"
#include "GameEngineCollision.h"

bool GameEngineLevel::IsDebugRender = false;												//기본적으로 false	
float4 GameEngineLevel::TextOutStart = float4::Zero;
std::vector<std::string> GameEngineLevel::DebugTexts;


GameEngineLevel::GameEngineLevel() 
{
}

GameEngineLevel::~GameEngineLevel()
{
	for (std::pair<int, std::list<GameEngineActor*>> UpdateGroup : Actors)					//Range For
	{
		std::list<GameEngineActor*>& ActorList = UpdateGroup.second;						//복사가 안 일어나게 하기 위한 &

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


float4 GameEngineLevel::GetMousePos()
{
	return GameEngineWindow::GetMousePosition();
}
float4 GameEngineLevel::GetMousePosToCamera()
{
	return GameEngineWindow::GetMousePosition() + CameraPos;
}

void GameEngineLevel::ActorStart(GameEngineActor* _Actor, int _Order)
{
	if (nullptr == _Actor)
	{
		MsgAssert("nullptr 액터를 Start하려고 했습니다.");
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
			int Order = GroupStartIter->first;
			float CurTimeScale = 1.0f;
			//현재 TimeScale은 1.0f이며, 일반적으로 영향을 주지 않음
			//TimeScale을 0으로 설정하거나 그 외의 값을 주면
			//화면을 정지(특정 그룹을 정지)시키거나 빠르게 움직여 보이게 할 수 있음
			if (TimeScales.end() != TimeScales.find(Order))
			{
				CurTimeScale = TimeScales[Order];
			}

			for (GameEngineActor* Actor : ActorList)
			{
				// Actors.erase()
				if (nullptr == Actor || false == Actor->IsUpdate())
				{
					continue;
				}

				//LiveTime은 진짜 살아있는 시간
				//TimeScale의 영향을 받지 않고 받아서도 안됨
				Actor->TimeScale = CurTimeScale;
				Actor->LiveTime += _DeltaTime;
				Actor->Update(_DeltaTime * CurTimeScale);
			}
		}
	}
}




void GameEngineLevel::Release()
{
	//Collision 삭제
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
	//Render 삭제
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
	//Actor 삭제
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

				Renderer->Render(_DeltaTime * Renderer->GetActor()->TimeScale);
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


	//출력
	{
		TextOutStart = float4::Zero;

		for (size_t i = 0; i < DebugTexts.size(); i++)
		{
			HDC ImageDc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
			TextOutA(ImageDc, TextOutStart.ix(), TextOutStart.iy(), DebugTexts[i].c_str(), static_cast<int>(DebugTexts[i].size()));
			TextOutStart.y += 20.0f;
		}

		DebugTexts.clear();					//사용 후 제거
	}
}


void GameEngineLevel::ActorLevelChangeEnd(GameEngineLevel* _NextLevel)
{
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

			for (GameEngineActor* Actor : ActorList)
			{
				Actor->LevelChangeEnd(_NextLevel);
			}
		}
	}
}

//레벨이 바뀌면 해당 레벨에 있던 액터들도 바뀐 레벨로 이동
void GameEngineLevel::ActorLevelChangeStart(GameEngineLevel* _PrevLevel)
{
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

			for (GameEngineActor* Actor : ActorList)
			{
				Actor->LevelChangeStart(_PrevLevel);
			}
		}
	}
}

void GameEngineLevel::PushRender(GameEngineRender* _Render, int _ChangeOrder)
{
	// 0 => 10
	//제거하고 새로운 곳에 넣음
	Renders[_Render->GetOrder()].remove(_Render);

	_Render->GameEngineObject::SetOrder(_ChangeOrder);
	if (nullptr == _Render)
	{
		MsgAssert("nullptr인 랜더를 랜더링 그룹속에 넣으려고 했습니다.");
	}

	//이미 들어가 있을 수 있음
	Renders[_Render->GetOrder()].push_back(_Render);
}

void GameEngineLevel::PushCollision(GameEngineCollision* _Collision, int _ChangeOrder)
{
	//그룹에서 제거한 뒤, 새로운 오더(변경하고 싶은)로 그룹에 다시 넣음
	Collisions[_Collision->GetOrder()].remove(_Collision);

	_Collision->GameEngineObject::SetOrder(_ChangeOrder);

	if (nullptr == _Collision)
	{
		MsgAssert("nullptr인 충돌체를 충돌 그룹속에 넣으려고 했습니다.");
	}

	//이미 들어가 있을 수 있음
	Collisions[_Collision->GetOrder()].push_back(_Collision);
}