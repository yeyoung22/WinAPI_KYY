#include "GameEngineActor.h"
#include "GameEngineRender.h"

GameEngineActor::GameEngineActor() 
{
}

GameEngineActor::~GameEngineActor() 
{
}

GameEngineRender* GameEngineActor::CreateRender(const std::string_view& _Image, int _Order /*= 0*/)
{
	GameEngineRender* Render = CreateRender(_Order);
	Render->SetImage(_Image);
	return Render;
}

GameEngineRender* GameEngineActor::CreateRender(int _Order /*= 0*/)
{
	GameEngineRender* Render = new GameEngineRender();
	//수정할 예정

	Render->SetParent(this);
	Render->Owner = this;
	Render->SetOrder(_Order);
	RenderList.push_back(Render);
	return Render;
}