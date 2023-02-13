#pragma once
#include <vector>
#include "GameEngineObject.h"
#include "GameEngineRender.h"

enum class Align				//정렬 상태
{
	Left,
	Right,
	Center
};


// 설명 : 숫자를 숫자이미지로 랜더하는 기능
// 무조건 Actor 계열이어야 함
class GameEngineActor;
class NumberRenderObject : public GameEngineObject
{
public:
	// constrcuter destructer
	NumberRenderObject();
	~NumberRenderObject();

	// delete Function
	NumberRenderObject(const NumberRenderObject& _Other) = delete;
	NumberRenderObject(NumberRenderObject&& _Other) noexcept = delete;
	NumberRenderObject& operator=(const NumberRenderObject& _Other) = delete;
	NumberRenderObject& operator=(NumberRenderObject&& _Other) noexcept = delete;

	//이미지 세팅
	void SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor, const std::string_view& _NegativeName = "");
	//값 세팅
	void SetValue(int _Value);

	void SetMove(float4 _RenderPos);
	void SetAlign(Align _Align);

	void SetCameraEffect(bool _EffectSetting)
	{
		CameraEffect = _EffectSetting;
	}

	void SetRenderPos(float4 _Pos);

	inline int GetValue()
	{
		return Value;
	}

	inline void SetNumOfDigits(int _Num)							//랜더 할 자릿수 설정
	{ 
		NumOfDigits = _Num;
	}

	inline void ResetDigits() 										//자릿수 리셋 (Value만큼 랜더)
	{
		SetNumOfDigits(-1);
	}

protected:

private:
	int Order = 0;
	float4 NumberScale = {};
	float4 Pos = {};
	int Value = 0;
	int TransColor = RGB(255, 0, 255);
	Align AlignState = Align::Left;
	
	bool CameraEffect = false;										//카메라 이펙트 적용
	
	bool Negative = false;											//음수 기호

	int NumOfDigits = -1;											//랜더를 하기 위한 숫자의 자릿수

	std::string_view ImageName = std::string_view();
	std::string_view NegativeName = std::string_view();

	std::vector<GameEngineRender*> NumberRenders = std::vector<GameEngineRender*>();
	GameEngineRender* NegativeRender = nullptr;

	
	void SetNumberRenders(size_t _Index, int _TransColor, float4 _Pos, const std::string_view& _ImageName, float4 _Scale, bool _CameraEffect, int _Frame = -1);
};