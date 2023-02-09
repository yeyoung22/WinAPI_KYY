#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 설명 :
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
	//카메라 크기 반환
	inline float4 GetCameraScale()
	{
		return CameraScale;
	}
	//카메라 크기 설정
	inline void SetCameraScale(float4 _Scale)
	{
		CameraScale = _Scale;
	}

protected:

private:
	float4 CameraScale;
};