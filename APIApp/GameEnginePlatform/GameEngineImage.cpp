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

	BitMap = CreateCompatibleBitmap(GameEngineWindow::GetWindowBackBufferHdc(), _Scale.ix(), _Scale.iy());

	if (nullptr == BitMap)
	{
		MsgAssert("�̹��� ������ �����߽��ϴ�.");
		return false;
	}

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