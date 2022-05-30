#pragma once

#include <vector>
#include <algorithm>
#include <ranges>

namespace TP {

	//------check the T type whether is iterable------
	template<typename T>
	constexpr bool iterable(T) {
		return std::ranges::range<T>;//concept to bool's implicit conversion
	}
	//------check the T type whether is iterable------
	
	//------template type constraint------
	template<typename T>
	concept sortable = requires(T t, size_t i)
	{
		t[i];
	};
	//------template type constraint------

	//------T must sortable------
	template<sortable T>
	void Sort(T& t) {
		std::sort(std::begin(t), std::end(t));
	}
	//------T must sortable------

	//------std::ranges::sort-------
	template<std::ranges::range T>
	T sorted(T input) {
		std::ranges::sort(input);
		return input;
	}
	//------std::ranges::sort-------

	//------from the view to vector------
	template<std::ranges::view T>
	auto make_vector(T a) {
		return std::vector(a.begin(), a.end());
	}
	//------from the view to vector------

	void test();
}