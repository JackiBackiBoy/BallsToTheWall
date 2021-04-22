#include "SaveLoad.h"
#include <iostream>
#include <fstream>
#include <sstream>


std::map<std::string, std::string> SaveLoad::mySavedStrings = std::map<std::string, std::string>();
bool SaveLoad::myLoadedFlag = false;
std::string SaveLoad::myAppdataString = "";
std::string SaveLoad::mySavePos = "/BallsToTheWallSave.txt";

void SaveLoad::ReadSave()
{
	if (myAppdataString == "")
	{
		char* pValue;
		size_t len;
		errno_t err = _dupenv_s(&pValue, &len, "APPDATA");
		myAppdataString = (std::string)pValue;
		delete(pValue);
	}

	mySavedStrings.clear();

	std::string text;
	std::ifstream tempFile;
	tempFile.open(myAppdataString + mySavePos);
	std::string tempSegment;
	std::vector<std::string> tempSplit;

	while (std::getline(tempFile, tempSegment, ';'))
	{
		tempSplit.push_back(tempSegment);
	}
	std::vector<std::string> tempSplit2;
	for (std::string s : tempSplit)
	{
		tempSplit2.clear();
		std::stringstream tempSs = (std::stringstream)s;
		while (std::getline(tempSs, tempSegment, ':'))
		{
			tempSplit2.push_back(tempSegment);
		}
		mySavedStrings.emplace(tempSplit2[0], tempSplit2[1]);
	}
	myLoadedFlag = true;
}

void SaveLoad::Save(const std::string& aKey, const std::string& aValue)
{
	if (myAppdataString == "")
	{
		char* pValue;
		size_t len;
		errno_t err = _dupenv_s(&pValue, &len, "APPDATA");
		myAppdataString = (std::string)pValue;
		delete(pValue);
	}

	if (!myLoadedFlag)
		ReadSave();


	std::ofstream tempFile;

	tempFile.open(myAppdataString + mySavePos);//std::ios_base::app to not override
	if (mySavedStrings.find(aKey) != mySavedStrings.end())
	{
		mySavedStrings[aKey] = aValue;
	}
	else
	{
		mySavedStrings.emplace(aKey, aValue);
	}
	for (std::pair<std::string, std::string> pair : mySavedStrings)
	{
		tempFile << pair.first + ":" + pair.second + ";";
	}

	tempFile.close();
}

std::string SaveLoad::Load(const std::string& aKey)
{
	if (myAppdataString == "")
	{
		char* pValue;
		size_t len;
		errno_t err = _dupenv_s(&pValue, &len, "APPDATA");
		myAppdataString = (std::string)pValue;
	}
	if (!myLoadedFlag)
		ReadSave();
	if (mySavedStrings.find(aKey) != mySavedStrings.end())
	{
		return mySavedStrings[aKey];
	}
	else
	{
		return "";
	}
}



