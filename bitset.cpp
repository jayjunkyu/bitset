// by JJeong

#include "bitset.hpp"
#include <string>
#include <cstdint>
#include <iostream>

// Default constructor: Sets 8 zero bits.
Bitset::Bitset()
{
	m_numOfBits = 8;
	m_ptrBitset = new uint8_t[1]; //Allocate 1 array. 1 uint8_t array = 1 byte = 8 bits
	m_ptrBitset[0] = { 0 }; //Set to 0.

	validity = true;
}

// Constructor: Sets necessary number of index in bitset array depending on "size" or number of bits.
Bitset::Bitset(intmax_t size)
{
	unsigned int m_numOfArrIndex = 0; //Number of index.
	if (size > 0)
	{
		validity = true;
		m_numOfBits = size; //Storee "size" to keep track of number of bits we have.
		
		if ((size % (sizeof(uint8_t) * 8)) == 0) //Byte = 8 bits, so if there are no remainder let array size equal "size"/8.
			m_numOfArrIndex = (size / 8);

		if ((size % (sizeof(uint8_t) * 8)) != 0) //If there is a remainder +1 to array size.
			m_numOfArrIndex = (size / 8) + 1;
	}

	else
	{
		validity = false;
		m_numOfBits = 0;
	}

	m_ptrBitset = new uint8_t[m_numOfArrIndex]();
}

// Constructor: Takes string "value" in binary, then stores it in our bitset pointer.
Bitset::Bitset(const std::string & value)
{
	int numOfArrIndex = 0;
	m_numOfBits = value.length(); //Keeping track of number of bits.
	std::string strBits = ""; //Initialize a string to store our "value" string.

	if ((value.size() % 8 == 0) == true) //Same logic as above to find appropriate bitset width. (Due to constant compiler warning, I wrote it differently than above.)
	{
		numOfArrIndex = (value.size() / 8);
	}
	else if ((value.size() % 8 == 0) == false)
	{
		numOfArrIndex = (value.size() / 8) + 1;
	}
	else 
	{
		std::cout << "Wrong value.";
	}

	m_ptrBitset = new uint8_t[numOfArrIndex]();

	if (m_numOfBits > 0) //Checking if bitset is valid.
	{
		validity = true;
		strBits = value;

		if (strBits.find_first_not_of("01") == std::string::npos) //Checking if string contains only 0's and 1's.
		{
			validity = true;
			int temp = 0; 
			for (int i = 8; i <= (numOfArrIndex * 8); i += 8)
			{
				temp = i - 8 <= 0 ? 0 : i - 8; //Subtracting 8 to temp each time so we can slice the string into bitsets of 8 bits each except in base case where temp is 0.
				std::string strByte = strBits.substr(temp, i);
				m_ptrBitset[(i / 8) - 1] = std::stoi(strByte, nullptr, 2);
			}
		}
		else
			validity = false;
	}
	else if (m_numOfBits <= 0)
		validity = false;
}

// Destructor: Deletes bitset array.
Bitset::~Bitset()
{
	delete[] m_ptrBitset;
	m_ptrBitset = nullptr; //Making sure the memory address is deleted as well. So that there are no dangling pointers.
}

// size() function : Returns number of bits that were beeing kept track.
intmax_t Bitset::size() const
{
	return m_numOfBits;
}

// good() function : Returns our private boolean variable to confirm validity of bitsets.
bool Bitset::good() const
{
	return validity;
}

// set() function : Sets nth bit. n is [0, arrLength-1].
void Bitset::set(intmax_t index)
{
	unsigned int numOfArrIndex = ((m_numOfBits / 8) + (m_numOfBits % 8 == 0 ? 0 : 1)) - 1; //I subtracted 1 here for easier calculations down low.
	unsigned int indexShift = index / 8; //Calculated how much index shift is needed per desired index.
	unsigned int shift = index - ((index / 8) * 8); //Calculate how many shit is needed per desired index.

	if (index >= 0 && index < ((numOfArrIndex + 1) * 8)) //Checking validity if index is between 0 and max index.
	{
		if (index >= 0 && numOfArrIndex == 0) //Base case where index length = 1 or 8 bits.
		{
			validity = true;
			m_ptrBitset[0] = (m_ptrBitset[0] | (1 << index)); //To set the nth bit, shift 1 to nth index and use the OR operator.
		}

		if (index >= 0 && (numOfArrIndex > 0)) //General case where index length > 1.
		{
			validity = true;
			m_ptrBitset[numOfArrIndex - indexShift] = (m_ptrBitset[numOfArrIndex - indexShift] | (1 << shift));
		}
	}
	else
		validity = false;
}

