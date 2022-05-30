#pragma once

namespace Reflect
{
	struct AnyType {
		template<typename T>
		operator T();
	};

	template <typename T, typename = void, typename ...Ts>
	struct CountMember {
		constexpr static size_t value = sizeof...(Ts) - 1;
	};

	template <typename T, typename ...Ts>
	struct CountMember < T, std::void_t<decltype(T{ Ts{}... }) > , Ts... > {
		constexpr static size_t value = CountMember<T, void, Ts..., AnyType>::value;
	};

#define GET_NTH_ARG(                                                                        \
		_1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9,  _10, _11, _12, _13, _14, _15, _16,         \
		_17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32,         \
		_33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48,         \
		_49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, n, ...) n

#define GET_ARG_COUNT(...) GET_NTH_ARG(__VA_ARGS__,                     \
        64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, \
        48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, \
        32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, \
        16, 15, 14, 13, 12, 11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1)

#define PAIR(x) PARE x//PAIR((double) x) => PARE(double) x => double x
#define PARE(...) __VA_ARGS__
#define STRIP(x) EAT x//STRIP((double) x) => EAT(double) x => x
#define EAT(...)

#define STRING(x) STR(x)
#define STR(x) #x

#define PASTE(x, y) CONCATE(x, y)
#define CONCATE(x, y) x##y

#define FIELD_EACH(i, arg)\
PAIR(arg);\
template<typename T>\
struct FIELD<T, i>{\
	T& obj;\
	FIELD(T& obj):obj(obj){}\
	auto value()->decltype(auto){\
		return (obj.STRIP(arg));\
}\
	static constexpr const char* name(){\
		return STRING(STRIP(arg));\
}\
}

#define FOR_EACH_1(func, i, arg) func(i, arg);
#define FOR_EACH_2(func, i, arg, ...) func(i, arg); FOR_EACH_1(func, i + 1, __VA_ARGS__)
#define FOR_EACH_3(func, i, arg, ...) func(i, arg); FOR_EACH_2(func, i + 1, __VA_ARGS__)

#define DEFINE_STRUCT(st, ...)                                                \
struct st {                                                                   \
    template <typename, size_t> struct FIELD;                                 \
    static constexpr size_t _field_count_ = GET_ARG_COUNT(__VA_ARGS__);       \
    PASTE(FOR_EACH_, GET_ARG_COUNT(__VA_ARGS__)) (FIELD_EACH, 0, __VA_ARGS__) \
}

	DEFINE_STRUCT(Apple, (double)a, (double)b);

//(f(Point::FIELD<0>(obj).name(), Point::FIELD<0>(obj).value()),
//f(Point::FIELD<1>(obj).name(), Point::FIELD<1>(obj).value());
template<typename T, typename F, size_t... Is>
inline constexpr void ForEach(T&& obj, F&& f, std::index_sequence<Is...>) {
	using TDECAY = std::decay_t<T>;
	(void(f(typename TDECAY::template FIELD<TDECAY, Is>(obj).name(), typename TDECAY::template FIELD<TDECAY, Is>(obj).value())), ...);
}

template<typename T, typename F>
inline constexpr void ForEach(T&& obj, F&& f) {
	ForEach(std::forward<T>(obj),
		std::forward<F>(f),
		std::make_index_sequence<std::decay_t<T>::_field_count_>{});
}

template<typename T>
void DumpObj(T&& obj, const char* fieldName = "", int depth = 0) {
	auto indent = [depth] {
		for (int i = 0; i < depth; ++i) {
			std::cout << " ";
		}
	};

	if constexpr (std::is_class_v<std::decay_t<T>>) {
		indent();
		std::cout << fieldName << (*fieldName ? ": {" : "{") << std::endl;
		ForEach(obj, [depth](auto&& fieldName, auto&& value) {
			DumpObj(value, fieldName, depth + 1);
		});
		indent();
		std::cout << "}" << (depth == 0 ? "" : ",") << std::endl;
	}
	else {
		indent();
		std::cout << fieldName << ":" << obj << "," << std::endl;
	}
};



	void test()
	{
		//Apple::FIELD<Apple, 1>
		std::cout << Apple::FIELD<Apple, 0>::name() << std::endl;
		//std::cout << Apple::FIELD<Apple, 0>::obj() << std::endl;
		std::cout << Apple::FIELD<Apple, 1>::name() << std::endl;

		Apple apple;

		DumpObj(apple);
	}
}