#pragma once

#include <vector>
#include <algorithm>
#include <ranges>

namespace TP {

	template<typename T>
	constexpr bool iterable(T) {
		return std::ranges::range<T>;//concept to bool's implicit conversion
	}

	//------template type constraint------
	template<typename T>
	concept sortable = requires(T t, size_t i)
	{
		t[i];
	};
	//------template type constraint------

	template<sortable T>
	void Sort(T& t) {
		std::sort(std::begin(t), std::end(t));
	}

	template<std::ranges::range T>
	T sorted(T input) {
		std::ranges::sort(input);
		return input;
	}

	template<std::ranges::view T>
	auto make_vector(T a) {
		return std::vector(a.begin(), a.end());
	}

	void test();
}