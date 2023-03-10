#pragma once
#include <Windows.h>
#include <string_view>
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineDebug.h>

struct ImageCutData
{
	float StartX = 0.0f;	//사용할 이미지의 좌측상단 지점(시작점)
	float StartY = 0.0f;
	//사용하고 싶은 이미지의 크기
	float SizeX = 0.0f;		//지정한 시작점에서의 너비(X)
	float SizeY = 0.0f;		//지정한 시작점에서의 높이(Y)

	float4 GetStartPos()
	{
		return { StartX, StartY };
	}

	float4 GetScale()
	{
		return { SizeX, SizeY };
	}
};

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

	bool ImageLoad(const GameEnginePath& _Path);

	bool ImageLoad(const std::string_view& _Path);

	void ImageClear();

	HDC GetImageDC() const
	{
		return ImageDC;
	}

	//Imagedml 너비, 높이 정보를 반환
	float4 GetImageScale() const
	{
		return float4{ static_cast<float>(Info.bmWidth), static_cast<float>(Info.bmHeight) };
	}

	//이미지 자를 수 있는지
	bool IsImageCutting()
	{
		return IsCut;
	}

	//잘린 이미지 개수 반환
	size_t GetImageCuttingCount()
	{
		return ImageCutDatas.size();
	}

	bool IsCutIndexValid(int _Index) const
	{
		if (0 > _Index)
		{
			return false;
		}

		if (ImageCutDatas.size() <= _Index)
		{
			return false;
		}

		return true;
	}


	ImageCutData GetCutData(int _Index) const
	{
		if (false == IsCutIndexValid(_Index))
		{
			MsgAssert("유효하지 않은 컷 인덱스 입니다.");
		}

		return ImageCutDatas[_Index];
	}
	
	//이미지 자르는 함수
	//지정한 부분에서 지정한 만큼 자름
	void Cut(float4 _Start, float4 _End, int _X, int _Y);

	//자를 이미지 가로, 세로
	void Cut(int _X, int _Y);

	void BitCopy(const GameEngineImage* _OtherImage, float4 _CenterPos, float4 _Scale);

	//랜더링 제외할 컬러 지정 가능
	void TransCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Color = RGB(255, 0, 255));

	void TransCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color = RGB(255, 0, 255));

	//Alpha 블랜드 함수
	void AlphaCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Alpha);

	void AlphaCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color);
	
	//이미지 회전 함수, 회전을 위한 별도의 이미지가 한 장 더 필요
	void PlgCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, float _Angle, GameEngineImage* _FilterImage);

	void PlgCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, float _Angle, GameEngineImage* _FilterImage);

	
	DWORD GetPixelColor(float4 _Pos, DWORD _OutColor);

	DWORD GetPixelColor(int _X, int _Y, DWORD _OutColor);

protected:

private:
	HDC ImageDC = nullptr;
	HBITMAP BitMap = nullptr;
	HBITMAP OldBitMap = nullptr;
	BITMAP Info = BITMAP();
	bool IsCut = false;

	std::vector<ImageCutData> ImageCutDatas;

	void ImageScaleCheck();
};

