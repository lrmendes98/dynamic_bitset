#include "tests.h"
#include "dynamic_bitset.h"
#include <ctime>

#define ITERATIONS 1000

using namespace std;

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
		if(aux.to_ullong() != 0) {
			cerr << "Erro em testSum()" << endl;
			cerr << "Expected: " << 0 << endl;
			aux.printBitset();
			exit(EXIT_FAILURE);
		}
	}
    {
		dynamic_bitset aux = 5;
		aux += 4;
		if(aux.to_ullong() != 9) {
			cerr << "Erro em testSum()" << endl;
			cerr << "Expected: " << 9 << endl;
			aux.printBitset();
			exit(EXIT_FAILURE);
		}
	}

    // not so simple tests
    // for(int i = 0; i < 2; ++i){
    //     dynamic_bitset aux = i;
    //     cout << "hello??????" << endl;
    //     aux += 2;
    //     uint64_t result = i + 2;


    //     if(result != aux.to_ullong()) {
	// 		cerr << "Erro em testSum()" << endl;
	// 		cerr << "Expected: " << result << endl;
	// 		aux.printBitset();
	// 		exit(EXIT_FAILURE);
	// 	}
    // }

	// random numbers sum
	for(size_t i = 0; i < ITERATIONS; i++) {
		uint64_t random1 = 0;
		random1 = rand();
		dynamic_bitset aux = random1;

		aux += random1;

		uint64_t result = random1 + random1;

		if(result != aux.to_ullong()) {
			cerr << "Erro em testSum()" << endl;
			cerr << "Expected: " << result << endl;
			aux.printBitset();
			exit(EXIT_FAILURE);
		}
	}

	cout << "\033[32mPass testSum\033[0m" << endl;

	return;
}