#include "tests.h"
#include "dynamic_bitset.h"

using namespace std;

void testSum()
{
    dynamic_bitset aux = 5;
    uint64_t result = 5;

    aux += 5;
    result += 5;
    if (aux.to_ullong() != result){
        cerr << "Erro" << endl;
        cerr << "Value: " << aux.to_ullong() << endl;
        cerr << "Expected: " << result << endl;
    }
	return;
}