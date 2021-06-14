#include <iostream>
#include <array>
#include <vector>
#include <string>
#include "Algs.h"
#include "Array.h"
#include "Vector.h"
#include <unordered_map>
#include "Max_Heap.h"
#include "Min_Heap.h"
#include "version2/vectorclass.h"

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

//Definition for singly - linked list.
struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
	std::vector<int> twoSum(std::vector<int>& nums, int target) {
		std::unordered_map<int, int> map = { { nums[0],0 } };
		std::vector<int> result(2, 0);

		for (int i = 1; i < nums.size(); i++)
		{
			int cmplmnt = target - nums[i];
			auto search = map.find(cmplmnt);
			if (search != map.end())
			{
				result[0] = search->second;
				result[1] = i;
				return result;
			}
			map[nums[i]] = i;
		}
		return result;
	}

	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		
		if (!l1)
			return l2;
		if (!l2)
			return l1;
		
		ListNode* res = new ListNode(-1);
		ListNode* current = res;
		while (l1 && l2)
		{
			if (l1->val <= l2->val)
			{
				current->next = l1;
				l1 = l1->next;
			}
			else
			{
				current->next = l2;
				l2 = l2->next;
			}
			current = current->next;
		}

		if (l1)
			current->next = l1;
		else
			current->next = l2;

		return res->next;
	}

	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

		int resid = 0;
		ListNode* res = new ListNode(-1);
		ListNode* curr = res;

		while (l1 || l2)
		{
			int val1 = l1 ? l1->val : 0;
			int val2 = l2 ? l2->val : 0;

			int sum = val1 + val2 + resid;

			resid = sum / 10;

			curr->next = new ListNode(sum % 10);

			if (l1) l1->next;
			if (l2) l2->next;
		}

		if (resid)
			curr->next = new ListNode(resid);

		return res->next;
	}
};

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
	

// 	float A[16] = { 9, 5, 1, 3, 0,
// 					5, 3, 6, 7, 7,
// 					1, 7, 8, 1, 7};
// 	float B[16] = { 6, 3, 1,
// 					5, 8, 1,
// 					5, 3, 3,
// 					4, 7, 6,
// 					8, 9, 9 };
// 	float C[16];
// 	matrix_multiply_c(A, B, C, 3, 3, 5);

// 	Solution s;
// 	std::vector<int> v = { 2,7,11,15 };
// 	int target = 26;
// 	std::vector<int> result = s.twoSum(v, target);

// 	MinHeap<int> heap1;
// 	int arr[10] = { 1,2,3,4,5,6,7,8,9,0 };
// 	heap1.build_heap_from_data(arr, 10, 12);
// 	heap1.insert_value(14);
// 	heap1.insert_value(6);
// 	heap1.insert_value(8);
// 	heap1.remove_by_idx(2);
// 	heap1.replace_top(20);
// 	heap1.replace_top(1);

// 	int val = 121;
// 	int res = val / 10;
// 	int first = val % 10;
// 	Solution sol;
// 	ListNode* a = new ListNode(0);
// 	ListNode* b = new ListNode(7); b->next = new ListNode(3);
// 	ListNode* res = sol.addTwoNumbers(a, b);
*/

	Vec8f A(1, 2, 3, 4, 5, 6, 7, 8);
	Vec8f B(5, 1, 4, 2, 9, 8, 0, 6);

	Vec8f C = A + B;
	
	std::cin.get();

	return 0;
}