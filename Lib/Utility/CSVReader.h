#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>


class CSVReader
{
public:

	/// <summary>
	/// CSVファイルを開く
	/// </summary>
	/// <param name="filePath">ファイル名</param>
	std::stringstream LoadFlle(const std::string& filePath);
};

