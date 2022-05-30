#include "Chapter1.h"

#include <fstream>
#include <ranges>

namespace FP {

	auto count_lines(std::ifstream&& in)->int
	{
		//std::ifstream in(filename);

		return std::count(
			std::istreambuf_iterator<char>{in},
			std::istreambuf_iterator<char>{},
			'\n');
	}

	auto open_file(const std::string& filename)->std::ifstream
	{
		std::ifstream in{filename};
		return in;
	}

	std::vector<int> count_lines_in_files(const std::vector<std::string>& files)
	{
		//1
		//std::vector<int> results;
		//for (const auto& file : files) {
		//	results.push_back(count_lines(file));//save the results
		//}

		//return results;

		//2
		//std::vector<int> results(files.size());

		//std::transform(files.cbegin(), files.cend(),
		//				results.begin(),//save
		//				count_lines);//transform function

		//return results;

		//3
		//return files | std::ranges::views::transform(count_lines);

		//std::vector<int> v;

		auto res = files | std::views::transform(open_file) | std::views::transform(count_lines);

		return std::vector<int>(res.begin(), res.end());
	}
	
	
}