#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>
#include "GameEngineWindow.h"

//�ٸ� lib ���
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
		MsgAssert("�̹��� ������ �����߽��ϴ�. nullptr�� HDC�� �־�����ϴ�.");
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
		MsgAssert("ũ�Ⱑ 0�� �̹����� ���� ���� �����ϴ�");
		return false;
	}

	//1*1 �ܻ� ��Ʈ���� ���õ�						�ڵ�							�ʺ�				����
	BitMap = CreateCompatibleBitmap(GameEngineWindow::GetWindowBackBufferHdc(), _Scale.ix(), _Scale.iy());

	if (nullptr == BitMap)
	{
		MsgAssert("�̹��� ������ �����߽��ϴ�.");
		return false;
	}

	//������ ����̽��� ȣȯ�Ǵ� DC����
	//NULL�̸� ���� ȭ��� ȣȯ�Ǵ� �޸� DC����
	ImageDC = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC)
	{
		MsgAssert("�̹��� HDC ������ �����߽��ϴ�.");
		return false;
	}

	//ImageDC 1,1 �迭�� ���� 
	//�����찡 ó�� ��������� �־��� HDC�� 2���� �迭�� OldBitMap�� ����
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	ImageScaleCheck();

	ImageClear();

	return true;
}

bool GameEngineImage::ImageLoad(const GameEnginePath& _Path)
{
	//�̹����� �ε�
	return ImageLoad(_Path.GetPathToString().c_str());
}

bool GameEngineImage::ImageLoad(const std::string_view& _Path)
{

	//LoadImageA(hInstance, �ε��� �̹���, �̹��� ����, �ʺ� ����, �ȼ� ����, )
	//���� ������ �������Ƿ� ȭ�鿡 �׸��� ���ؼ��� �� DC�� ����� �����ؾ� ��
	//������ �����Ƿ� ȭ�鿡 �׸� ���� ���� ����
	//0, 0�̸� �̹��� �� �Ϻθ� �ε��ϴ� ���� �ƴ� ���� �ε�
	//LR_LOADFROMFILE ������ ���Ͽ������� �ε�

	// �̹����� �ε��� 2���� �迭�� ����
	// �����쿡�� new�� ������ �Ͱ� ����
	BitMap = static_cast<HBITMAP>(LoadImageA(nullptr, _Path.data(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	if (nullptr == BitMap)
	{
		std::string Path = _Path.data();
		MsgAssert(Path + " �̹��� �ε忡 �����߽��ϴ�.");
		return false;
	}

	//�׸��� ���� ����
	ImageDC = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC)
	{
		std::string Path = _Path.data();
		MsgAssert(Path + " �̹��� HDC ������ �����߽��ϴ�.");
		return false;
	}

	// ImageDC 1,1 �迭�� ����
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	ImageScaleCheck();

	return true;
}

void GameEngineImage::ImageScaleCheck()
{
	//HDC �ڵ��� �̿��� ���� ������ DC�� ���õ� �׷��� ��ü�� ���� ���� �˻�
	//GetCurrentBitMap(, OBJ_BITMAP)�� ���� ������ DC�� �������� BitMap ��ȯ
	HBITMAP CurrentBitMap = static_cast<HBITMAP>(GetCurrentObject(ImageDC, OBJ_BITMAP));
	//GetObject(���� ��� �ڵ�, ���ۿ� ����� ũ��, ������Ʈ ������ ���� ����ü ������ )
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info);
}

//Copy
void GameEngineImage::BitCopy(const GameEngineImage* _OtherImage, float4 _CenterPos, float4 _Scale)
{
	//�ȼ��� ���� �����͸� ��Ʈ ��� ���� ����
	//�̹��� ũ�� ���� �� ���� ����
	BitBlt(
		ImageDC,							//���� ���� �̹��� �ڵ�
		_CenterPos.ix() - _Scale.hix(),		//��ġ(�̹����� ���� ��ġ�� �߽ɺη�)
		_CenterPos.iy() - _Scale.hiy(),
		_Scale.ix(),						//�ʺ�
		_Scale.iy(),						//����
		_OtherImage->GetImageDC(),			//������ �̹���
		0,									//������ �̹����� x��ġ
		0,									//������ �̹����� y��ġ
		SRCCOPY								//SRCCOPY ���� �簢���� ��� �簢���� ���� ����
	);
}

void GameEngineImage::TransCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color)
{
	if (false == _OtherImage->IsCut)
	{
		MsgAssert("�߸��� ���� �̹����� cut��� �Լ��� ����Ϸ��� �߽��ϴ�.");
		return;
	}

	ImageCutData Data = _OtherImage->GetCutData(_CutIndex);

	TransCopy(_OtherImage, _CopyCenterPos, _CopySize, Data.GetStartPos(), Data.GetScale(), _Color);
}

