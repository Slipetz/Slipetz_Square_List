/**	@file ut_square_list_swap_function.cpp
	@author Garth Santor
	@date 2013-12-30
	@version 2.0.0
	@note Developed for C++ 11/vc12
	@brief square_list<> unit test for swap method.
	*/

#include "ut_square_list.hpp"
#include <boost\test\auto_unit_test.hpp>
#include <string>


#if TEST_PHASE >= 24

/** Test square_list<T>::swap() */
BOOST_AUTO_TEST_CASE( ut_swapf_empty_to_empty ) {
	square_list<char> a, b;

	BOOST_CHECK( a.empty() );
	BOOST_CHECK( b.empty() );

	swap(a, b);

	BOOST_CHECK( a.empty() );
	BOOST_CHECK( b.empty() );
}



BOOST_AUTO_TEST_CASE( ut_swapf_pop_to_empty ) {
	square_list<char> a, b;

	std::string s = "abcde";
	for (auto ch : s)
		a.insert(ch);

	BOOST_CHECK( a.size() == s.size() );
	BOOST_CHECK( std::equal( a.begin(), a.end(), s.begin() ) );

	BOOST_CHECK( b.empty() );

	swap(a, b);

	BOOST_CHECK( a.empty() );
	BOOST_CHECK( b.size() == s.size() );
	BOOST_CHECK( std::equal( b.begin(), b.end(), s.begin() ) );
}



BOOST_AUTO_TEST_CASE( ut_swapf_empty_to_populated ) {
	square_list<char> a, b;

	std::string s = "abcde";
	for (auto ch : s)
		a.insert(ch);

	BOOST_CHECK( a.size() == s.size() );
	BOOST_CHECK( std::equal( a.begin(), a.end(), s.begin() ) );

	BOOST_CHECK( b.empty() );

	swap(a, b);

	BOOST_CHECK( a.empty() );
	BOOST_CHECK( b.size() == s.size() );
	BOOST_CHECK( std::equal( b.begin(), b.end(), s.begin() ) );
}



BOOST_AUTO_TEST_CASE( ut_swapf_populated_to_populated ) {
	square_list<char> a, b;

	std::string s = "abcde", t = "fghi";
	for (auto ch : s)
		a.insert(ch);
	for (auto ch : t)
		b.insert(ch);

	BOOST_CHECK( a.size() == s.size() );
	BOOST_CHECK( std::equal( a.begin(), a.end(), s.begin() ) );

	BOOST_CHECK( b.size() == t.size() );
	BOOST_CHECK( std::equal( b.begin(), b.end(), t.begin() ) );

	swap(a, b);

	BOOST_CHECK( a.size() == t.size() );
	BOOST_CHECK( std::equal( a.begin(), a.end(), t.begin() ) );

	BOOST_CHECK( b.size() == s.size() );
	BOOST_CHECK( std::equal( b.begin(), b.end(), s.begin() ) );
}
#endif



/*============================================================================

Revision History

Version 1.0.0: 2013-12-30

Version 0.0.0: 2006-10-16

==============================================================================
Copyright Garth Santor, 2006-2014

The copyright to the computer program(s) herein
is the property of Garth Santor, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
============================================================================*/