#pragma once
class Options
{
public:
	static void Load();
	static void Save();
	static float GetMasterVolume();
	static float GetMusicVolume();
	static float GetSoundEffectVolume();
	static void SetMasterVolume(float aValue);
	static void SetMusicVolume(float aValue);
	static void SetSoundEffectVolume(float aValue);
private:
	static float myMasterVolume;
	static float myMusicVolume;
	static float mySoundEffectVolume;

};