void GameEngineImage::TransCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Color)
{
	//BitBlt���� ����� ����
	TransparentBlt(ImageDC,						//�̹����� �׷��� ���
		_CopyCenterPos.ix() - _CopySize.hix(),	//�׷��� ��ġ�� ����
		_CopyCenterPos.iy() - _CopySize.hiy(),
		_CopySize.ix(),							//�׷��� ũ���
		_CopySize.iy(),
		_OtherImage->GetImageDC(),
		_OtherImagePos.ix(),					//������ �̹��� x y��������
		_OtherImagePos.iy(),
		_OtherImageSize.ix(),					//������ �̹��� ũ��
		_OtherImageSize.iy(),
		_Color);								//�������� ó���� ������ �̹����� RGB ����
}

void GameEngineImage::AlphaCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color)
{
	if (false == _OtherImage->IsCut)
	{
		MsgAssert(" �߸��� ���� �̹����� cut��� �Լ��� ����Ϸ��� �߽��ϴ�.");
		return;
	}

	ImageCutData Data = _OtherImage->GetCutData(_CutIndex);

	AlphaCopy(_OtherImage, _CopyCenterPos, _CopySize, Data.GetStartPos(), Data.GetScale(), _Color);
}

void GameEngineImage::AlphaCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Alpha)
{
	BLENDFUNCTION BF;								//����ü

	BF.BlendOp = AC_SRC_OVER;						//�ҽ� ȥ�� �۾�
	BF.BlendFlags = 0;								//0�̾�� ����
	BF.SourceConstantAlpha = _Alpha;				//���� ��Ʈ�ʿ� ����� ���� ���� �� ���� (Alpha = 255: ������)
	BF.AlphaFormat = AC_SRC_ALPHA;					//���� ��Ʈ���� �ؼ��Ǵ� ���

	AlphaBlend(ImageDC,								//�׸��� ����
		_CopyCenterPos.ix() - _CopySize.hix(),		//���� ��ġ
		_CopyCenterPos.iy() - _CopySize.hiy(),
		_CopySize.ix(),								//ũ��
		_CopySize.iy(),
		_OtherImage->GetImageDC(),
		_OtherImagePos.ix(),						//������ �̹��� x y��������
		_OtherImagePos.iy(),
		_OtherImageSize.ix(),						//������ �̹��� ũ��
		_OtherImageSize.iy(),
		BF);										//���� ��Ʈ�ʿ� ���� ���� ȥ�� �Լ�
}

void GameEngineImage::Cut(int _X, int _Y)
{
	ImageCutData Data;

	//�̹����� ���η� _X��ŭ, ���η� _Y��ŭ �ڸ�
	Data.SizeX = static_cast<float>(GetImageScale().ix() / _X);
	Data.SizeY = static_cast<float>(GetImageScale().iy() / _Y);

	for (size_t i = 0; i < _Y; i++)
	{
		for (size_t i = 0; i < _X; i++)
		{
			//�ڸ� �̹����� ����
			ImageCutDatas.push_back(Data);
			Data.StartX += Data.SizeX;
		}
		//�� �� �ڸ��� StartX�� ��ġ�� �ٽ� 0(�̹����� X�� ������ġ)
		Data.StartX = 0.0f;
		Data.StartY += Data.SizeY;
	}

	//�ٵ������ ǥ��
	IsCut = true;
}

void GameEngineImage::Cut(float4 _Start, float4 _End, int _X, int _Y)
{
	ImageCutData Data;

	//End-Start�� ���� �ʺ� �� ����
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

//( x, y ) ��ġ������ ���� ������ �������� �Լ�
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


	return GetPixel(ImageDC, _X, _Y);								//������ ��ǥ������ RGB �� �˻�
}