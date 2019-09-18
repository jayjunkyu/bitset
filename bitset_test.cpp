// by JJeong

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "bitset.hpp"
#include <cstdint>


TEST_CASE( "Test bitset constructor", "[bitset]" ) {

    Bitset b; 
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
}

//Test bitset constructor initialized based on width N.
intmax_t test_bitWidth = 20;
TEST_CASE("Test bitset constructor w/ size", "[bitset]")
{
	Bitset b(test_bitWidth); //Create bitset with width N.
	REQUIRE(b.size() == 20); //Size should return number of bits.
	REQUIRE(b.good()); //This checks if N > 0.
}

//Test bitset constructor initialized based on string.
std::string test_binString = "000000001";
TEST_CASE("Test bitset constructor w/ string", "[bitset]")
{
	Bitset b(test_binString); //Create bitset via string.
	REQUIRE(b.size() == 9); //Check number of bits created.
	REQUIRE(b.good()); //Check if string only contains 0's and 1's and if size() > 0.
}

//Testing the set() function.
std::string test_binString1 = "00010";
intmax_t test_index1 = -1;
TEST_CASE("Test setting nth bit", "[bitset]")
{
	Bitset b(test_binString1);
	b.set(test_index1); //Set index -1 to 1. (Which is NOT A VALID INDEX.)
	REQUIRE_FALSE(b.good()); //Check validity.
	REQUIRE(b.size() == 5); //Check size
}

//Testing the reset() function.
std::string test_binString2 = "101";
intmax_t test_index2 = 0;
TEST_CASE("Test resetting nth bit", "[bitset]")
{
	Bitset b(test_binString2);
	b.reset(test_index2); //Reset index 0 (0th bit) to 1.
	REQUIRE(b.size() == 3); //Check size.
	REQUIRE(b.good());  //Check validity.
}

//Testing the toggle() function.
std::string test_binString3 = "1011101";
intmax_t test_index3 = 0;
TEST_CASE("Test toggling nth bit", "[bitset]")
{
	Bitset b(test_binString3);
	b.reset(test_index3); //Toggle index 0 (0th bit) to 1.
	REQUIRE(b.size() == 7); //Check size.
	REQUIRE(b.good());  //Check validity.
}

//Testing the test() function.
std::string test_binString4 = "00000001";
intmax_t test_index4 = 0;
TEST_CASE("Test if nth bit is set", "[bitset]")
{
	Bitset b(test_binString4); //Create bitset
	b.test(test_index4); //Call test function which returns a boolean value to good()
	REQUIRE(b.size() == 8);
	REQUIRE(b.good()); //Call good(). If true, nth bit is set.
}

//Testing the asString() function.
std::string test_binString5 = "10101010";
TEST_CASE("Test binary to string function", "[bitset]")
{
	Bitset b(test_binString5); //Create a bitset using test_binString5.
	b.asString(); //This will output 10101010 on the command window.
}