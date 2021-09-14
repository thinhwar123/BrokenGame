#include "SoundEffect.h"
#include <windows.h>
#include <mmsystem.h>

SoundEffect::SoundEffect()
{

}

SoundEffect::~SoundEffect()
{

}

void SoundEffect::Play(int i)
{
	switch (i)
	{
	case 0:
		PlaySound("sss1.wav", NULL, SND_ASYNC || SND_LOOP);
		break;
	case 1:
		PlaySound("ddd1.wav", NULL, SND_ASYNC || SND_LOOP);
		break;
	default:
		break;
	}

}
