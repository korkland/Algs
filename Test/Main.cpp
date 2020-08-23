#include <iostream>
#include <array>
#include <vector>
#include <string>
#include "Algs.h"
#include "Array.h"
#include "Vector.h"

struct Vector3
{
	float x = 0.0f, y = 0.0f, z = 0.0f;
	int* m_MemoryBlock = nullptr;

	Vector3(){
		m_MemoryBlock = new int[5];
	}
	Vector3(float scalar)
		:x(scalar), y(scalar), z(scalar) {
		m_MemoryBlock = new int[5];
	}
	Vector3(float x, float y, float z)
		:x(x), y(y), z(z) {
		m_MemoryBlock = new int[5];
	}

	Vector3(const Vector3& other) = delete;

	Vector3(Vector3&& other)
		:x(other.x), y(other.y), z(other.z)
	{
		m_MemoryBlock = other.m_MemoryBlock;
		other.m_MemoryBlock = nullptr;
		std::cout << "Move\n";
	}
	~Vector3()
	{

		delete[] m_MemoryBlock;
		std::cout << "Destroy\n";
	}

	Vector3& operator=(const Vector3& other) = delete;

	Vector3& operator=(Vector3&& other)
	{
		m_MemoryBlock = other.m_MemoryBlock;
		other.m_MemoryBlock = nullptr;
		std::cout << "Move\n";
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}
};

void print_vec(const Vector<Vector3>& vec)
{
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << vec[i].x << ", " << vec[i].y << ", " << vec[i].z << ", " << std::endl;
}
template<typename T>
void print_vec(const Vector<T>& vec)
{
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << std::endl;
}

void matrix_multiply_c(float* A, float* B, float* C, unsigned int n, unsigned int m, unsigned int k) {
	// n - A rows
	// m - B cols
	// k - A cols/B rows
	for (unsigned int i_idx = 0; i_idx < n; i_idx++) {
		for (unsigned int j_idx = 0; j_idx < m; j_idx++) {
			float result = 0;
			for (unsigned int k_idx = 0; k_idx < k; k_idx++) {
				result += A[n*i_idx + k_idx] * B[m*k_idx + j_idx];
			}
			C[n*j_idx + i_idx] = result;
			std::cout << result << ", ";
		}
		std::cout << "\n";
	}
}

int main() {
	/*
	Vector<std::string> vec;
	vec.emplace_back("Chen");
	vec.push_back("Ha");
	vec.push_back("Meleh");
	print_vec(vec);
	{

		Vector<Vector3> vec3;
		vec3.emplace_back(4.f);
		vec3.emplace_back(1.f, 2.f, 3.f);
		vec3.emplace_back(2.f, 6.f, 5.f);
		vec3.emplace_back();
		print_vec(vec3);
		vec3.pop_back();
		vec3.pop_back();
		print_vec(vec3);
		vec3.emplace_back(3.f, 7.f, 2.f);
		vec3.emplace_back(4.f, 8.f, 0.f);
		print_vec(vec3);
		vec3.clear();
		print_vec(vec3);
		vec3.emplace_back(3.f, 7.f, 2.f);
		vec3.emplace_back(4.f, 8.f, 0.f);
		print_vec(vec3);
	}
	*/

	float A[16] = { 9, 5, 1, 3, 0,
					5, 3, 6, 7, 7,
					1, 7, 8, 1, 7};
	float B[16] = { 6, 3, 1,
					5, 8, 1,
					5, 3, 3,
					4, 7, 6,
					8, 9, 9 };
	float C[16];
	matrix_multiply_c(A, B, C, 3, 3, 5);
	std::cin.get();

	return 0;
}