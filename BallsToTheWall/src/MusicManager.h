#pragma once
#include <string>
#include "SFML/Audio.hpp"

class MusicManager
{
public:
	static void TransitionTo(std::string aString);
	static void Stop();
	static void Start(std::string aString);
	static void Pause();
	static void Resume();
	static void SetLoopingFlag(bool aFlag);
	static bool GetLoopingFlag();
	static void OnUpdate();
private:
	static void TransitionThread();
	static sf::Music myMusic[];
	static int myCurrentMusicIndex;
	static float myTransitionPercent;
	static bool myTransitioningFlag;
	static int GetOtherMusicIndex();
	static float myTransitionTime;
	static sf::Clock myTransitionThreadClock;
	static bool myLoopingFlag;
};

