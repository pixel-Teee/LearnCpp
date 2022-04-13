#pragma once

#include <type_traits>

namespace DetailedList1dot2 {
	class Foo {
	public:
		static int get(void) {
			return 0;
		}
	};

	class Bar {
	public:
		static const char* get(void) {
			return "0";
		}
	};

	template<class A>
	void func(void) {
		auto var = A::get();
	}
}
