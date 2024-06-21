#include "Loder.h"
#include "json.hpp"
#include <fstream>
#include <cassert>


void Loder::LoadJsonFile(const std::string kDefaultBaseDirectory, const std::string fileName)
{
	// 連結してフルパスを得る
	const std::string fullpath = kDefaultBaseDirectory + fileName + ".json";

	// ファイルストリーム
	std::ifstream file;

	// ファイルを開く
	file.open(fullpath);
	// ファイルオープン失敗をチェック
	if (file.fail()) {
		assert(0);
	}
	
}
