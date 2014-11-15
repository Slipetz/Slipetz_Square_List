/**	@file ut_square_list_13_erase_range.cpp
	@author Garth Santor
	@date 2013-12-30
	@version 1.0.0
	@note Developed for C++11/vc12
	@brief square_list<> unit test for erase a range of elements.
	*/

#include "ut_square_list.hpp"
#include <boost\test\auto_unit_test.hpp>
#include <algorithm>
#include <iostream>
#include <vector>


#if TEST_PHASE >= 13


/** Test square_list<int>::erase() of a list of scrambled integers. */
BOOST_AUTO_TEST_CASE( test_erase_range ) {

	std::vector<int> data{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<int> nextData{ 1, 2, 9, 10 };

	square_list<int> s;
	for (auto datum : data)
		s.insert(datum);

	auto b = std::find( s.begin(), s.end(), 3 );
	auto e = std::find( s.begin(), s.end(), 9 );
	auto r = s.erase( b, e );
	BOOST_CHECK( std::equal( s.begin(), s.end(), nextData.begin() ) );
	BOOST_CHECK( *r == 9 );
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