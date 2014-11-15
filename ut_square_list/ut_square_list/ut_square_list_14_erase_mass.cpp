/**	@file ut_square_list_14_erase_mass.cpp
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
#include <set>


#if TEST_PHASE >= 14


/** Test square_list<int>::erase(key) of a list of integers. */
BOOST_AUTO_TEST_CASE( test_erase_mass ) {

	std::multiset<int> data{ 1, 1, 2, 3, 4, 4, 4, 5, 6, 7, 8, 9, 10, 10 };

	square_list<int> s;
	for (auto datum : data)
		s.insert(datum);

	auto nListErased = s.erase(1);
	auto nSetErased = data.erase(1);
	BOOST_CHECK_EQUAL(nListErased, nSetErased);
	BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), data.begin(), data.end());

	nListErased = s.erase(4);
	nSetErased = data.erase(4);
	BOOST_CHECK_EQUAL(nListErased, nSetErased);
	BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), data.begin(), data.end());

	nListErased = s.erase(10);
	nSetErased = data.erase(10);
	BOOST_CHECK_EQUAL(nListErased, nSetErased);
	BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), data.begin(), data.end());
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