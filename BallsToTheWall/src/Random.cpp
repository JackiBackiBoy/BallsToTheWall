#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "Random.h"
#include <time.h>

int Random::seed1 = 100;
int Random::seed2 = 100;
int Random::seed3 = 100;

void Random::RSeed() 
{
	seed1 = time(NULL) % 30269;
	Sleep(seed1 % 23);
	seed2 = time(NULL) % 30307;
	Sleep(seed2 % 27);
	seed3 = time(NULL) % 30323;
}

float Random::Float()
{
	seed1 = (171 * seed1) % 30269;
	seed2 = (172 * seed2) % 30307;
	seed3 = (170 * seed3) % 30323;
	return std::fmod(seed1 / 30269.f + seed2 / 30307.f + seed3 / 30323.f, 1);
}

int Random::Int(const int& min, const int& max) 
{
	return (max - min) * Float() + min;
}
