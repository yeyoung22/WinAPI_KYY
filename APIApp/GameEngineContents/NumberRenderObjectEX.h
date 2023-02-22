#pragma once
#include <vector>
#include <GameEngineCore/GameEngineObject.h>
#include <GameEngineCore/GameEngineRender.h>


enum class Align				//���� ����
{
	Left,
	Right,
	Center
};


// ���� : ���ڸ� �����̹����� �����ϴ� ���
// ������ Actor �迭�̾�� ��
class GameEngineActor;
class NumberRenderObjectEX : public GameEngineObject
{
public:
	// constrcuter destructer
	NumberRenderObjectEX();
	~NumberRenderObjectEX();

	// delete Function
	NumberRenderObjectEX(const NumberRenderObjectEX& _Other) = delete;
	NumberRenderObjectEX(NumberRenderObjectEX&& _Other) noexcept = delete;
	NumberRenderObjectEX& operator=(const NumberRenderObjectEX& _Other) = delete;
	NumberRenderObjectEX& operator=(NumberRenderObjectEX&& _Other) noexcept = delete;

	//�̹��� ����
	void SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor, const std::string_view& _NegativeName = "");
	//�� ����
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

	inline void SetNumOfDigits(int _Num)							//���� �� �ڸ��� ����
	{
		NumOfDigits = _Num;
	}

	inline void ResetDigits() 										//�ڸ��� ���� (Value��ŭ ����)
	{
		SetNumOfDigits(-1);
	}


	//�� ����� �ڸ����� �����ϰڴٴ� �ǹ��� �Լ�
	inline void SetIsFixedOn()
	{
		IsFixed = true;												//�ڸ��� �Һ�
	}

	inline void SetIsFixedOff()
	{
		IsFixed = false;
	}

protected:

private:
	int Order = 0;
	float4 NumberScale = {};
	float4 Pos = {};
	int Value = 0;
	int TransColor = RGB(255, 0, 255);
	Align AlignState = Align::Left;

	bool IsFixed = false;

	bool CameraEffect = false;										//ī�޶� ����Ʈ ����

	bool Negative = false;											//���� ��ȣ

	int NumOfDigits = -1;											//������ �ϱ� ���� ������ �ڸ���

	std::string_view ImageName = std::string_view();
	std::string_view NegativeName = std::string_view();

	std::vector<GameEngineRender*> NumberRenders = std::vector<GameEngineRender*>();
	GameEngineRender* NegativeRender = nullptr;


	void SetNumberRenders(size_t _Index, int _TransColor, float4 _Pos, const std::string_view& _ImageName, float4 _Scale, bool _CameraEffect, int _Frame = -1);
};