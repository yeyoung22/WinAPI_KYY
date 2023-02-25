#include "GameEngineSound.h"
#include <GameEngineBase/GameEngineDebug.h>


//다른 lib나 dll을 사용하기 위한 전처리문
//lib를 통해 dll을 사용하는 것은 fmod.dll을 쓰는 것
#ifdef _DEBUG																		
#pragma comment(lib, "GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmodL_vc.lib")				//Debug Mode
#else
#pragma comment(lib, "GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmod_vc.lib")
#endif

//FMOD의 기능을 사용하기 위한 클래스의 포인터(WinAPI의 HDC와 유사)
FMOD::System* SoundSystem = nullptr;

class SoundSystemCreator
{
public:
	SoundSystemCreator()
	{
		FMOD::System_Create(&SoundSystem);

		if (nullptr == SoundSystem)
		{
			MsgAssert("사운드 초기화가 제대로 되지 않았습니다.");
		}

		//                                     option
		if (FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))				//시스템 초기화: Channel을 32개 까지 사용
		{
			MsgAssert("사운드 시스템 이니셜라이즈에 실패했습니다.");
		}
	}

	~SoundSystemCreator()
	{
		SoundSystem->release();
	}
};

SoundSystemCreator SoundInitObject = SoundSystemCreator();							//사운드 시스템 객체 생성

void GameEngineSound::SoundUpdate()
{
	if (nullptr == SoundSystem)
	{
		MsgAssert("사운드 업데이트가 불가능합니다.");
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
	// _Path.data() 파일로 사운드 생성
	//															option				   const 아니므로 값을 넣어주면 그 값이 바뀔 수 있음
	if (FMOD_OK != SoundSystem->createSound(_Path.data(), FMOD_LOOP_NORMAL, nullptr, &FMODSound))		
	{
		MsgAssert(std::string("사운드 로드에 실패했습니다.\n 경로 : ") + _Path.data());
	}

	return;
}

FMOD::Channel* GameEngineSound::Play()
{
	if (nullptr == FMODSound)
	{
		MsgAssert(std::string("FMODSound가 nullptr 입니다 "));
	}

	FMOD::Channel* Return;

	SoundSystem->playSound(FMODSound, nullptr, false, &Return);

	return Return;
}

