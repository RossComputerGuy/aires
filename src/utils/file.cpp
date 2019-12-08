#include <aires/utils/file.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace Aires::Utils;

std::string FileUtils::readFile(const char* path) {
	std::ifstream file(path);
	std::string str;

	file.seekg(0, std::ios::end);
	str.reserve(file.tellg());
	file.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	return str;
}
