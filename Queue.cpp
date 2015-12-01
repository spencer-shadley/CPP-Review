#include <stdio.h>
#include <iostream>
#include <utility>
#include <deque>
#include <vector>

using namespace std::rel_ops;

template <typename T, typename C = std::vector<T>>
class my_queue {

private:
	C collection;

public:

	friend bool operator==(const my_queue& lhs, const my_queue& rhs) {
		return lhs.collection == rhs.collection;
	}

	friend bool operator<(const my_queue& lhs, const my_queue& rhs) {
		std::lexicographical_compare(lhs.collection.begin(), lhs.collection.end(), rhs.collection.end());
	}

	explicit my_queue(C c = C()) : collection(c) {}
	my_queue(const my_queue& q) = default;
	~my_queue() = default;
	my_queue& operator=(const my_queue& rhs) = default;

	bool empty() const {
		return collection.empty();
	}

	void pop_front() {
		collection.erase(collection.begin());
	}

	void push_back(const T& v) {
		collection.push_back(v);
	}

	size_t size() const {
		return collection.size();
	}

	T& peek() {
		return collection.front();
	}

	const T& peek() const {
		return peek();
	}
};