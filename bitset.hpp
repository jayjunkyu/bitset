// by JJeong

#ifndef BITSET_HPP
#define BITSET_HPP

#include <cstdint>
#include <string>

class Bitset{
public:

  // Default constructor.
  Bitset();

  // Constructor to set bit width.
  Bitset(intmax_t size);

  // Constructor to get bit value from string.
  Bitset(const std::string & value);

  // Destructor to delete pointer for memory leak prevention.
  ~Bitset();

  Bitset(const Bitset &) = delete;
  Bitset & operator=(const Bitset &) = delete;

  // Function to return bit size.
  intmax_t size() const;

  // Boolean function to check if bitset is valid.
  bool good() const;

  // Bitwise operator to set nth bit.
  void set(intmax_t index);

  // Bitwise operator to reset nth bit.
  void reset(intmax_t index);

  // Bitwise operator to toggle nth bit.
  void toggle(intmax_t index);

  // Bitwise operator to test if nth bit is set.
  bool test(intmax_t index);

  // Creates a string value that contains the current set bitset.
  std::string asString() const;

private:
	uint8_t *m_ptrBitset; //This pointer will be dynamically allocated with bitsets.
	unsigned int m_numOfBits; //This integer keeps track of number of bits.
	bool validity; //This boolean keeps track if bitsets are valid or not.
};

#endif
