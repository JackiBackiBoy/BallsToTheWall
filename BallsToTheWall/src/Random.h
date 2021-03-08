#pragma once
#include <iostream>
class Random
{
public:
	static void RSeed();
	static float Float();
	static int Int(int min, int max);
private:
	static int seed1, seed2, seed3;

};

