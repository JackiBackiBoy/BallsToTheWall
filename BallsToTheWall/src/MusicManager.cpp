#include "MusicManager.h"
#include <iostream>
#include <thread>
#include <SFML/System/Clock.hpp>
#include "Options.h"

sf::Music MusicManager::myMusic[2];
int MusicManager::myCurrentMusicIndex = 0;
float MusicManager::myTransitionTime = 2;
float MusicManager::myTransitionPercent = 0;
sf::Clock MusicManager::myTransitionThreadClock = sf::Clock();
bool MusicManager::myLoopingFlag = true;
bool MusicManager::myTransitioningFlag = false;

void MusicManager::TransitionTo(const std::string& aString)
{
	myTransitioningFlag = true;
	myCurrentMusicIndex = GetOtherMusicIndex();
	myMusic[myCurrentMusicIndex].setVolume(0);
	Start(aString);


	myTransitionPercent = 0;
	myTransitionThreadClock.restart();
	std::thread t1(TransitionThread);


	t1.join();

}

void MusicManager::TransitionThread()
{
	while (myTransitionPercent < 100)
	{
		myTransitionPercent += myTransitionThreadClock.restart().asSeconds() * 100 / myTransitionTime;
		myMusic[myCurrentMusicIndex].setVolume((myTransitionPercent/100) * Options::GetMusicVolume());
		myMusic[GetOtherMusicIndex()].setVolume((100 - myTransitionPercent) * Options::GetMusicVolume());
	}
	myMusic[myCurrentMusicIndex].setVolume(Options::GetMusicVolume());
	myTransitioningFlag = false;
}

void MusicManager::OnUpdate()
{
	if (myMusic[myCurrentMusicIndex].getVolume() != Options::GetMusicVolume() && !myTransitioningFlag)
	{
		myMusic[myCurrentMusicIndex].setVolume(Options::GetMusicVolume());
	}
}

void MusicManager::Stop()
{
	myMusic[myCurrentMusicIndex].stop();
}
void MusicManager::Start(const std::string& aString)
{
	myMusic[myCurrentMusicIndex].openFromFile("Assets/" + aString + ".wav");
	myMusic[myCurrentMusicIndex].setLoop(myLoopingFlag);
	myMusic[myCurrentMusicIndex].play();
}
void MusicManager::Pause()
{
	myMusic[myCurrentMusicIndex].pause();

}
void MusicManager::Resume()
{
	myMusic[myCurrentMusicIndex].play();
}

void MusicManager::SetLoopingFlag(const bool& aFlag)
{
	myLoopingFlag = aFlag;
	myMusic[myCurrentMusicIndex].setLoop(myLoopingFlag);
}

bool MusicManager::GetLoopingFlag()
{
	return myLoopingFlag;
}

int MusicManager::GetOtherMusicIndex()
{
	return (myCurrentMusicIndex == 0 ? 1 : 0);
}


