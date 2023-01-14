#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>
#include "GameEngineWindow.h"

GameEngineImage::GameEngineImage() 
{
}

GameEngineImage::~GameEngineImage() 
{
}

bool GameEngineImage::ImageCreate(HDC _Hdc)
{
	if (nullptr == _Hdc)
	{
		MsgAssert("이미지 생성에 실패했습니다. nullptr인 HDC를 넣어줬습니다.");
		return false;
	}

	ImageDC = _Hdc;
	ImageScaleCheck();

	return true;
}

bool GameEngineImage::ImageCreate(const float4& _Scale)
{
	if (true == _Scale.IsZero())
	{
		MsgAssert("크기가 0인 이미지를 만들 수는 없습니다");
		return false;
	}

	BitMap = CreateCompatibleBitmap(GameEngineWindow::GetWindowBackBufferHdc(), _Scale.ix(), _Scale.iy());

	if (nullptr == BitMap)
	{
		MsgAssert("이미지 생성에 실패했습니다.");
		return false;
	}

	ImageDC = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC)
	{
		MsgAssert("이미지 HDC 생성에 실패했습니다.");
		return false;
	}

	//ImageDC 1,1 배열과 연결 
	//윈도우가 처음 만들어질때 주어진 HDC와 2차원 배열을 OldBitMap에 넣음
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	ImageScaleCheck();

	ImageClear();

	return true;
}

void GameEngineImage::ImageClear()
{
	Rectangle(ImageDC, 0, 0, Info.bmWidth, Info.bmHeight);
}


void GameEngineImage::ImageScaleCheck()
{
	//HDC 핸들을 이용해 현재 지정된 DC에 선택된 그래픽 개체에 대한 설명 검색
	//GetCurrentBitMap(, OBJ_BITMAP)은 현재 지정된 DC를 바탕으로 BitMap 반환
	HBITMAP CurrentBitMap = static_cast<HBITMAP>(GetCurrentObject(ImageDC, OBJ_BITMAP));
	//GetObject(조사 대상 핸들, 버퍼에 기록할 크기, 오브젝트 정보를 받을 구조체 포인터 )
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info);
}