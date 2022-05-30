#include <iostream>
#include <map>
#include "1-1.h"
#include "Template/LearnConcept.h"
#include "Template/Reflect.h"

struct TestClass {
	int a;
	int b;
	int c;
	int d;
};

int main()
{
	//int arr[10] = { 0 };
	//auto aa = arr;//aa -> int *
	//auto rr[10] = arr;

	//DetailedList1dot1::Bar<int> bar;
	//Bar<auto> bb = bar; error

	//TP::test();
	//std::cout << CountMember<Test>();


	std::cout << (Reflect::CountMember<TestClass>::value);

	Reflect::test();
	return 0;
}