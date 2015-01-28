#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <iostream>
#include <stdexcept>
#include "SSLL.h"
#include "PSLL.h"
#include "SDAL.h"
#include "CDAL.h"

bool same_char( const char& a, const char& b ) {
                                // argument for contains()
  return (a == b);
}

void in_list( const cop3530::SSLL<char>& list, char c, std::ostream& out ) {
  out << c << " is " << (list.contains( c, same_char ) ? "" : "not ")
	    << "in the list ";
  list.print( out );
  out << std::endl;
}

void in_list( const cop3530::PSLL<char>& list, char c, std::ostream& out ) {
  out << c << " is " << (list.contains( c, same_char ) ? "" : "not ")
	    << "in the list ";
  list.print( out );
  out << std::endl;
}

void in_list( const cop3530::SDAL<char>& list, char c, std::ostream& out ) {
  out << c << " is " << (list.contains( c, same_char ) ? "" : "not ")
	    << "in the list ";
  list.print( out );
  out << std::endl;
}

void in_list( const cop3530::CDAL<char>& list, char c, std::ostream& out ) {
  out << c << " is " << (list.contains( c, same_char ) ? "" : "not ")
	    << "in the list ";
  list.print( out );
  out << std::endl;
}

cop3530::SSLL<char> ssll;
cop3530::PSLL<char> psll;
cop3530::SDAL<char> sdal;
cop3530::CDAL<char> cdal;


cop3530::SSLL<char>::iterator ssll_iter;
cop3530::SSLL<char>::const_iterator ssll_const_iter;
cop3530::PSLL<char>::iterator psll_iter;
cop3530::PSLL<char>::const_iterator psll_const_iter;
cop3530::SDAL<char>::iterator sdal_iter;
cop3530::SDAL<char>::const_iterator sdal_const_iter;
cop3530::CDAL<char>::iterator cdal_iter;
cop3530::CDAL<char>::const_iterator cdal_const_iter;

TEST_CASE("SSLL: is_empty() method", "checking if list is empty")
{
    REQUIRE(ssll.is_empty());
}

TEST_CASE("SSLL: empty list checking exception", "check to see if we can pop element from empty list")
{
    SECTION("pop_back()")
        REQUIRE_THROWS_AS(ssll.pop_back(), std::logic_error); // if the list is empty and we are trying to pop, it should throw a logic error
    SECTION("pop_front()")
        REQUIRE_THROWS_AS(ssll.pop_front(), std::logic_error); // if the list is empty and we are trying to pop, it should throw a logic error
    SECTION("remove(position)")
        REQUIRE_THROWS_AS(ssll.remove(5), std::logic_error); // if the list is empty and we are trying to remove, it should throw a logic error
    SECTION("replace(element, position)")
        REQUIRE_THROWS_AS(ssll.replace('S', 1), std::logic_error); // if the list is empty and we are trying to replace an element, it should throw a logic error
    SECTION("item_at(position)")
        REQUIRE_THROWS_AS(ssll.item_at(0), std::logic_error); // if the list is empty and we are trying to find an item at a position, it should throw a logic error
    SECTION("opearatot[]int(i)")
        REQUIRE_THROWS_AS(ssll[3], std::logic_error); // if the list is empty and we are trying to use subscript operator, it should throw a logic error
}

TEST_CASE("SSLL: replace(element, position) method", "check to see if we can replace elements in SSLL")
{
    for(int i = 0; i < 5; i++)
    {
        ssll.push_front('U');
    }

    REQUIRE(ssll.replace('A', 3) == 'U');
}

TEST_CASE("SSLL: exception checking other than with empty list", "check to see if appropriate exceptions are thrown")
{
    SECTION("replace(element, position)")
        REQUIRE_THROWS_AS(ssll.replace('B', -1), std::out_of_range); //making sure after evaluating the expression, it throws the appropriate exception
    SECTION("insert(element, position)")
        REQUIRE_THROWS_AS(ssll.insert('Q', 8), std::out_of_range); //we cant insert into position larger than max
    SECTION("remove(position)")
        REQUIRE_THROWS_AS(ssll.remove(10), std::out_of_range); //we cant remove from position larger than max
    SECTION("item_at(position)")
        REQUIRE_THROWS_AS(ssll.item_at(9), std::out_of_range); //we cant access element from position larger than max
    SECTION("opearatot[]int(i)")
        REQUIRE_THROWS_AS(ssll[7], std::logic_error); // we cant access element from position larger than max using subscript operator

}

TEST_CASE("SSLL: size() method ", "check to see if size() method works correctly")
{
    for(int i = 0; i < 5; i++)
    {
        ssll.push_front('X');
    }
    REQUIRE(ssll.size() == 10); // checking if size() returns the correct answer
}

TEST_CASE("SSLL: pop_front() method", "check to see if pop_front() method works correctly")
{
    for(int i = 0; i < 5; i++)
    {
        ssll.push_front('T');
    }
    REQUIRE_FALSE(ssll.pop_front() == 't'); // making sure pop_front() do not returns wrong answer
}

TEST_CASE("SSLL: insert(element, position", "check to see if insert method works correctly")
{
    ssll.insert('Q', 3);
    REQUIRE(ssll.item_at(3) == 'Q'); // checking element at the inserted position
}

TEST_CASE("SSLL: reference* iterators ", "check to see reference* for iterator works correctly")
{
    SECTION("regular iterator")
    {
        ssll_iter = ssll.begin();
        REQUIRE(*ssll_iter == 'T');
    }

    SECTION("const iterator")
    {
        const cop3530::SSLL<char> ssll_const_list = ssll;
        ssll_const_iter = ssll_const_list.begin();
        REQUIRE(*ssll_const_iter == 'T');
    }
}


