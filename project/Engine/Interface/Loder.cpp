#include "Loder.h"
#include "json.hpp"
#include <fstream>
#include <cassert>


void Loder::LoadJsonFile(const std::string kDefaultBaseDirectory, const std::string fileName)
{
	// 連結してフルパスを得る
	const std::string fullpath = kDefaultBaseDirectory +"/" + fileName + ".json";

	// ファイルストリーム
	std::ifstream file;

	// ファイルを開く
	file.open(fullpath);
	// ファイルオープン失敗をチェック
	if (file.fail()) {
		assert(0);
	}

	// Json文字列から回答したデータ
	nlohmann::json deserialized;

	// 解凍
	file >> deserialized;

	// 正しいレベルデータファイルかチェック
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());

	// "name"を文字列として取得
	std::string name =
		deserialized["name"].get<std::string>();
	// 正しいレベルデータファイル化チェック
	assert(name.compare("scene") == 0);
	
}
