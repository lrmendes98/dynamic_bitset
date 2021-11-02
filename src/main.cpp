#include "dynamic_bitset.h"
#include "tests.h"
#include <iostream>
#include "consoleUtils.h"

using namespace std;

int main()
{
	// clear();
	// testSum();
	// testSub();
	// testCompressBitsets();

	dynamic_bitset aux = 2;
	// aux += 2;
	cout << aux.printBitset() << endl;

	cout << endl;
	return 0;
}
