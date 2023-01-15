#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>
#include "GameEngineWindow.h"

// �ٸ� lib ���
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

void GameEngineImage::ImageClear()
{
	Rectangle(ImageDC, 0, 0, Info.bmWidth, Info.bmHeight);
}


void GameEngineImage::ImageScaleCheck()
{
	//HDC �ڵ��� �̿��� ���� ������ DC�� ���õ� �׷��� ��ü�� ���� ���� �˻�
	//GetCurrentBitMap(, OBJ_BITMAP)�� ���� ������ DC�� �������� BitMap ��ȯ
	HBITMAP CurrentBitMap = static_cast<HBITMAP>(GetCurrentObject(ImageDC, OBJ_BITMAP));
	//GetObject(���� ��� �ڵ�, ���ۿ� ����� ũ��, ������Ʈ ������ ���� ����ü ������ )
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info);
}


bool GameEngineImage::ImageLoad(const GameEnginePath& _Path)
{
	return ImageLoad(_Path.GetPathToString().c_str());
}

bool GameEngineImage::ImageLoad(const std::string_view& _Path)
{

	//LoadImageA(hInstance, �ε��� �̹���, �̹��� ����, �ʺ� ����, �ȼ� ����, )
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

//Copy
void GameEngineImage::BitCopy(const GameEngineImage* _OtherImage, float4 _Pos, float4 _Scale)
{
	//�ȼ��� ���� ������ ��Ʈ ��� ���� ����
	BitBlt(
		ImageDC,						//���� ���� �̹��� �ڵ�
		_Pos.ix(),						//��ġ
		_Pos.iy(),
		_Scale.ix(),					//�ʺ�
		_Scale.iy(),					//����
		_OtherImage->GetImageDC(),		//������ �̹���
		0,								//������ �̹����� x��ġ
		0,								//������ �̹����� y��ġ
		SRCCOPY							//SRCCOPY ���� �簢���� ��� �簢���� ���� ����
	);
}

void GameEngineImage::TransCopy(const GameEngineImage* _OtherImage, float4 _CopyPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Color)
{
	// �⺻���� �Լ��� �ƴմϴ�.
	//TransparentBlt(ImageDC,
	//	_CopyPos.ix(),
	//	_CopyPos.iy(),
	//	_CopySize.ix(),
	//	_CopySize.iy(),
	//	_OtherImage->GetImageDC(),
	//	_OtherImagePos.ix(),
	//	_OtherImagePos.iy(),
	//	_OtherImageSize.ix(),
	//	_OtherImageSize.iy(),
	//	_Color);

	TransparentBlt(ImageDC,
		_CopyPos.ix(),
		_CopyPos.iy(),
		100,
		100,
		_OtherImage->GetImageDC(),
		0,
		0,
		100,
		100,
		_Color);					//�������� ó���� ������ �̹����� RGB ����
}