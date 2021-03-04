#ifndef MATH_HEADER
#define MATH_HEADER

class Math
{
public:
	~Math() {};

	inline static float ToDegrees(const float& someRadians) { return (180 / Pi) * someRadians; }
	inline static float ToRadians(const float& someDegrees) { return (Pi / 180) * someDegrees; }

	static constexpr double Pi = 3.14159265358979323846;

private:
	Math() {};
};
#endif