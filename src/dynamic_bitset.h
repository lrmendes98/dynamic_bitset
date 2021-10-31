#ifndef DYNAMICBITSET_H
#define DYNAMICBITSET_H

#include <iostream>
#include <vector>

class dynamic_bitset
{
  private:
	std::vector<bool> bitset;
	void normalizeBitsets(dynamic_bitset* a, dynamic_bitset* b);
	void compressBitset(dynamic_bitset* b);
	void compressBitset();

  public:
	dynamic_bitset() {}
	dynamic_bitset(uint64_t number);
	std::vector<bool> getBitset() const { return this->bitset; }

	void flip(size_t index);
	bool test(size_t index) const;
	uint64_t to_ullong() const;
	void printBitset() const;

	dynamic_bitset operator+(dynamic_bitset b);
	dynamic_bitset operator+(uint64_t n);
	dynamic_bitset operator-(dynamic_bitset b);
	dynamic_bitset operator-(uint64_t n);
	void operator>>(uint64_t n);
	void operator<<(uint64_t n);
	std::vector<bool>::reference operator[](size_t n);
	bool operator>(dynamic_bitset second) const;
	bool operator>(uint64_t n) const;
	bool operator<(dynamic_bitset second) const;
	bool operator<(uint64_t n) const;
	bool operator==(dynamic_bitset second) const;
	bool operator==(uint64_t n) const;
	bool operator!=(dynamic_bitset second) const;
	bool operator!=(uint64_t n) const;
	void operator+=(dynamic_bitset b);
	void operator+=(uint64_t n);
	void operator-=(dynamic_bitset b);
	void operator-=(uint64_t n);
	void operator=(dynamic_bitset b);
	void operator=(uint64_t n);
};

#endif