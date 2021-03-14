#pragma once
#include <string>
#include <map>
#include <vector>
class SaveLoad
{
private:
	static std::string mySavePos;
	static std::string myAppdataString;
	static std::map<std::string, std::string> mySavedStrings;
	static void ReadSave();
	static bool myLoadedFlag;
public:
	static void Save(const std::string& aKey, const std::string& aValue);
	static std::string Load(const std::string& aKey);
};

