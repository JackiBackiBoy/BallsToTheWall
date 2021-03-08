#include "Options.h"
//#include "data/SaveLoad.h"
#include "SFML/Audio.hpp"


float Options::myMasterVolume = 100;
float Options::myMusicVolume = 100;
float Options::mySoundEffectVolume = 100;

void Options::Load()
{
	////Defaults
	//if (SaveLoad::Load("MVol") == "")
	//	SaveLoad::Save("MVol", std::to_string(myMasterVolume));
	//if (SaveLoad::Load("SEffVol") == "")
	//	SaveLoad::Save("SEffVol", std::to_string(mySoundEffectVolume));
	//if (SaveLoad::Load("MusicVol") == "")
	//	SaveLoad::Save("MusicVol", std::to_string(myMusicVolume));



	//myMasterVolume = std::stof(SaveLoad::Load("MVol"));
	//mySoundEffectVolume = std::stof(SaveLoad::Load("SEffVol"));
	//myMusicVolume = std::stof(SaveLoad::Load("MusicVol"));
}

void Options::Save()
{
	//SaveLoad::Save("MVol", std::to_string(myMasterVolume));
	//SaveLoad::Save("SEffVol", std::to_string(mySoundEffectVolume));
	//SaveLoad::Save("MusicVol", std::to_string(myMusicVolume));
}

float Options::GetMasterVolume()
{
	return myMasterVolume;
}

float Options::GetMusicVolume()
{
	return myMusicVolume;
}

float Options::GetSoundEffectVolume()
{
	return mySoundEffectVolume;
}

void Options::SetMasterVolume(float aValue)
{
	myMasterVolume = aValue;
	sf::Listener::setGlobalVolume(aValue);
}

void Options::SetMusicVolume(float aValue)
{
	myMusicVolume = aValue;
}

void Options::SetSoundEffectVolume(float aValue)
{
	mySoundEffectVolume = aValue;
}
