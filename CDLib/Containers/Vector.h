#pragma once

template<typename Vector>
class VectorIterator
{
public:
	using ValueType = typename Vector::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;
public:
	VectorIterator(PointerType ptr)
		: m_ptr(ptr){}

	VectorIterator& operator++()
	{
		m_ptr++;
		return *this;
	}

	VectorIterator& operator++(int)
	{
		VectorIterator iterator = *this;
		++(*this);
		return iterator;
	}

	VectorIterator& operator--()
	{
		m_ptr--;
		return *this;
	}

	VectorIterator& operator--(int)
	{
		VectorIterator iterator = *this;
		--(*this);
		return iterator;
	}

	ReferenceType operator[](int index)
	{
		return *(m_ptr + index);
	}

private:
	PointerType m_ptr;
};

template<typename T>
class Vector
{
public:
	using ValueType = T;
	using Iterator = VectorIterator<Vector<T>>;
public:
	Vector()
	{
		re_alloc(2);
	}

	Vector(size_t capacity)
	{
		re_alloc(capacity);
	}

	~Vector()
	{
		clear();
		::operator delete(m_data, m_capacity * sizeof(T));
	}

	void push_back(const T& val)
	{
		if (m_size >= m_capacity)
			re_alloc(m_capacity + m_capacity / 2 + 1);

		new(&m_data[m_size++]) T(val);
	}

	void push_back(T&& val)
	{
		if (m_size >= m_capacity)
			re_alloc(m_capacity + m_capacity / 2 + 1);

		new (&m_data[m_size++]) T(std::move(val));
	}

	template<typename... Args>
	T& emplace_back(Args&&... args)
	{
		if (m_size >= m_capacity)
			re_alloc(m_capacity + m_capacity / 2 + 1);

		new(&m_data[m_size]) T(std::forward<Args>(args) ...);
		return m_data[m_size++];
	}

	void pop_back()
	{
		if (m_size > 0)
		{
			m_size--;
			m_data[m_size].~T();
		}
	}

	void clear()
	{
		for (size_t i = 0; i < m_size; i++)
			m_data[i].~T();

		m_size = 0;
	}

	const T& operator[](size_t index) const 
	{
#ifdef _DEBUG
		if (!(index < m_size)) // vector overflow case #debugonly
			__debugbreak();
#endif

		return m_data[index]; 
	}

	T& operator[](size_t index) 
	{
#ifdef _DEBUG
		if (!(index < m_size)) // vector overflow case #debugonly
			__debugbreak();
#endif

		return m_data[index]; 
	}

	size_t size() const { return m_size; }

	Iterator begin()
	{
		return Iterator(m_data);
	}
	
	Iterator end()
	{
		return Iterator(m_data + m_size);
	}

private:
	void re_alloc(size_t new_capacity)
	{
		T* new_block = (T*)::operator new(new_capacity * sizeof(T));

		if (new_capacity < m_size)
			m_size = new_capacity;

		for (size_t i = 0; i < m_size; ++i)
			new (new_block + i) T(std::move(m_data[i]));

		for (size_t i = 0; i < m_size; ++i)
			m_data[i].~T();

		::operator delete(m_data, new_capacity * sizeof(T));
		m_data = new_block;
		m_capacity = new_capacity;
	}
private:
	size_t m_size = 0;
	size_t m_capacity = 0;
	T* m_data = nullptr;
};