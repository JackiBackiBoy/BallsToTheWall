#pragma once
class Options
{
public:
	static void Load();
	static void Save();
	static float GetMasterVolume();
	static float GetMusicVolume();
	static float GetSoundEffectVolume();
	static void SetMasterVolume(const float& aValue);
	static void SetMusicVolume(const float& aValue);
	static void SetSoundEffectVolume(const float& aValue);
private:
	static float myMasterVolume;
	static float myMusicVolume;
	static float mySoundEffectVolume;

};

