#ifndef TESTS_H
#define TESTS_H
#include "dynamic_bitset.h"

void testCompressBitsets();
void assert(dynamic_bitset b, uint64_t expected);
void testSum();
void testSub();

#endif