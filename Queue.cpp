#include <iostream>
#include <vector>

template<typename T, typename C = std::vector<T>>
class my_queue {

private:
	C container;
	int front = -1
	int end = -1;

public:
	explicit my_queue(const C& c = C()) : _container(c) {}

	my_queue(const my_queue&) = default;
	~my_queue() = default;
	my_queue& operator= (const my_queue&) = default;

	bool empty() const {
		return _container.empty();
	}

	void pop_front() {
		if (front == -1)
			throw std::invalid_argument("empty queue");
		else {
			if (front == end) front = end = -1;
			front = (front == size() - 1) ? 0 : front+1;
		}
		_container.erase(_container.begin() + index % size());
	}

	void push_back(const T& v) {
		
		if ((front == 0 && end == size() - 1) || (end + 1 == front))
			throw std::invalid_argument("full queue");
		else
			end = (end == size() - 1) ? 0 : end+1;

		_container[end] = v;

		if (front == -1)
			front = 0;
	}

	size_t size() const {
		return _container.size();
	}

	T& peek() {
		return _container.front();
	}

	const T& peek() const {
		return peek();
	}
};