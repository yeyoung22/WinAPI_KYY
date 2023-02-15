#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>
#include "GameEngineWindow.h"

//다른 lib 사용
#pragma comment(lib, "msimg32.lib")

GameEngineImage::GameEngineImage() 
{
}

GameEngineImage::~GameEngineImage() 
{
	if (nullptr != BitMap)
	{
		DeleteObject(BitMap);
		BitMap = nullptr;
	}

	if (nullptr != OldBitMap)
	{
		DeleteObject(OldBitMap);
		OldBitMap = nullptr;
	}

	if (nullptr != ImageDC)
	{
		DeleteDC(ImageDC);
		ImageDC = nullptr;
	}
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

void GameEngineImage::ImageClear()
{
	Rectangle(ImageDC, 0, 0, Info.bmWidth, Info.bmHeight);
}

bool GameEngineImage::ImageCreate(const float4& _Scale)
{
	if (true == _Scale.IsZero())
	{
		MsgAssert("크기가 0인 이미지를 만들 수는 없습니다");
		return false;
	}

	//1*1 단색 비트맵이 선택됨						핸들							너비				높이
	BitMap = CreateCompatibleBitmap(GameEngineWindow::GetWindowBackBufferHdc(), _Scale.ix(), _Scale.iy());

	if (nullptr == BitMap)
	{
		MsgAssert("이미지 생성에 실패했습니다.");
		return false;
	}

	//지정된 디바이스와 호환되는 DC생성
	//NULL이면 현재 화면과 호환되는 메모리 DC생성
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

bool GameEngineImage::ImageLoad(const GameEnginePath& _Path)
{
	//이미지만 로드
	return ImageLoad(_Path.GetPathToString().c_str());
}

bool GameEngineImage::ImageLoad(const std::string_view& _Path)
{

	//LoadImageA(hInstance, 로드할 이미지, 이미지 형식, 너비 단위, 픽셀 단위, )
	//색상 정보만 가져오므로 화면에 그리기 위해서는 빈 DC를 만들고 연결해야 함
	//권한이 없으므로 화면에 그릴 수는 없는 상태
	//0, 0이면 이미지 중 일부만 로드하는 것이 아닌 전부 로드
	//LR_LOADFROMFILE 지정된 파일에서부터 로드

	// 이미지를 로드한 2차원 배열의 정보
	// 윈도우에게 new를 지시한 것과 같음
	BitMap = static_cast<HBITMAP>(LoadImageA(nullptr, _Path.data(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	if (nullptr == BitMap)
	{
		std::string Path = _Path.data();
		MsgAssert(Path + " 이미지 로드에 실패했습니다.");
		return false;
	}

	//그리기 권한 생성
	ImageDC = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC)
	{
		std::string Path = _Path.data();
		MsgAssert(Path + " 이미지 HDC 생성에 실패했습니다.");
		return false;
	}

	// ImageDC 1,1 배열과 연결
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	ImageScaleCheck();

	return true;
}

void GameEngineImage::ImageScaleCheck()
{
	//HDC 핸들을 이용해 현재 지정된 DC에 선택된 그래픽 개체에 대한 설명 검색
	//GetCurrentBitMap(, OBJ_BITMAP)은 현재 지정된 DC를 바탕으로 BitMap 반환
	HBITMAP CurrentBitMap = static_cast<HBITMAP>(GetCurrentObject(ImageDC, OBJ_BITMAP));
	//GetObject(조사 대상 핸들, 버퍼에 기록할 크기, 오브젝트 정보를 받을 구조체 포인터 )
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info);
}

//Copy
void GameEngineImage::BitCopy(const GameEngineImage* _OtherImage, float4 _CenterPos, float4 _Scale)
{
	//픽셀의 색상 데이터를 비트 블록 전송 수행
	//이미지 크기 조절 및 색상 복사
	BitBlt(
		ImageDC,							//복사 당할 이미지 핸들
		_CenterPos.ix() - _Scale.hix(),		//위치(이미지의 기준 위치를 중심부로)
		_CenterPos.iy() - _Scale.hiy(),
		_Scale.ix(),						//너비
		_Scale.iy(),						//높이
		_OtherImage->GetImageDC(),			//복사할 이미지
		0,									//복사할 이미지의 x위치
		0,									//복사할 이미지의 y위치
		SRCCOPY								//SRCCOPY 원본 사각형을 대상 사각형에 직접 복사
	);
}

void GameEngineImage::TransCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color)
{
	if (false == _OtherImage->IsCut)
	{
		MsgAssert("잘리지 않은 이미지로 cut출력 함수를 사용하려고 했습니다.");
		return;
	}

	ImageCutData Data = _OtherImage->GetCutData(_CutIndex);

	TransCopy(_OtherImage, _CopyCenterPos, _CopySize, Data.GetStartPos(), Data.GetScale(), _Color);
}

void GameEngineImage::TransCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Color)
{
	//BitBlt보다 기능이 많음
	TransparentBlt(ImageDC,						//이미지가 그려질 대상
		_CopyCenterPos.ix() - _CopySize.hix(),	//그려질 위치의 시작
		_CopyCenterPos.iy() - _CopySize.hiy(),
		_CopySize.ix(),							//그려질 크기로
		_CopySize.iy(),
		_OtherImage->GetImageDC(),
		_OtherImagePos.ix(),					//복사할 이미지 x y에서부터
		_OtherImagePos.iy(),
		_OtherImageSize.ix(),					//복사할 이미지 크기
		_OtherImageSize.iy(),
		_Color);								//투명으로 처리할 복사할 이미지의 RGB 색상
}

void GameEngineImage::AlphaCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color)
{
	if (false == _OtherImage->IsCut)
	{
		MsgAssert(" 잘리지 않은 이미지로 cut출력 함수를 사용하려고 했습니다.");
		return;
	}

	ImageCutData Data = _OtherImage->GetCutData(_CutIndex);

	AlphaCopy(_OtherImage, _CopyCenterPos, _CopySize, Data.GetStartPos(), Data.GetScale(), _Color);
}

