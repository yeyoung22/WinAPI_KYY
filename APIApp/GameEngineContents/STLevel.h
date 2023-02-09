#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
class STLevel :public GameEngineLevel
{
public:
	// constrcuter destructer
	STLevel();
	~STLevel();

	// delete Function
	STLevel(const STLevel& _Other) = delete;
	STLevel(STLevel&& _Other) noexcept = delete;
	STLevel& operator=(const STLevel& _Other) = delete;
	STLevel& operator=(STLevel&& _Other) noexcept = delete;

public:
	//ī�޶� ũ�� ��ȯ
	inline float4 GetCameraScale()
	{
		return CameraScale;
	}
	//ī�޶� ũ�� ����
	inline void SetCameraScale(float4 _Scale)
	{
		CameraScale = _Scale;
	}

protected:

private:
	float4 CameraScale;
};