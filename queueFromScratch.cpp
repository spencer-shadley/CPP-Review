#include <cassert>
#include <utility>
#include <deque>

// implemented using only notes

using namespace std::rel_ops;

template<typename T, typename C = std::deque<T>>
class q {
public:
	using container_type = C;
	using value_type = typename container_type::value_type;
	using size_type = typename container_type::size_type;
	using reference = typename container_type::reference;
	using const_reference = typename container_type::const_reference;

private:
	container_type container;

public:
	friend operator==(q& lhs, q& rhs) const {
		return lhs.container == rhs.container;
	}
	friend operator<(q& lhs, q& rhs) const {
		return lhs.container < rhs.container;
	}

	explicit q(const container_type& c = container_type()) container(c) {}
	q(const q& other) = default;
	~q() = default;
	q& operator=(const q& other) = default;

	// ...
	// basically the same shit as stack...
	// ...

};