void GameEngineImage::AlphaCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Alpha)
{
	BLENDFUNCTION BF;								//구조체

	BF.BlendOp = AC_SRC_OVER;						//소스 혼합 작업
	BF.BlendFlags = 0;								//0이어야 동작
	BF.SourceConstantAlpha = _Alpha;				//원본 비트맵에 사용할 알파 투명도 값 지정 (Alpha = 255: 불투명)
	BF.AlphaFormat = AC_SRC_ALPHA;					//원본 비트맵이 해석되는 방식

	AlphaBlend(ImageDC,								//그리기 권한
		_CopyCenterPos.ix() - _CopySize.hix(),		//시작 위치
		_CopyCenterPos.iy() - _CopySize.hiy(),
		_CopySize.ix(),								//크기
		_CopySize.iy(),
		_OtherImage->GetImageDC(),
		_OtherImagePos.ix(),						//복사할 이미지 x y에서부터
		_OtherImagePos.iy(),
		_OtherImageSize.ix(),						//복사할 이미지 크기
		_OtherImageSize.iy(),
		BF);										//원본 비트맵에 대한 알파 혼합 함수
}

void GameEngineImage::Cut(int _X, int _Y)
{
	ImageCutData Data;

	//이미지를 가로로 _X만큼, 세로로 _Y만큼 자름
	Data.SizeX = static_cast<float>(GetImageScale().ix() / _X);
	Data.SizeY = static_cast<float>(GetImageScale().iy() / _Y);

	for (size_t i = 0; i < _Y; i++)
	{
		for (size_t i = 0; i < _X; i++)
		{
			//자른 이미지를 담음
			ImageCutDatas.push_back(Data);
			Data.StartX += Data.SizeX;
		}
		//한 줄 자르면 StartX의 위치는 다시 0(이미지의 X값 시작위치)
		Data.StartX = 0.0f;
		Data.StartY += Data.SizeY;
	}

	//다듬어졌음 표시
	IsCut = true;
}

void GameEngineImage::Cut(float4 _Start, float4 _End, int _X, int _Y)
{
	ImageCutData Data;

	//End-Start는 각각 너비 및 높이
	Data.SizeX = static_cast<float>((_End.x - _Start.x) / _X);
	Data.SizeY = static_cast<float>((_End.y - _Start.y) / _Y);

	Data.StartX = _Start.x;
	Data.StartY = _Start.y;

	for (size_t i = 0; i < _Y; i++)
	{
		for (size_t i = 0; i < _X; i++)
		{
			ImageCutDatas.push_back(Data);
			Data.StartX += Data.SizeX;
		}

		Data.StartX = _Start.x;
		Data.StartY += Data.SizeY;
	}

	IsCut = true;
}

DWORD GameEngineImage::GetPixelColor(float4 _Pos, DWORD _OutColor)
{
	return GetPixelColor(_Pos.ix(), _Pos.iy(), _OutColor);
}

//( x, y ) 위치에서의 색상 정보를 가져오는 함수
DWORD GameEngineImage::GetPixelColor(int _X, int _Y, DWORD _OutColor)
{
	//OutColor: 
	if (_X < 0)
	{
		return _OutColor;
	}
	if (_X >= GetImageScale().ix())
	{
		return _OutColor;
	}
	if (_Y < 0)
	{
		return _OutColor;
	}
	if (_Y >= GetImageScale().iy())
	{
		return _OutColor;
	}


	return GetPixel(ImageDC, _X, _Y);								//지정된 좌표에서의 RGB 값 검색
}