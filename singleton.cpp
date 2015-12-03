#include <iostream>

template<typename T>
class singletonFunction {
	T data;

public:
	T getData() {
		static T single = T();
		data = single;
		return data;
	}

};

template<typename T>
class singletonMember {
	static T data = T();

public:
	T getData() const {
		return data;
	}

	void setData(const T& d) {
		data = d;
	}

};

int main() {

	singletonFunction<int> asdf;
	std::cout << asdf.getData() << std::endl;

	return 0;
}