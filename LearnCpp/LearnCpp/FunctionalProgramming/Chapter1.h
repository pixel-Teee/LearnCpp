#pragma once

#include <string>
#include <vector>

namespace FP {
	int count_lines(const std::string& filename);

	std::vector<int> count_lines_in_files(const std::vector<std::string>& files);
}