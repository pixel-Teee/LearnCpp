#include "Chapter1.h"

#include <fstream>
#include <ranges>

namespace FP {

	int count_lines(const std::string& filename)
	{
		std::ifstream in(filename);

		return std::count(
			std::istreambuf_iterator<char>(in),
			std::istreambuf_iterator<char>(),
			'\n');
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

		auto res = files | std::views::transform(count_lines);

		return std::vector<int>(res.begin(), res.end());
		//return v;
	}
	
	
}