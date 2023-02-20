#pragma once
#include <vector>
#include <GameEngineCore/GameEngineObject.h>
#include <GameEngineCore/GameEngineRender.h>


// 설명 : 텍스트 이미지를 랜더하는 기능
class GameEngineActor;
class TextRenderObject : public GameEngineObject
{
public:
	// constrcuter destructer
	TextRenderObject();
	~TextRenderObject();

	// delete Function
	TextRenderObject(const TextRenderObject& _Other) = delete;
	TextRenderObject(TextRenderObject&& _Other) noexcept = delete;
	TextRenderObject& operator=(const TextRenderObject& _Other) = delete;
	TextRenderObject& operator=(TextRenderObject&& _Other) noexcept = delete;

	void SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor);
	void SetValue(std::string_view& _Word);

	void SetMove(float4 _RenderPos);

	void SetCameraEffectOff();

	void On() override;
	void Off() override;

	void SetRenderPos(float4 _Pos);

	inline std::string_view& GetValue()
	{
		return Word;
	}

protected:

private:
	int Order = 0;
	int TransColor = RGB(255, 0, 255);			//Magenta
	float4 WordScale = {};
	float4 Pos = {};
	std::string_view Word = std::string_view();
	std::string_view ImageName = std::string_view();

	std::vector<GameEngineRender*> WordRenders = std::vector<GameEngineRender*>();
};

