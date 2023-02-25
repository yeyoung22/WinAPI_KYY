#include "GameEngineSound.h"
#include <GameEngineBase/GameEngineDebug.h>


//�ٸ� lib�� dll�� ����ϱ� ���� ��ó����
//lib�� ���� dll�� ����ϴ� ���� fmod.dll�� ���� ��
#ifdef _DEBUG																		
#pragma comment(lib, "GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmodL_vc.lib")				//Debug Mode
#else
#pragma comment(lib, "GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmod_vc.lib")
#endif

//FMOD�� ����� ����ϱ� ���� Ŭ������ ������(WinAPI�� HDC�� ����)
FMOD::System* SoundSystem = nullptr;

class SoundSystemCreator
{
public:
	SoundSystemCreator()
	{
		FMOD::System_Create(&SoundSystem);

		if (nullptr == SoundSystem)
		{
			MsgAssert("���� �ʱ�ȭ�� ����� ���� �ʾҽ��ϴ�.");
		}

		//                                     option
		if (FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))				//�ý��� �ʱ�ȭ: Channel�� 32�� ���� ���
		{
			MsgAssert("���� �ý��� �̴ϼȶ���� �����߽��ϴ�.");
		}
	}

	~SoundSystemCreator()
	{
		SoundSystem->release();
	}
};

SoundSystemCreator SoundInitObject = SoundSystemCreator();							//���� �ý��� ��ü ����

void GameEngineSound::SoundUpdate()
{
	if (nullptr == SoundSystem)
	{
		MsgAssert("���� ������Ʈ�� �Ұ����մϴ�.");
		return;
	}

	SoundSystem->update();
}


GameEngineSound::GameEngineSound() 
{
}

GameEngineSound::~GameEngineSound() 
{
}

void GameEngineSound::SoundLoad(const std::string_view& _Path)
{ 
	// _Path.data() ���Ϸ� ���� ����
	//															option				   const �ƴϹǷ� ���� �־��ָ� �� ���� �ٲ� �� ����
	if (FMOD_OK != SoundSystem->createSound(_Path.data(), FMOD_LOOP_NORMAL, nullptr, &FMODSound))		
	{
		MsgAssert(std::string("���� �ε忡 �����߽��ϴ�.\n ��� : ") + _Path.data());
	}

	return;
}

FMOD::Channel* GameEngineSound::Play()
{
	if (nullptr == FMODSound)
	{
		MsgAssert(std::string("FMODSound�� nullptr �Դϴ� "));
	}

	FMOD::Channel* Return;

	SoundSystem->playSound(FMODSound, nullptr, false, &Return);

	return Return;
}

