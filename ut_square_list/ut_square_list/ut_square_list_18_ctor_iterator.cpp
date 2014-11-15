/**	@file ut_square_list_18_ctor_iterator.cpp
	@author Garth Santor
	@date 2013-12-30
	@version 1.0.0
	@note Developed for C++ 11/vc12
	@brief square_list<> unit test for iterator constructor.
	*/

#include "ut_square_list.hpp"
#include <boost\test\auto_unit_test.hpp>
#include <string>
#include <vector>


#if TEST_PHASE >= 18

/** Test square_list<T>::square_list(iter,iter) */
BOOST_AUTO_TEST_CASE( ut_ctor_iterator_int ) {
	std::vector<int> a{ 1, 9, 2, 10, 3, 12, 4, 11, 5, 6, 7, 8 };
	square_list<int> s( a.begin(), a.end() );
	std::sort( a.begin(), a.end() );

	BOOST_CHECK( std::equal( s.begin(), s.end(), a.begin() ) );

	BOOST_CHECK( !s.empty() );
	BOOST_CHECK( s.size() == a.size() );
}



BOOST_AUTO_TEST_CASE( ut_ctor_iterator_double ) {
	std::vector<double> a{ 1, 9, 2, 10, 3, 12, 4, 11, 5, 6, 7, 8 };
	square_list<double> s( a.begin(), a.end() );
	std::sort( a.begin(), a.end() );

	BOOST_CHECK( std::equal( s.begin(), s.end(), a.begin() ) );

	BOOST_CHECK( !s.empty() );
	BOOST_CHECK( s.size() == a.size() );
}



BOOST_AUTO_TEST_CASE( ut_ctor_iterator_int_to_double ) {
	std::vector<int> a{ 1, 9, 2, 10, 3, 12, 4, 11, 5, 6, 7, 8 };
	square_list<double> s( a.begin(), a.end() );
	std::sort( a.begin(), a.end() );

	BOOST_CHECK( std::equal( s.begin(), s.end(), a.begin() ) );

	BOOST_CHECK( !s.empty() );
	BOOST_CHECK( s.size() == a.size() );
}



BOOST_AUTO_TEST_CASE( ut_ctor_iterator_string_to_char ) {
	std::string a = "Hello";
	square_list<char> s( a.begin(), a.end() );
	std::sort( a.begin(), a.end() );

	BOOST_CHECK( std::equal( s.begin(), s.end(), a.begin() ) );

	BOOST_CHECK( !s.empty() );
	BOOST_CHECK( s.size() == a.size() );
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