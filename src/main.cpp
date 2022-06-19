#include "dynamic_bitset.h"
#include "tests.h"
#include <iostream>
#include "consoleUtils.h"

using namespace std;

int main()
{
	clear();

	testSum();
	testSub();
	testCompressBitsets();
	testNormalizeBitsets();

	
	// // aux += 2;
	// cout << "state: " << state.printBitset() << endl;
	// cout << "aux: " << aux.printBitset() << endl;

	// cout << endl;
	return 0;
}
