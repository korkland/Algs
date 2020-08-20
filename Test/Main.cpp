#include <iostream>
#include <array>
#include <string>
#include "Algs.h"
#include "Array.h"

int main() {
	int arr[5] = { -2,-3,-1,-5,-7 };

	std::cout << cd::sum_of_abs(arr,5) << std::endl;

	cd::Array<std::string, 3> arrStr;
	arrStr[0] = "Chen";
	arrStr[1] = "Che";
	arrStr[2] = "Chenss";

	std::cout << arrStr[cd::max_element_loc(arrStr.data(), arrStr.size())] << std::endl;

	std::cin.get();

	return 0;
}