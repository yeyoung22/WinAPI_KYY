#include "Monster.h"
#include "Player.h"


Monster::Monster() 
{
}

Monster::~Monster() 
{
}

void Monster::SetEffectSound(const std::string_view& _String, int _loop, float _BasicVolume)
{
	EffectPlayer = GameEngineResources::GetInst().SoundPlayToControl(_String);
	EffectPlayer.LoopCount(_loop);
	EffectPlayer.Volume(_BasicVolume);
}