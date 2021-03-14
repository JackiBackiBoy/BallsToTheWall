#pragma once
#include <iostream>
class Random
{
public:
	static void RSeed();
	static float Float();
	static int Int(const int& min, const int& max);
private:
	static int seed1, seed2, seed3;

};

