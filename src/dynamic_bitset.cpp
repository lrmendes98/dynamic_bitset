#include "dynamic_bitset.h"

#define MASK(N) (0x1ull << N)

using namespace std;

void dynamic_bitset::compressBitset()
{
	size_t aux = this->bitset.size() - 1;
	while(this->bitset[aux] == 0 && aux > 0) {
		this->bitset.pop_back();
		--aux;
	}

	return;
}

void dynamic_bitset::compressBitset(dynamic_bitset* b)
{
	size_t aux = b->bitset.size() - 1;
	while(b->bitset[aux] == 0 && aux > 1) {
		b->bitset.pop_back();
		--aux;
	}

	return;
}

void dynamic_bitset::normalizeBitsets(dynamic_bitset* a, dynamic_bitset* b)
{
	// convert both binaries to the same size
	size_t diff = a->bitset.size() - b->bitset.size();
	if(diff == 0)
		return;
	else if(diff < 0)
		while(diff > 0) {
			a->bitset.push_back(0);
			--diff;
		}
	else
		while(diff > 0) {
			b->bitset.push_back(0);
			--diff;
		}

	return;
}

dynamic_bitset::dynamic_bitset(uint64_t number)
{
	if(number == 0)
		this->bitset.push_back(0);
	while(number > 0) {
		this->bitset.push_back(number % 2);
		number = number >> 1; /* / 2 */
	}
}

uint64_t dynamic_bitset::to_ullong() const
{
	if(this->bitset.size() > 64) {
		std::cerr << "Size of bitset: " << this->bitset.size() << std::endl;
		throw std::overflow_error(
			"Can't convert to uint64 number larger that uint64_t limit!");
	}

	uint64_t result = 0;
	for(size_t i = 0; i < this->bitset.size(); ++i) {
		result += this->bitset[i] * MASK(i);
	}

	return result;
}

string dynamic_bitset::printBitset() const
{
	string output;
	for(size_t i = this->bitset.size(); i > 0; i--) {
		output += to_string(this->bitset[i - 1]);
	}

	if(this->bitset.size() <= 64) {
		output += " -> ";
		output += to_string(this->to_ullong());
	} else
		output += "-> Inf ";

	return output;
}

void dynamic_bitset::flip(size_t index)
{
	if(index >= this->bitset.size()) {
		// add 0's while size() - index
		for(size_t i = 0; i < this->bitset.size() - index - 1; ++i) {
			this->bitset.push_back(0);
		}
	}

	bitset[index] = !bitset[index];

	if(bitset[index] == 0) {
		this->compressBitset();
	}
}

bool dynamic_bitset::test(size_t index) const
{
	if(index >= this->bitset.size())
		throw std::invalid_argument("bitset.test() argument out of bounds!");
	return this->bitset[index] == 1;
}

dynamic_bitset dynamic_bitset::operator+(dynamic_bitset b)
{
	// normalizeBitsets(this, &b);
	dynamic_bitset result;

	size_t i = 0;
	bool carry = false;
	for(; i < this->bitset.size(); ++i) {
		bool sum = (this->bitset[i] ^ b[i]) ^ carry;
		carry = (this->bitset[i] && b[i]) || (this->bitset[i] && carry) ||
				(b[i] && carry);
		result.bitset.push_back(sum);
	}

	// last carry
	if(carry)
		result.bitset.push_back(carry);

	// compressBitset(&result);

	return result;
}

dynamic_bitset dynamic_bitset::operator-(dynamic_bitset b)
{
	// normalizeBitsets(this, &b);

	dynamic_bitset result;

	size_t i = 0;
	bool borrow = false;

	for(; i < b.bitset.size() || i < this->bitset.size(); ++i) {
		bool sub = (this->bitset[i] ^ b.bitset[i]) ^ borrow;
		borrow = (!this->bitset[i] && b.bitset[i]) || (!this->bitset[i] && borrow) ||
				 (b.bitset[i] && borrow);
		result.bitset.push_back(sub);
	}
	// last borrow
	if(borrow) {
		bool sub = this->bitset[i] ^ b.bitset[i];
		result.bitset.push_back(sub);
	}

	// compressBitset(&result);

	return result;
}

