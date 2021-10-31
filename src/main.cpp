#include "dynamic_bitset.h"
#include <iostream>

using namespace std;

int main()
{
	// {
	// 	dynamic_bitset a1(5);
	// 	dynamic_bitset a2(0);

	// 	for(int i = 0; i < 1000; ++i) {
	// 		dynamic_bitset aux = a1 + a2;
	// 		if(aux.to_ullong() != 5)
	// 			cerr << "Error 1" << endl;
	// 	}

	// 	for(int i = 0; i < 1000; ++i) {
	// 		dynamic_bitset aux = a1 + a2;
	// 		if(aux.to_ullong() != 5)
	// 			cerr << "Error 2" << endl;
	// 	}
	// }

	dynamic_bitset a1 = 5;
	dynamic_bitset a2 = 4;
	// dynamic_bitset a3 = a1 + a2;
	// dynamic_bitset a4 = a1 + a2;
	// dynamic_bitset a5 = a1 + a2;

	// a3.printBitset();
	// a4.printBitset();
	// a5.printBitset();

	cout << (a1 - a2).to_ullong() << endl;

	return 0;
}
