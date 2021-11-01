#ifndef TESTS_H
#define TESTS_H
#include "dynamic_bitset.h"

void testCompressBitsets();
void assert(dynamic_bitset b, uint64_t expected, std::string testName);
void assert(uint64_t b, uint64_t expected, std::string testName);
void testSum();
void testSub();

#endif