#pragma once

// This heap does not meant to grow dynamically !
// capacity allocation options:
// Constructor(capacity)
// re_alloc(capacity)
// build_heap_from_data(data, data_size, heap_capacity)

template <class T>
class MaxHeap
{
public:

	MaxHeap(){}

	MaxHeap(size_t capacity)
	{
		re_alloc(capacity);
	}

	~MaxHeap()
	{
		clear();
		::operator delete(m_data, (m_capacity + 1) * sizeof(T));
	}

	void re_alloc(size_t capacity)
	{
		for (size_t i = 0; i < m_size; i++)
			m_data[i].~T();
		
		::operator delete(m_data, (m_capacity + 1) * sizeof(T));

		m_capacity = capacity;
		m_data = (T*)::operator new((m_capacity + 1) * sizeof(T));
	}

	void build_heap_from_data(T* data, size_t data_size, size_t heap_capacity)
	{
		// build heap from InitData in O(N)

		re_alloc(heap_capacity);

		m_size = data_size;

		size_t first_leaf_idx = (m_size / 2);

		// copy all leaf nodes to heap
		for (size_t j = first_leaf_idx; j < m_size; j++)
			m_data[j + 1] = data[j];

		// heapify every node
		for (size_t i = first_leaf_idx; i > 0; i--)
		{
			m_data[i] = data[i - 1];
			bubble_down(i);
		}
	}

	void insert_value(T val)
	{
		if (m_size >= m_capacity)
		{
#ifdef _DEBUG
			__debugbreak();
#endif
			return;
		}

		m_data[++m_size] = val;

		bubble_up(m_size);
	}

	void replace_top(T val)
	{
		m_data[1] = val;
		bubble_down(1);
	}

	void remove_by_idx(size_t i /* 1 base indexing !*/)
	{
#ifdef _DEBUG
		if (i > m_size || i == 0)
			__debugbreak();
#endif

		std::swap(m_data[i], m_data[m_size--]);

		if (i == 1 || m_data[i] < m_data[parent(i)])
			bubble_down(i);
		else
			bubble_up(i);
	}

	void remove_by_val(T val) 
	{
		for (size_t i = 1; i <= m_size; i++)
		{
			if (m_data[i] == val)
			{
				remove_by_idx(i);
				return;
			}
		}

#ifdef _DEBUG
		__debugbreak();
#endif
	}

	void clear() 
	{
		for (size_t i = 0; i < m_size; i++)
			m_data[i].~T();

		m_size = 0; 
	}

	size_t size() const { return m_size; }

	size_t capacity() const { return m_capacity; }

	T pop_max()
	{
		T max = m_data[1];
		std::swap(m_data[1], m_data[m_size--]);
		bubble_down(1);

		return max;
	}

	T get_max() const { return m_data[1]; }

private:

	size_t parent(size_t i) { return i >> 1; } // i/2

	size_t left_child(size_t i) { return i << 1; } // i*2

	size_t right_child(size_t i) { return (i << 1) + 1; } // i*2 + 1

	void bubble_up(size_t i)
	{
		if (i > m_size) return;

		while (i != 1 && m_data[i] > m_data[parent(i)])
		{
			std::swap(m_data[parent(i)], m_data[i]);
			i = parent(i);
		}
	}

	void bubble_down(size_t i)
	{
		if (i > m_size) return;

		size_t left = left_child(i);
		size_t right = right_child(i);
		size_t swap_id = i;

		if (left <= m_size && m_data[i] < m_data[left])
		{
			swap_id = left;
		}

		if (right <= m_size && m_data[swap_id] < m_data[right])
		{
			swap_id = right;
		}

		if (swap_id != i)
		{
			std::swap(m_data[i], m_data[swap_id]);
			bubble_down(swap_id);
		}

		return;
	}

private:
	T*	m_data = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 0;
};