void dynamic_bitset::operator>>(uint64_t n)
{
	this->bitset.erase(this->bitset.begin(), this->bitset.begin() + n);
}

void dynamic_bitset::operator<<(uint64_t n)
{
	auto it = this->bitset.begin();

	for(size_t i = 0; i < n; ++i) {
		this->bitset.insert(it, 0);
		++it;
	}
}

std::vector<bool>::reference dynamic_bitset::operator[](size_t n)
{
	if(n >= this->bitset.size())
		throw std::invalid_argument("bitset [] access out of bounds!");
	return this->bitset[n];
}

bool dynamic_bitset::operator>(dynamic_bitset second) const
{
	if(this->bitset.size() != second.bitset.size())
		return (this->bitset.size() > second.bitset.size());

	bool first_is_greater = false;
	for(size_t i = 0; i < this->bitset.size(); ++i) {
		if((this->bitset[i] ^ second[i]) == 0x0)
			continue;
		if(this->bitset[i] == 1 && second[i] == 0) {
			first_is_greater = true;
			continue;
		}
		if(this->bitset[i] == 0 && second[i] == 1)
			first_is_greater = false;
	}

	return first_is_greater;
}

bool dynamic_bitset::operator<(dynamic_bitset second) const
{
	if(this->bitset.size() != second.bitset.size())
		return (this->bitset.size() < second.bitset.size());

	bool first_is_smaller = false;
	for(size_t i = 0; i < this->bitset.size(); ++i) {
		if((this->bitset[i] ^ second[i]) == 0x0)
			continue;
		if(this->bitset[i] == 0 && second[i] == 1) {
			first_is_smaller = true;
			continue;
		}
		if(this->bitset[i] == 1 && second[i] == 0)
			first_is_smaller = false;
	}

	return first_is_smaller;
}

bool dynamic_bitset::operator==(dynamic_bitset second) const
{
	if(this->bitset.size() != second.bitset.size())
		return false;

	for(size_t i = 0; i < this->bitset.size(); ++i) {
		if((this->bitset[i] ^ second[i]) == 0x1)
			return false;
	}

	return true;
}

bool dynamic_bitset::operator!=(dynamic_bitset second) const
{
	return !(*this == second);
}

void dynamic_bitset::operator+=(dynamic_bitset b) { *this = *this + b; }

void dynamic_bitset::operator-=(dynamic_bitset b) { *this = *this - b; }

void dynamic_bitset::operator=(dynamic_bitset b) { this->bitset = b.bitset; }

bool dynamic_bitset::operator>(uint64_t n) const
{
	dynamic_bitset second(n);
	return *this > second;
}

bool dynamic_bitset::operator<(uint64_t n) const
{
	// convert size_t to dynamic_bitset
	dynamic_bitset second(n);
	return *this < second;
}

bool dynamic_bitset::operator==(uint64_t n) const
{
	dynamic_bitset second(n);
	return *this == second;
}

bool dynamic_bitset::operator!=(uint64_t n) const
{
	dynamic_bitset second(n);
	return *this != second;
}

void dynamic_bitset::operator+=(uint64_t n)
{
	dynamic_bitset b(n);
	*this = *this + b;
}

void dynamic_bitset::operator-=(uint64_t n)
{
	dynamic_bitset b(n);
	*this = *this - b;
}

void dynamic_bitset::operator=(uint64_t n)
{
	dynamic_bitset b(n);
	this->bitset = b.bitset;
}

dynamic_bitset dynamic_bitset::operator+(uint64_t n)
{
	dynamic_bitset b(n);
	return *this + b;
}

dynamic_bitset dynamic_bitset::operator-(uint64_t n)
{
	dynamic_bitset b(n);

	return *this - b;
}