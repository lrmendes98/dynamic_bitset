#include "tests.h"
#include <ctime>

#define ITERATIONS 1000

using namespace std;

void testCompressBitsets(){
	dynamic_bitset b = 0;
	b.bitset.push_back(0);
	b.printBitset();
	b.compressBitset();
	b.printBitset();
}

void assert(dynamic_bitset b, uint64_t expected)
{
	if(b.to_ullong() != expected) {
		cerr << "\033[31mErro\033[0m" << endl;
		cerr << "Expected: " << 1 << endl;
		b.printBitset();
		exit(EXIT_FAILURE);
	}
}

void testSub()
{
	std::srand(std::time(0));

	// simple tests
	{
		dynamic_bitset aux = 0;
		aux -= 0;
		if(aux.to_ullong() != 0) {
			cerr << "Erro em testSum()" << endl;
			cerr << "Expected: " << 0 << endl;
			aux.printBitset();
			exit(EXIT_FAILURE);
		}
	}
	{
		dynamic_bitset aux = 5;
		aux -= 4;
		if(aux.to_ullong() != 1) {
			cerr << "\033[31mErro em testSub())\033[0m" << endl;
			cerr << "Expected: " << 1 << endl;
			aux.printBitset();
			exit(EXIT_FAILURE);
		}
	}

	// random numbers sum
	for(size_t i = 0; i < ITERATIONS; i++) {
		uint64_t random1 = 0;
		random1 = rand();
		dynamic_bitset aux = random1;

		aux -= random1;

		uint64_t result = random1 - random1;

		if(result != aux.to_ullong()) {
			cerr << "\033[31mErro em testSub()\033[0m" << endl;
			cerr << "Expected: " << result << endl;
			aux.printBitset();
			exit(EXIT_FAILURE);
		}
	}

	cout << "\033[32mPass testSub\033[0m" << endl;

	return;
}

void testSum()
{
	std::srand(std::time(0));

	// simple tests
	{
		dynamic_bitset aux = 0;
		aux += 0;
		assert(aux, 0);
	}
	{
		dynamic_bitset aux = 5;
		aux += 4;
		assert(aux, 9);
	}

	// not so simple tests
	// for(int i = 0; i < 2; ++i){
	//     dynamic_bitset aux = i;
	//     aux += 2;
	//     uint64_t result = i + 2;

	//     assert(aux, result);
	// }

	// random numbers sum
	for(size_t i = 0; i < ITERATIONS; i++) {
		uint64_t random1 = 0;
		random1 = rand();
		dynamic_bitset aux = random1;

		aux += random1;

		uint64_t result = random1 + random1;

		assert(aux, result);
	}

	cout << "\033[32mPass testSum\033[0m" << endl;

	return;
}