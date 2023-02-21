#pragma once
#include <vector>
#include <GameEngineCore/GameEngineObject.h>
#include <GameEngineCore/GameEngineRender.h>


// 설명 : 알파벳 이미지를 랜더하는 기능
class GameEngineActor;
class WordRenderObject : public GameEngineObject
{
public:
	// constrcuter destructer
	WordRenderObject();
	~WordRenderObject();

	// delete Function
	WordRenderObject(const WordRenderObject& _Other) = delete;
	WordRenderObject(WordRenderObject&& _Other) noexcept = delete;
	WordRenderObject& operator=(const WordRenderObject& _Other) = delete;
	WordRenderObject& operator=(WordRenderObject&& _Other) noexcept = delete;

	void SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor);
	virtual void SetValue(std::string_view& _Word);

	void SetMove(float4 _RenderPos);

	virtual void SetCameraEffectOff();

	void On() override;
	void Off() override;

	virtual void SetRenderPos(float4 _Pos);

	inline std::string_view& GetValue()
	{
		return Word;
	}

protected:
	int Order = 0;
	int TransColor = RGB(255, 0, 255);			//Magenta
	float4 WordScale = {};
	float4 Pos = {};
	std::string_view Word = std::string_view();
	std::string_view ImageName = std::string_view();

private:
	std::vector<GameEngineRender*> WordRenders = std::vector<GameEngineRender*>();
};