// reset() function: Resets nth bit. n is [0, arrLength-1].
void Bitset::reset(intmax_t index)
{
	//Same logical flow as set but different bitwise operator used.

	unsigned int numOfArrIndex = ((m_numOfBits / 8) + (m_numOfBits % 8 == 0 ? 0 : 1)) - 1;
	unsigned int indexShift = index / 8; 
	unsigned int shift = index - ((index / 8) * 8);

	if (index >= 0 && index < ((numOfArrIndex + 1) * 8))
	{
		if (index >= 0 && numOfArrIndex == 0) //This time we do a negated AND operation to reset the nth bit to 0.
		{
			validity = true;
			m_ptrBitset[0] = (m_ptrBitset[0] & ~(1 << index));
		}

		if (index >= 0 && (numOfArrIndex > 0))
		{
			validity = true;
			m_ptrBitset[numOfArrIndex - indexShift] = (m_ptrBitset[numOfArrIndex - indexShift] & ~(1 << shift));
		}
	}
	else
		validity = false;
}

// toggle() function : Toggles nth bit. n is [0, arrLength-1].
void Bitset::toggle(intmax_t index)
{
	//Same logical flow as set but different bitwise operator used.

	unsigned int len = ((m_numOfBits / 8) + (m_numOfBits % 8 == 0 ? 0 : 1)) - 1;
	unsigned int indexShift = index / 8; 
	unsigned int shift = index - ((index / 8) * 8); 

	if (index >= 0 && index < ((len + 1) * 8))
	{
		if (index >= 0 && len == 0) //This time this is using XOR to toggle nth bit. 0 to 1 and 1 to 0.
		{
			validity = true;
			m_ptrBitset[0] = (m_ptrBitset[0] ^ (1 << index));
		}

		if (index >= 0 && (len > 0))
		{
			validity = true;
			m_ptrBitset[len - indexShift] = (m_ptrBitset[len - indexShift] ^ (1 << shift));
		}
	}
	else
		validity = false;
}

// bool test() function : Tests if nth bit is 1 or 0. True if 1, false if 0.
bool Bitset::test(intmax_t index)
{
	if (m_numOfBits <= 7) //Base case: where array length = 1.
	{
		if (m_ptrBitset[0] == (m_ptrBitset[0] | (1 << index))) //Check if current bit is the same as the current bit with nth bit set.
		{
			validity = true;
			return validity;
		}
		else
		{
			validity = false;
			return validity;
		}
	}

	if (m_numOfBits >= 8) //General case : Using the same logical flow from set(), reset(), toggle().
	{
		unsigned int len = ((m_numOfBits / 8) + (m_numOfBits % 8 == 0 ? 0 : 1)) - 1;
		unsigned int indexShift = index / 8; 
		unsigned int shift = index - ((index / 8) * 8); 
		if (m_ptrBitset[len - indexShift] == (m_ptrBitset[len - indexShift] | (1 << shift))) 
		{
			validity = true;
			return validity;
		}
		else
		{
			validity = false;
			return validity;
		}
	}
	else
	{
		validity = false;
		return validity;
	}
}

// asString()  function : stores the bitset as string in binary, 0's and 1's.
std::string Bitset::asString() const
{
	//This code referenced the binary print code in REXTESTER on Canvas with some added functions and conditions.
	//(Professor Plassmann allowed us to refer to them.)

	char *buff; //Create a buffer to store strings of 1's and 0's as manny as I want.
	buff = new char[100](); //Created a huge buffer char array.
	bool isBitSet; //This will check if the bit is set.

	unsigned int numOfArrIndex = ((m_numOfBits / 8)) + ((m_numOfBits % 8 == 0 ? 0 : 1) - 1); //Calculate number of index in array. Note the -1 for calculations.
	unsigned int k = numOfArrIndex + 1; //Initialize int k to loop the array index.
	std::string result = ""; //Temporary string to store all the values.
	std::string binToString = ""; //Just to make things clearer, created another string to store the resulted string from "result".

	for (int j = 0; j <= numOfArrIndex; j++)
	{
		k--;
		for (int i = 7; i >= 0; i--) //Here, we go backwards because strings store MSB first and in arrays [0] comes first than [index-1].
		{
			isBitSet = (m_ptrBitset[numOfArrIndex - k] & (1 << i));
			{
				if (isBitSet)
				{
					buff[i] = '1';
					result = result +buff[i]; //Keep adding the char buffer to our string "result".
				}
				else
				{
					buff[i] = '0';
					result = result + buff[i];
				}
			}
		}
	}

	delete[] buff; //Delete buffer char array
	buff = nullptr; //Make this dangling poitner null.

	binToString = result;
	std::cout << "\nasString() output: " << binToString << "\n";

	return binToString;
}