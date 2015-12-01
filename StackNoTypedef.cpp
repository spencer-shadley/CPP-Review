#include <stdio.h>
#include <iostream>
#include <utility>
#include <deque>
#include <vector>

using namespace std::rel_ops;

// using a deque or a vector should be the same right?
template<typename T, typename C = std::vector<T>>
// template<typename T, typename C = std::deque<T>>

class my_stack {

public:

	friend bool operator==(const my_vector& lhs, const my_vector& rhs) const {
		return lhs.collection == rhs.collection;
	}

	friend bool operator<(const my_vector& lhs, const my_vector& rhs) const {
		return lhs.collection < rhs.collection;
	}

private:
	C collection;

public:

	explicit my_stack(const C& c = C()) : collection(c) {}
	~my_stack() = default;
	my_stack(const my_stack& stack) = default;
	my_stack& operator=(const my_stack& rhs) = default;

	bool empty() const {
		return collection.empty();
	}

	void pop() {
		collection.pop_back();
	}

	void push(const T& v) {
		collection.push_back(v);
	}

	size_t size() const {
		return collection.size();
	}

	T& top() {
		return collection.back();
	}

	T& top() const {
		return top();
	}
};