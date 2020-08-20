#pragma once

#define CMP(lhs,rhs) bool(*cmp)(const T& lhs, const T& rhs)

namespace cd
{
	template<typename T>
	const size_t min_element_loc(const T* p, size_t size)
	{
		T min_element = p[0];
		size_t min_element_idx = 0;
		for (int i = 1; i < size; ++i)
		{
			if (p[i] < min_element)
			{
				min_element = p[i];
				min_element_idx = i;
			}
		}
		return min_element_idx;
	}

	template<typename T>
	const size_t min_element_loc(const T* p, size_t size, CMP(lhs, rhs))
	{
		T min_element = p[0];
		size_t min_element_idx = 0;
		for (int i = 1; i < size; ++i)
		{
			if (cmp(p[i], min_element))
			{
				min_element = p[i];
				min_element_idx = i;
			}
		}
		return min_element_idx;
	}

	template<typename T>
	const size_t max_element_loc(const T* p, size_t size)
	{
		T max_element = p[0];
		size_t max_element_idx = 0;
		for (int i = 1; i < size; ++i)
		{
			if (p[i] > max_element)
			{
				max_element = p[i];
				max_element_idx = i;
			}
		}
		return max_element_idx;
	}

	template<typename T>
	const size_t max_element_loc(const T* p, size_t size, CMP(lhs, rhs))
	{
		T max_element = p[0];
		size_t max_element_idx = 0;
		for (int i = 1; i < size; ++i)
		{
			if (cmp(p[i], max_element))
			{
				max_element = p[i];
				max_element_idx = i;
			}
		}
		return max_element_idx;
	}

	template<typename T>
	const T sum(const T* p, size_t size)
	{
		T total1 = 0;
		T total2 = 0;
		T total3 = 0;
		T total4 = 0;

		// Sum the data
		const T* data = p;
		for (size_t i = 0; i < size / 4; ++i)
		{
			total1 += data[0];
			total2 += data[1];
			total3 += data[2];
			total4 += data[3];

			data += 4;
		}

		// Sum residuals
		for (size_t i = 0; i < (size & 3); ++i)
			total1 += data[i];

		return (total1 + total2) + (total3 + total4);
	}

	template<typename T>
	const T sum_of_abs(const T* p, size_t size)
	{
		T total1 = 0;
		T total2 = 0;
		T total3 = 0;
		T total4 = 0;

		// Sum the data
		const T* data = p;
		for (size_t i = 0; i < size / 4; ++i)
		{
			total1 += abs(data[0]);
			total2 += abs(data[1]);
			total3 += abs(data[2]);
			total4 += abs(data[3]);

			data += 4;
		}

		// Sum residuals
		for (size_t i = 0; i < (size & 3); ++i)
			total1 += abs(data[i]);

		return (total1 + total2) + (total3 + total4);
	}

	template<typename T>
	const double standard_deviation(const T* p, size_t size)
	{
		double N = double(size);

		// Sums for N and N^2
		T s1_1 = 0, s2_1 = 0;
		T s1_2 = 0, s2_2 = 0;
		T s1_3 = 0, s2_3 = 0;
		T s1_4 = 0, s2_4 = 0;

		// Sum the data, and the data squared
		const T* data = p;
		for (size_t i = 0; i < size / 4; ++i)
		{
			s1_1 += data[0];
			s1_2 += data[1];
			s1_3 += data[2];
			s1_4 += data[3];

			s2_1 += data[0] * data[0];
			s2_2 += data[1] * data[1];
			s2_3 += data[2] * data[2];
			s2_4 += data[3] * data[3];

			data += 4;
		}

		// Sum residuals
		for (size_t i = 0; i < (size & 3); ++i)
		{
			s1_1 += data[i];
			s2_1 += data[i] * data[i];
		}

		// Sum the unrolled sums to scalars
		T s1 = (s1_1 + s1_2) + (s1_3 + s1_4);
		T s2 = (s2_1 + s2_2) + (s2_3 + s2_4);

		return sqrt((N*s2) - (s1*s1)) / N;
	}

	template<typename T>
	const T dot_product(const T* p1, const T* p2, int size)
	{
		T total1 = 0;
		T total2 = 0;
		T total3 = 0;
		T total4 = 0;

		// Sum the multiplied data
		const T* data_a = p1;
		const T* data_b = p2;
		for (int i = 0; i < size / 4; ++i)
		{
			total1 += data_a[0] * data_b[0];
			total2 += data_a[1] * data_b[1];
			total3 += data_a[2] * data_b[2];
			total4 += data_a[3] * data_b[3];

			data_a += 4;
			data_b += 4;
		}

		// Sum the multiplied residuals
		for (int i = 0; i < (size & 3); ++i)
			total1 += data_a[i] * data_b[i];

		return (total1 + total2) + (total3 + total4);
	}
}