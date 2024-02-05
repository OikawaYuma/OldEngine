#include "CSVReader.h"

std::stringstream CSVReader::LoadFlle(const std::string& filePath)
{
	//ファイルを開く
	std::ifstream file;
	file.open(filePath);
	assert(file.is_open());

	// ファイルの内容を文字列ストリームにコピー
	std::stringstream Command;
	Command << file.rdbuf();

	// ファイルを閉じる
	file.close();
	return Command;
}