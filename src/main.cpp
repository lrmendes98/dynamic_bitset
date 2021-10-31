#include "dynamic_bitset.h"
#include <iostream>

using namespace std;

int main()
{
	dynamic_bitset new1(5);
	dynamic_bitset new2(0);

	dynamic_bitset aux = new1 - new2;
	std::cout << "Result: ";
	aux.printBitset();

	aux = new1 - new2;
	std::cout << "Result: ";
	aux.printBitset();

	aux = new1 - new2;
	std::cout << "Result: ";
	aux.printBitset();

	return 0;
}
