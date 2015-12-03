#include <cassert>
#include <utility>
#include <vector>

// used only my notes

using namespace std::rel_ops;

template<typename T, typename C = std::vector<T>>
class sstack {

	friend bool operator==(const sstack& lhs, const sstack& rhs) {
		return lhs.container == rhs.container;
	}
	friend bool operator<(const sstack& lhs, const sstack& rhs) {
		return lhs.container < rhs.container;
	}

public:
	using container_type = typename C;
	using value_type = typename container_type::value_type;
	using size_type = typename container_type::size_type;
	using reference = typename container_type::reference;
	using const_reference = typename container_type::const_reference;

private:
	container_type container;

public:
	explicit sstack(const container_type& c = container_type()) : container(c) {}

	sstack(const sstack& s) = default;
	~stack() = default;
	stack& operator=(const stack& other) = default;

	bool empty() const {
		return container.empty();
	}

	size_type size() const {
		return container.size();
	}

	reference top() {
		return container.back();
	}

	const_reference top() const {
		return const_cast<sstack<T>*>(this)->top();
	}

	void push(const_reference v) {
		container.push_back(v);
	}

	void pop() {
		container.pop_back();
	}

};