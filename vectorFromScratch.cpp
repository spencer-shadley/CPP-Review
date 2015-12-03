#include <stdio.h>
#include <iostream>
#include <utility>

// using only my notes

using namespace std::rel_ops;

template<typename T, typename A = std::allocator<T>>
class vvector {
	friend bool operator==(const vvector& lhs, const vvector& rhs) {
		return (lhs.size() == rhs.size()) &&
				std::equal(lhs.begin(), lhs.end(), rhs.begin();
	}
	friend bool operator<(const vvector& lhs, const vvector& rhs) {
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

public:
	using allocator_type	= typename A;
	using value_type		= typename allocator_type::value_type;
	using size_type			= typename allocator_type::size_type;
	using difference_type	= typename allocator_type::difference_type;
	using pointer			= typename allocator_type::pointer;
	using const_pointer		= typename allocator_type::const_pointer;
	using reference			= typename allocator_type::reference;
	using const_reference	= typename allocator_type::const_reference;
	using iterator			= typename allocator_type::iterator;
	using const_iterator	= typename allocator_type::const_iterator;

private:
	A _a;
	T* _b;
	T* _e;

public:
	explicit vvector(size_type s = 0, const_reference v = T(), const A& a = A()) : 
		_a(a), 
		_b(s == 0 ? nullptr : _a.allocate(s)),
		_e(s == 0 ? nullptr : _b + s) {
		my_uninitialized_fill(_a, _b, _e, v);
	}

	vvector(const vvector& rhs) :
		_a(rhs._a),
		_b(rhs.size() == 0 ? nullptr : _a.allocate(rhs.size()),
		_e(rhs.size() == 0 ? nullptr : _b + size()) {
		my_unitialized_copy(_a, rhs._b, rhs._e, _b);
	}

	vvector(const vvector&& rhs) :
		_a(move(rhs._a)),
		_b(rhs._b),
		_e(rhs._e) {
		rhs._b = nullptr;
		rhs_e = nullptr;
	}

	vvector& operator=(const vvector& rhs) {
		vvector that(rhs);
		std::swap(_b, that._b);
		std::swap(_e, that._e);
		return *this;
	}

	~vvector() {
		my_destroy(_a, begin(), end());
		_a.deallocate(begin(), size());
	}

	refererence operator[](size_type i) {
		return begin()[i];
	}

	const_reference operator[](size_type i) const {
		return (*const_cast<vvector<T>*>(this))[i];
	}

	reference at(size_type i) {
		if (i >= size())
			throw std::out_of_range("cannot index");
		return (*this)[i];
	}

	const_reference at(size_type i) const {
		return const_cast<vvector<T>*>(this)->at(i);
	}

	pointer begin() {
		return _b;
	}

	const_pointer begin() const {
		return const_cast<vvector<T>*>(this)->begin();
	}

	pointer end() {
		return _e;
	}

	const_pointer end() const {
		return const_cast<vvector<T>*>(this)->end();
	}

	size_type size() const {
		return (begin() == nullptr) ? 0 : end() - begin();
	}

};