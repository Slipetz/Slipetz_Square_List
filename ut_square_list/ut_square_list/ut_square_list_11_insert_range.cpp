/**	@file ut_square_list_11_insert_range.cpp
	@author Garth Santor
	@date 2013-12-30
	@version 1.0.0
	@note Developed for C++ 11/vc12
	@brief square_list<> unit test for inserting a range of elements.
	*/

#include "ut_square_list.hpp"
#include <boost\test\auto_unit_test.hpp>
#include <array>
#include <algorithm>
#include <set>
#include <iostream>



#if TEST_PHASE >= 11

/** Test square_list<int>::insert() of a iterator defined range. */
BOOST_AUTO_TEST_CASE( test_insert_range_to_empty ) {
	std::array<int,10> a = { 9, 10, 7, 8, 5, 6, 3, 4, 1, 2 };
	square_list<int> sqi;

	sqi.insert( a.begin(), a.end() );
	std::sort( a.begin(), a.end() );

	BOOST_CHECK( sqi.size() == a.size() );
	BOOST_CHECK( std::equal( sqi.begin(), sqi.end(), a.begin() ) );
}



BOOST_AUTO_TEST_CASE( test_insert_range_to_populated ) {
	std::array<int,4> a = { 2, 4, 5, 3 };
	std::array<int,2> b = { 1, 6 };
	std::vector<int> v(a.begin(),a.end());
	v.insert(v.begin(),b.begin(),b.end());
	std::sort(v.begin(), v.end());

	square_list<int> sqi;

	sqi.insert( a.begin(), a.end() );
	sqi.insert( b.begin(), b.end() );

	BOOST_CHECK( sqi.size() == v.size() );
	BOOST_CHECK( std::equal( sqi.begin(), sqi.end(), v.begin() ) );
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