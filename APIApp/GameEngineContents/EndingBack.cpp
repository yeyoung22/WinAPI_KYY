#include "EndingBack.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
 #include "ContentsEnums.h"

EndingBack* EndingBack::Ending = nullptr;

EndingBack::EndingBack() 
{
}

EndingBack::~EndingBack() 
{
}

void EndingBack::Start()
{
	Ending = this;

	float4 Size = GameEngineWindow::GetScreenSize();

	SceneName.push_back("GameOver.bmp");
	SceneName.push_back("Ending2.bmp");
	SceneName.push_back("TimeUp.bmp");

	{
		GameEngineRender* Render = CreateRender(SceneName[static_cast<int>(Scene)], MarioRenderOrder::BackGround);
		Render->SetPosition(GameEngineWindow::GetScreenSize().half());
		Render->SetScale(GameEngineWindow::GetScreenSize());
	}

	{
		TxtImgRender1 = CreateRender("txt1.bmp", MarioRenderOrder::BackGroundTxt);
		TxtImgRender1->SetPosition({ 522, 300 });
		TxtImgRender1->SetScale(ImgScale);
		TxtImgRender1->Off();
	}
	{
		TxtImgRender2 = CreateRender("txt2.bmp", MarioRenderOrder::BackGroundTxt);
		TxtImgRender2->SetPosition({ 508, 460 });
		TxtImgRender2->SetScale(ImgScale);
		TxtImgRender2->Off();
	} 
	{
		TxtImgRender3 = CreateRender("txt3.bmp", MarioRenderOrder::BackGroundTxt);
		TxtImgRender3->SetPosition({ 510, 630 });
		TxtImgRender3->SetScale(ImgScale);
		TxtImgRender3->Off();
	}
	
}

void EndingBack::Update(float _DeltaTime)
{
	WaitTime -= _DeltaTime;
	
	if (EndingScene::Clear == Scene)
	{
		if (8.0f >= WaitTime)
		{
			TxtImgRender1->On();
		}

		if (6.0f >= WaitTime)
		{
			TxtImgRender2->On();
		}

		if (4.0f >= WaitTime)
		{
			TxtImgRender3->On();
		}
	}

}