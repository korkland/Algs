#pragma once

namespace cd
{
	template<typename T, size_t S>
	class Array
	{
	public:
		constexpr size_t size() const { return S; }

		T* data() { return m_data; }
		const T* data() const { return m_data; }

		void fill(const T& value)
		{
			for (size_t i = 0; i < S; ++i)
				m_data[i] = value;
		}

		T& operator[](size_t index) 
		{ 
#ifdef _DEBUG
			if (!(index < S)) // array overflow case #debugonly
				__debugbreak();
#endif
			return m_data[index]; 
		}

		const T& operator[](size_t index) const 
		{ 
#ifdef _DEBUG
			if (!(index < S)) // array overflow case #debugonly
				__debugbreak();
#endif
			return m_data[index]; 
		}

	private:
		T m_data[S];

		//#chenTODO iterators
	};
}
