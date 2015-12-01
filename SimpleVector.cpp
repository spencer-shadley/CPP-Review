#include <stdio.h>
#include <iostream>
#include <utility>

using namespace std::rel_ops;

template<typename T, typename A = std::allocator<T>>
class simple_vector {
private:
	A _a;
	T* _b;
	T* _e;

public:
	friend bool operator==(const simple_vector& lhs, const simple_vector& rhs) {
		if (&lhs == &rhs)				return true; // optimization for comparing the same vector
		if (lhs.size() != rhs.size())	return false;
		return std::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	friend bool operator<(const simple_vector& lhs, const simple_vector& rhs) {
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.end());
	}

	explicit simple_vector(size_t size = 0, const A& a = A(), const T& v = T()) :
		_a(a),
		_b(size == 0 ? nullptr : _a.allocate(size)),
		_e(size == 0 ? nullptr : _b + s) {
		my_unintialized_fill(_a, _b, _e, v);
	}

	simple_vector(const simple_vector& rhs) :
		_a(rhs._a),
		_b(rhs.size() == 0 ? nullptr : _a.allocate(rhs.size()),
		_e(rhs.size() == 0 ? nullptr : _b + rhs.size()) {
		my_unintialized_copy(_a, _b, _e, rhs._b);
	}

	simple_vector(simple_vector&& rhs) :
		_a(move(rhs._a)),
		_b(rhs._b),
		_e(rhs._e) {
		rhs._b = nullptr;
		rhs._e = nullptr;
	}

	simple_vector& operator=(simple_vector rhs) { // not by reference so will make a copy
		if (this == &rhs) return *this; // x = x;
		std::swap(_b, rhs._b);
		std::swap(_e, rhs._e);
		return *this;
	}

	simple_vector& operator=(simple_vector&& rhs) {
		
		// get rid of our stuff
		my_destroy(_a, _b, _e);
		_a.deallocate(begin(), size());

		// get the values
		_b = rhs._b;
		_e = rhs._e;

		// prevent deallocation of our new pointers
		rhs._b = nullptr;
		rhs._e = nullptr;

		return *this;
	}

	~simple_vector() {
		my_destroy(_a, _b, _e);
		_a.deallocate(_b, size());
	}

	const A* begin() const {
		return begin();
	}

	A* begin() {
		return const_cast<simple_vector<T>*>(this)->begin();
	}

	A* end() {
		return _e;
	}

	const A* end() const {
		return const_cast<simple_vector<T>*>(this)->end();
	}

	T& operator[] (const size_t index) {
		return *(_b + index);
	}

	const T& operator[] (const size_t index) const {
		return (*const_cast<simple_vector<T>*>(this))[index];
	}

	T& at(const size_t index) {
		if (index >= size()) throw std::out_of_range("index is greater than size");
		return (*this)[index];
	}

	const T& at(const size_t index) const {
		return const_cast<simple_vector<T>*>(this)->at(index);
	}

};