#include "tests.h"
#include "consoleUtils.h"
#include <ctime>

#define ITERATIONS 100000

using namespace std;

void testCompressBitsets()
{
	dynamic_bitset b = 0;
	for(int i = 0; i < ITERATIONS; ++i) {
		b.bitset.push_back(0);
	}
	dynamic_bitset::compressBitset(&b);
	cout << b.printBitset() << endl;
	if(b.getBitset().size() != 1) {
		cerr << printRedBold("Erro em compress bitset") << endl;
	}
	cout << printGreenBold("Pass testCompressBitset") << endl;
}

void assert(uint64_t b, uint64_t expected, string testName)
{
	if(b != expected) {
		cerr << printRedBold("Error in " + testName) << endl;
		cerr << "Received: " << b << endl;
		cerr << "Expected: " << expected << endl;
		exit(EXIT_FAILURE);
	} else {
		// cout << printGreenBold("Pass " + testName) << endl;
	}
}

void assert(dynamic_bitset b, uint64_t expected, string testName)
{
	if(b.to_ullong() != expected) {
		cerr << printRedBold("Error in " + testName) << endl;
		cerr << "Received: " << b.printBitset() << endl;
		cerr << "Expected: " << expected << endl;
		exit(EXIT_FAILURE);
	} else {
		// cout << printGreenBold("Pass " + testName);
	}
}

void testSub()
{
	std::srand(std::time(0));

	// simple tests
	{
		dynamic_bitset aux = 0;
		aux -= 0;
		assert(aux, 0, "testSub 1");
		cout << printGreenBold("Pass testSub 1") << endl << endl;
	}
	{
		dynamic_bitset aux = 5;
		aux -= 4;
		aux.printBitset();
		assert(aux, 1, "testSub 2");
		cout << printGreenBold("Pass testSub 2") << endl << endl;
	}

	// random numbers sum
	for(size_t i = 0; i < ITERATIONS; i++) {
		uint64_t random1 = 0;
		random1 = rand();
		dynamic_bitset aux = random1;

		aux -= random1;
		uint64_t result = random1 - random1;
		assert(aux, result, "testSub random");
	}

	cout << printGreenBold("Pass testSub random") << endl << endl;

	return;
}

void testSum()
{
	std::srand(std::time(0));

	// simple tests
	{
		dynamic_bitset aux = 0;
		aux += 0;
		assert(aux, 0, "testSum 1");
	}
	{
		dynamic_bitset aux = 5;
		aux += 4;
		assert(aux, 9, "testSum 2");
	}

	// not so simple tests
	for(int i = 0; i < ITERATIONS; ++i) {
		dynamic_bitset aux = i;
		aux += 2;
		uint64_t result = i + 2;
		assert(aux, result, "testSum 3");
	}

	// random numbers sum
	for(size_t i = 0; i < ITERATIONS; i++) {
		uint64_t random1 = 0;
		random1 = rand();
		dynamic_bitset aux = random1;

		aux += random1;

		uint64_t result = random1 + random1;

		assert(aux, result, "testSum random");
	}
	cout << printGreenBold("Pass testSum random") << endl << endl;

	return;
}