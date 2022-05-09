#include "LearnConcept.h"

#include <iostream>
#include <list>
#include <array>
#include <ranges>
#include <any>
#include <string>

namespace TP {

	void test()
	{
		std::vector<int> a{ 4, 2, 1, 3 };

		Sort(a);

		//std::list<int> a{ 4, 2, 1, 3 };
		//Sort(a);

		std::cout << iterable(std::vector<int>()) << std::endl;

		std::array b{ 4, 2, 1, 3 };
		b = sorted(b);
		for (const auto& elem : b) {
			std::cout << elem << " ";
		}

		for (auto i : std::ranges::views::iota(0, 10))
			std::cout << i << std::endl;

		auto ints = std::views::iota(0, 10);
		auto even = [](int i) { return 0 == i % 2;  };
		auto square = [](int i) { return i * i;  };
		
		for (int i : (ints | std::views::filter(even) | std::views::transform(square)))
			std::cout << i << ' ';

		std::any x = std::vector{ 1, 2, 3, 4 };

		x = make_vector(std::views::all(std::any_cast<std::vector<int>&>(x)) | std::views::transform([](int x) { return std::to_string(x); }));

		
	}

}