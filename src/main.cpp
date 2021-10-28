#include "dynamic_bitset.h"
#include <iostream>

using namespace std;

int main()
{
	dynamic_bitset bitset1 = 5;
	dynamic_bitset bitset2 = 0;

	bitset1.printBitset();
	(bitset1 - bitset2).printBitset();
	bitset1.printBitset();

	dynamic_bitset new1(5);
	dynamic_bitset new2(0);
	
	(new1 - new2).printBitset();

	(new1 - new2).printBitset();

	(new1 - new2).printBitset();
	
	// std::cout << bitset1.to_ullong() << std::endl;

	// std::cout << "state1: " << state1_num << std::endl;
	// dynamic_bitset state1(state1_num);
	// state1.printBitset();
	// uint64_t state2_num = 2;
	// std::cout << "state2: " << state2_num << std::endl;
	// dynamic_bitset state2(state2_num);

	// /* Operations */
	// state1 >> 2;
	// // state1 << 3;
	// state1.printBitset();
	// std::cout << "Converted state1: " << state1.to_ullong() << std::endl;

	// // state2 += 2;
	// // state2.printState();
	// // std::cout << "Converted state2: " << state2.to_uint64() << std::endl;

	// std::cout << "\n";

	// std::cout << "Greater than:" << std::endl;
	// if (state1 > state2)
	//     std::cout << "\ttrue" << std::endl;
	// else
	//     std::cout << "\tfalse" << std::endl;

	// std::cout << "Smaller than:" << std::endl;
	// if (state1 < state2)
	//     std::cout << "\ttrue" << std::endl;
	// else
	//     std::cout << "\tfalse" << std::endl;

	// std::cout << "Equals:" << std::endl;
	// if(bitset1 == bitset2)
	// 	std::cout << "\ttrue" << std::endl;
	// else
	// 	std::cout << "\tfalse" << std::endl;

	// std::cout << "Not Equals:" << std::endl;
	// if(bitset1 != bitset2)
	// 	std::cout << "\ttrue" << std::endl;
	// else
	// 	std::cout << "\tfalse" << std::endl;

	return 0;
}
