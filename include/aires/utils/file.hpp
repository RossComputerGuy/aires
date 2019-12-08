#pragma once

#include <string>

namespace Aires {
	namespace Utils {
		class FileUtils {
			public:
				static std::string readFile(const char* path);
		};
	};
};
