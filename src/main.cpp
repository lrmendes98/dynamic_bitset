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

	cout << endl;
	return 0;
}
