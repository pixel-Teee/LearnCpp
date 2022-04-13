namespace DetailedList1dot1 {
	/*
		void func(auto a = 1) {}

		error
	*/

	struct Foo {
		//auto var1_ = 0; error
		static const auto var2_ = 0;
	};

	template<typename T>
	struct Bar {};
}

