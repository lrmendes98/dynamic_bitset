#ifndef DYNAMICBITSET_H
#define DYNAMICBITSET_H

#include <iostream>
#include <vector>

#define MASK(N) (0x1ull << N)

class dynamic_bitset {
   private:
    std::vector<bool> bitset;

   public:
    dynamic_bitset() {}
    dynamic_bitset(uint64_t number) {
        if (number == 0) this->bitset.push_back(0);
        while (number > 0) {
            this->bitset.push_back(number % 2);
            number = number >> 1; /* / 2 */
        }
    }
    std::vector<bool> getQState() { return this->bitset; }
    void printBitset() const;

    // TODO: flip de 1 do mais significativo vira 0. remover 0?
    void flip(size_t index) {
        if (index >= this->bitset.size())
            throw std::invalid_argument(
                "bitset.flip() argument out of bounds!");
        bitset[index] = !bitset[index];
    }

    bool test(size_t index) {
        if (index >= this->bitset.size())
            throw std::invalid_argument(
                "bitset.test() argument out of bounds!");
        return this->bitset[index] == 1;
    }

    uint64_t to_ullong() {
        if (this->bitset.size() > 64) {
            std::cerr << "Size of bitset: " << this->bitset.size() << std::endl;
            throw std::overflow_error(
                "Can't convert to uint64 number larger that uint64_t limit!");
        }

        uint64_t result = 0;
        for (size_t i = 0; i < this->bitset.size(); ++i) {
            result += this->bitset[i] * MASK(i);
        }

        return result;
    }

    // overload + operator (size_t + QuantumGlobalState)
    dynamic_bitset operator+(dynamic_bitset b) {
        dynamic_bitset result;

        size_t i = 0;
        bool carry = false;
        for (; i < b.bitset.size() || i < this->bitset.size(); ++i) {
            bool sum = (this->bitset[i] ^ b[i]) ^ carry;
            carry = (this->bitset[i] && b[i]) || (this->bitset[i] && carry) ||
                    (b[i] && carry);
            result.bitset.push_back(sum);
        }
        // last carry
        if (carry) {
            bool sum = (this->bitset[i] ^ b[i]) ^ carry;
            carry = (this->bitset[i] && b[i]) || (this->bitset[i] && carry) ||
                    (b[i] && carry);
            result.bitset.push_back(sum);
        }

        return result;
    }

    dynamic_bitset operator+(uint64_t n) {
        dynamic_bitset b(n);
        return *this + b;
    }

    dynamic_bitset operator-(dynamic_bitset b) {
        dynamic_bitset result;

        size_t i = 0;
        bool borrow = false;
        for (; i < b.bitset.size() || i < this->bitset.size(); ++i) {
            bool sub = (this->bitset[i] ^ b[i]) ^ borrow;
            borrow = (!this->bitset[i] && b[i]) ||
                     (!this->bitset[i] && borrow) || (b[i] && borrow);
            result.bitset.push_back(sub);
        }
        // last borrow
        if (borrow) {
            bool sub = (this->bitset[i] ^ b[i]) ^ borrow;
            borrow = (!this->bitset[i] && b[i]) ||
                     (!this->bitset[i] && borrow) || (b[i] && borrow);
            result.bitset.push_back(sub);
        }

        return result;
    }

    dynamic_bitset operator-(uint64_t n) {
        dynamic_bitset result;
        dynamic_bitset b(n);

        return *this - b;
    }

    void operator>>(uint64_t n) {
        this->bitset.erase(this->bitset.begin(), this->bitset.begin() + n);
    }

    void operator<<(uint64_t n) {
        auto it = this->bitset.begin();

        for (size_t i = 0; i < n; ++i) {
            this->bitset.insert(it, 0);
            ++it;
        }
    }

    std::vector<bool>::reference operator[](uint64_t n) {
        return this->bitset[n];
    }

    bool operator>(dynamic_bitset second) {
        if (this->bitset.size() != second.bitset.size())
            return (this->bitset.size() > second.bitset.size());

        bool first_is_greater = false;
        for (size_t i = 0; i < this->bitset.size(); ++i) {
            if ((this->bitset[i] ^ second[i]) == 0x0) continue;
            if (this->bitset[i] == 1 && second[i] == 0) {
                first_is_greater = true;
                continue;
            }
            if (this->bitset[i] == 0 && second[i] == 1)
                first_is_greater = false;
        }

        return first_is_greater;
    }

    bool operator>(uint64_t n) {
        dynamic_bitset second(n);
        return *this > second;
    }

    bool operator<(dynamic_bitset second) {
        if (this->bitset.size() != second.bitset.size())
            return (this->bitset.size() < second.bitset.size());

        bool first_is_smaller = false;
        for (size_t i = 0; i < this->bitset.size(); ++i) {
            if ((this->bitset[i] ^ second[i]) == 0x0) continue;
            if (this->bitset[i] == 0 && second[i] == 1) {
                first_is_smaller = true;
                continue;
            }
            if (this->bitset[i] == 1 && second[i] == 0)
                first_is_smaller = false;
        }

        return first_is_smaller;
    }

    bool operator<(uint64_t n) {
        // convert size_t to dynamic_bitset
        dynamic_bitset second(n);
        return *this < second;
    }

    bool operator==(dynamic_bitset second) {
        if (this->bitset.size() != second.bitset.size()) return false;

        for (size_t i = 0; i < this->bitset.size(); ++i) {
            if ((this->bitset[i] ^ second[i]) == 0x1) return false;
        }

        return true;
    }

    bool operator==(uint64_t n) {
        dynamic_bitset second(n);
        return *this == second;
    }

    bool operator!=(dynamic_bitset second) { return !(*this == second); }

    bool operator!=(uint64_t n) {
        dynamic_bitset second(n);
        return *this != second;
    }

    void operator+=(dynamic_bitset b) { *this = *this + b; }

    void operator+=(uint64_t n) {
        dynamic_bitset b(n);
        *this = *this + b;
    }

    void operator-=(dynamic_bitset b) { *this = *this - b; }

    void operator-=(uint64_t n) {
        dynamic_bitset b(n);
        *this = *this - b;
    }
};

void dynamic_bitset::printBitset() const {
    for (size_t i = this->bitset.size(); i > 0; i--) {
        std::cout << this->bitset[i - 1];
    }
    std::cout << std::endl;
}

int main() {
    uint64_t state1_num = 4;
    uint64_t state2_num = 3;

    dynamic_bitset bitset1(state1_num);
    dynamic_bitset bitset2(state2_num);
    // bitset1.printBitset();
    // std::cout << (bitset1 - ~0).to_ullong() << std::endl;
    // std::cout << bitset1.to_ullong() << std::endl;
    bitset1.printBitset();
    bitset2.printBitset();
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

    std::cout << "Equals:" << std::endl;
    if (bitset1 == bitset2)
        std::cout << "\ttrue" << std::endl;
    else
        std::cout << "\tfalse" << std::endl;

    std::cout << "Not Equals:" << std::endl;
    if (bitset1 != bitset2)
        std::cout << "\ttrue" << std::endl;
    else
        std::cout << "\tfalse" << std::endl;

    return 0;
}

#endif