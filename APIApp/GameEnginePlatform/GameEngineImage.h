#pragma once
#include <Windows.h>
#include <string_view>
#include <GameEngineBase/GameEngineMath.h>

// 설명 :
class GameEnginePath;
class GameEngineImage
{
public:
	// constrcuter destructer
	GameEngineImage();
	~GameEngineImage();

	// delete Function
	GameEngineImage(const GameEngineImage& _Other) = delete;
	GameEngineImage(GameEngineImage&& _Other) noexcept = delete;
	GameEngineImage& operator=(const GameEngineImage& _Other) = delete;
	GameEngineImage& operator=(GameEngineImage&& _Other) noexcept = delete;

	//이미지 생성
	bool ImageCreate(HDC _Hdc);

	bool ImageCreate(const float4& _Scale);


	void ImageClear();

protected:

private:
	HDC ImageDC = nullptr;
	HBITMAP BitMap = nullptr;
	HBITMAP OldBitMap = nullptr;
	BITMAP Info = BITMAP();

	void ImageScaleCheck();
};

