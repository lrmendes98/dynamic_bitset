#include "dynamic_bitset.h"
#include "tests.h"
#include <iostream>

using namespace std;

int main()
{
	testSum();

	dynamic_bitset aux = 5;
	aux += 5;
	aux.printBitset();

	return 0;
}
